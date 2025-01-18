//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-or-later
//

#include <ibis/util/file/file_loader.hpp>
#include <ibis/platform.hpp>

#include <ibis/settings.hpp>
#include <ibis/message.hpp>

#include <ibis/util/compiler/warnings_off.hpp>  // [-Wsign-conversion]
#include <boost/locale/format.hpp>
#include <boost/locale/message.hpp>
#include <ibis/util/compiler/warnings_on.hpp>

#include <fstream>
#include <format>
#include <map>
#include <sstream>
#include <utility>
#include <string_view>
#include <filesystem>
#include <chrono>
#include <ratio>
#include <system_error>
#include <ctime>
#include <cerrno>

namespace ibis::util {

file_loader::file_loader(std::ostream& os_)
    : os{ os_ }
    , quiet{ ibis::settings::instance().get<bool>("quiet") }
{
}

bool file_loader::exist_file(fs::path const& filename) const
{
    using boost::locale::format;
    using boost::locale::translate;

    fs::path filename_preferred = filename;
    filename_preferred.make_preferred();

    try {
        if (fs::exists(filename)) {
            if (fs::is_regular_file(filename)) {
                return true;
            }

            if (!quiet) {
                os << format(translate("File {1} is not a regular file")) % filename_preferred;
            }

            return false;
        }

        if (!quiet) {
            os << format(translate("File {1} does not exists")) % filename_preferred;
        }
        return false;
    }
    catch (fs::filesystem_error const& e) {
        if (!quiet) {
            os << format(translate("Failed existence test for file {1}: caught exception {2}")) %
                      filename_preferred % e.what();
        }
        return false;
    }
}

bool file_loader::unique_files(std::vector<fs::path> const& fs_path_list) const
{
    using boost::locale::format;
    using boost::locale::translate;

    auto const canonical = [](fs::path const& filename) {
        return fs::canonical(filename).make_preferred();
    };

    auto const print_duplicates = [&](auto const& canonical_filename) {
        std::string_view delimiter{ "" };
        for (auto const& filename : fs_path_list) {
            if (canonical(filename) == canonical_filename) {
                os << std::format("{}'{}'", std::exchange(delimiter, ", "), filename.string());
            }
        }
    };

    std::map<fs::path,    // canonical_filename
             std::size_t  // count
             >
        occurrence;

    for (auto const& filename : fs_path_list) {
        if (!exist_file(filename)) {
            return false;
        }
        ++occurrence[canonical(filename)];
    }

    for (auto const& [filename, count] : occurrence) {  // NOLINT(readability-use-anyofallof)

        if (count > 1) {
            if (!quiet) {
                os << format(translate("Duplicates of file \"{1}\", specified as: ")) % filename;
                print_duplicates(filename);
                os << '\n';
            }
            return false;
        }
    }

    return true;
}

std::expected<std::string, std::error_code> file_loader::read_file(fs::path const& filename) const
{
    using boost::locale::format;
    using boost::locale::translate;

    std::ifstream ifs{ filename, std::ios::in | std::ios::binary };

    if (!ifs.is_open()) {
        std::error_code const ec{ errno, std::generic_category() };
        if (!quiet) {
            std::cout << format(translate("Error opening file \"{1}\" ({2})"))  // --
                             % filename % ec.message();
        }
        return std::unexpected{ ec };
    }

    // see Scott Meyers "Effective STL" item 29
    std::string contents{ std::istreambuf_iterator<char>(ifs), std::istreambuf_iterator<char>() };

    if (ifs.fail() && !ifs.eof()) {
        std::error_code const ec{ errno, std::generic_category() };
        if (!quiet) {
            std::cout << format(translate("Error reading file \"{1}\" ({2})"))  // --
                             % filename % ec.message();
        }
        return std::unexpected{ ec };
    }

    if (!quiet) {
        std::cout << std::format("read '{}' ({} bytes)\n", filename.generic_string(),
                                 contents.size());
    }

    return contents;
}

std::expected<std::string, std::error_code> file_loader::read_file_alt(
    fs::path const& filename) const
{
    // ToDo Seems not as easy as one can read on blogs (regards tellg()), see notes at SO
    // [How do I read an entire file into a std::string in C++?](
    //  https://stackoverflow.com/questions/116038/how-do-i-read-an-entire-file-into-a-stdstring-in-c)

    using boost::locale::format;
    using boost::locale::translate;

    std::ifstream ifs{ filename, std::ios::in | std::ios::binary | std::ios::ate };

    if (!ifs.is_open()) {
        std::error_code const ec{ errno, std::generic_category() };
        if (!quiet) {
            std::cout << format(translate("Unable opening file \"{1}\" ({2})"))  // --
                             % filename % ec.message();
        }
        return std::unexpected{ ec };
    }

    ifs.unsetf(std::ios::skipws);

    std::ifstream::pos_type const file_size = ifs.tellg();
    if (file_size < 0) {
        std::error_code const ec{ errno, std::generic_category() };
        if (!quiet) {
            std::cout << format(translate("Error tellg() for file \"{1}\" ({2})"))  // --
                             % filename % ec.message();
        }
        return std::unexpected{ ec };
    }

    std::string contents{};
    contents.reserve(static_cast<std::string::size_type>(file_size));

    ifs.seekg(0, std::ios::beg);
    ifs.read(contents.data(), file_size);

    if (ifs.fail() && !ifs.eof()) {
        std::error_code const ec{ errno, std::generic_category() };
        if (!quiet) {
            std::cout << format(translate("Error reading file \"{1}\" ({2})"))  // --
                             % filename % ec.message();
        }
        return std::unexpected{ ec };
    }

    return contents;
}

std::time_t file_loader::timesstamp(fs::path const& filename) const
{
    namespace chrono = std::chrono;
    using boost::locale::format;
    using boost::locale::translate;

    auto const report_error = [&](std::error_code ec) {
        if (ec && !quiet) {
            ibis::warning(                                                      // --
                format(translate("Failed to determine file time of {1}: {2}"))  // --
                // [C++26] has std::formatter<std::filesystem::path>
                % fs::path{ filename }.make_preferred() % ec.message());
        }
    };

    std::error_code ec;
    auto const file_time = fs::last_write_time(filename, ec);
    report_error(ec);  // not tragic from today's perspective, as not (yet) used (and tested)

    // See [How to convert std::filesystem::file_time_type to time_t?](
    //  https://stackoverflow.com/questions/61030383/how-to-convert-stdfilesystemfile-time-type-to-time-t)
    if constexpr (ibis::build_compiler_has_libcpp == true) {
        // handle libc++ compile error: no member named 'clock_cast' in namespace 'std::chrono'
        auto const to_time_t = [](fs::file_time_type time_point) {
            using namespace std::chrono;
            auto sctp = time_point_cast<system_clock::duration>(
                time_point - fs::file_time_type::clock::now() + system_clock::now());
            return system_clock::to_time_t(sctp);
        };

        std::time_t const sys_time = to_time_t(file_time);
        return sys_time;
    }
    else {
#if !defined(_LIBCPP_VERSION)  // hide "faulty code" from Clang/libc++ 18 (clock_cast<> won't found)
        auto const sys_time = chrono::clock_cast<chrono::system_clock>(file_time);
        return chrono::system_clock::to_time_t(sys_time);
#endif
    }
}

}  // namespace ibis::util
