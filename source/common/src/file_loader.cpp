#include <ibis/util/file/file_loader.hpp>

#include <ibis/settings.hpp>

#include <boost/locale/format.hpp>
#include <boost/locale/message.hpp>

#include <fstream>
#include <map>
#include <sstream>
#include <utility>
#include <filesystem>
#include <chrono>
#include <ratio>
#include <system_error>

namespace ibis::util {

file_loader::file_loader(std::ostream& os_)
    : os{ os_ }
    , quiet{ ibis::settings::instance().get<bool>("quiet") }
{
}

file_loader::file_loader(std::ostream& os_, bool quiet_)
    : os{ os_ }
    , quiet{ quiet_ }
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
    contents.reserve(size);

    ifs.read(&contents[0], size);

    if (ifs.fail() && !ifs.eof()) {
        if (!quiet) {
            os << format(translate("Error reading file \"{1}\"")) % filename << '\n';
        }
        return {};
    }

    return contents;
}

std::time_t file_loader::timesstamp(fs::path const& filename) const
{
    std::error_code ec;
    auto const ftime = fs::last_write_time(filename, ec);

    if (ec && !quiet) {
        os << "Failed to determine file time of " << fs::path{ filename }.make_preferred() << ": "
           << ec.message() << std::endl;
    }

    // FixMe [C++20] What for a mess, see
    // [How to convert std::filesystem::file_time_type to time_t?](
    // https://stackoverflow.com/questions/61030383/how-to-convert-stdfilesystemfile-time-type-to-time-t)
    auto const to_time_t = [](fs::file_time_type tp) {
        using namespace std::chrono;
        auto sctp = time_point_cast<system_clock::duration>(tp - fs::file_time_type::clock::now() +
                                                            system_clock::now());
        return system_clock::to_time_t(sctp);
    };

    std::time_t cftime = to_time_t(ftime);
    return cftime;
}

}  // namespace ibis::util
