//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-or-later
//

#include <ibis/util/file/file_loader.hpp>
#include <ibis/util/platform.hpp>

#include <ibis/settings.hpp>
#include <ibis/message.hpp>

#include <ibis/util/compiler/warnings_off.hpp>  // [-Wsign-conversion]
#include <boost/locale/format.hpp>
#include <boost/locale/message.hpp>
#include <ibis/util/compiler/warnings_on.hpp>

#include <fstream>
#include <map>
#include <sstream>
#include <utility>
#include <filesystem>
#include <chrono>
#include <ratio>
#include <system_error>
#include <ctime>

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

bool file_loader::unique_files(std::vector<fs::path> const& file_list) const
{
    using boost::locale::format;
    using boost::locale::translate;

    auto const canonical = [](fs::path const& filename) {
        return fs::canonical(filename).make_preferred();
    };

    auto const print_duplicates = [&](auto const& canonical_filename) {
        const char* delimiter = "";
        for (auto const& filename : file_list) {
            if (canonical_filename == canonical(filename)) {
                os << delimiter << '"' << filename << '"';
                delimiter = ", ";
            }
        }
    };

    std::map<fs::path,    // canonical_filename
             std::size_t  // count
             >
        occurrence;

    for (auto const& filename : file_list) {
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

std::optional<std::string> file_loader::read_file(fs::path const& filename) const
{
    using boost::locale::format;
    using boost::locale::translate;

    std::ifstream ifs{ filename, std::ios::in | std::ios::binary };

    if (!ifs) {
        if (!quiet) {
            os << format(translate("Unable to open file \"{1}\"")) % filename << '\n';
        }
        return {};
    }

    ifs.unsetf(std::ios::skipws);

    std::ostringstream ss{};
    ss << ifs.rdbuf();

    if (ifs.fail() && !ifs.eof()) {
        if (!quiet) {
            os << format(translate("Error reading file \"{1}\"")) % filename << '\n';
        }
        return {};
    }

    return ss.str();
}

std::optional<std::string> file_loader::read_file_alt(fs::path const& filename) const
{
    using boost::locale::format;
    using boost::locale::translate;

    std::ifstream ifs{ filename, std::ios::in | std::ios::binary | std::ios::ate };

    if (!ifs) {
        if (!quiet) {
            os << format(translate("Unable to open file \"{1}\"")) % filename << '\n';
        }
        return {};
    }

    ifs.unsetf(std::ios::skipws);

    std::ifstream::pos_type const size = ifs.tellg();
    ifs.seekg(0, std::ios::beg);

    std::string contents{};
    contents.reserve(static_cast<std::string::size_type>(size));

    ifs.read(contents.data(), size);

    if (ifs.fail() && !ifs.eof()) {
        if (!quiet) {
            os << format(translate("Error reading file \"{1}\"")) % filename << '\n';
        }
        return {};
    }

    return std::optional<std::string>{ contents };
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
                % fs::path{ filename }.make_preferred() % ec.message()          // --
            );
        }
    };

    std::error_code ec;
    auto const file_time = fs::last_write_time(filename, ec);
    report_error(ec);  // not tragic from today's perspective, as not (yet) used (and tested)

    // See [How to convert std::filesystem::file_time_type to time_t?](
    //  https://stackoverflow.com/questions/61030383/how-to-convert-stdfilesystemfile-time-type-to-time-t)
    if constexpr (ibis::build_compiler_has_libcpp) {
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
        auto const sys_time = chrono::clock_cast<chrono::system_clock>(file_time);

        return chrono::system_clock::to_time_t(sys_time);
    }
}

}  // namespace ibis::util
