/*
 * file_reader.cpp
 *
 *  Created on: 31.07.2018
 *      Author: olaf
 */

#include <eda/util/file/file_reader.hpp>

#include <eda/compiler/warnings_off.hpp>
#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>
#include <eda/compiler/warnings_on.hpp>

#include <eda/support/boost/locale.hpp>

#include <iterator>

#include <map>

#include <eda/namespace_alias.hpp>


namespace eda { namespace util {


bool file_loader::exist_file(std::string const& filename) const
{
    using boost::locale::format;
    using boost::locale::translate;

    try {
        fs::path file_path{ filename };

        if (fs::exists(file_path)) {

            if (fs::is_regular_file(file_path)) {
                //os << file_path.make_preferred() << " (OK)\n";
                return true;
            }
            else {
                os << format(translate(
                      "File {1} is not a regular file"))
                      % file_path.make_preferred();
                return false;
            }
        }
        else {
            os << format(translate(
                  "File {1} does not exists"))
                  % file_path.make_preferred();
            return false;
        }
    }
    catch (fs::filesystem_error const& e) {
        os << format(translate(
              "Failed existence test for file {1}: caught exception {1}"))
              % e.what();
        return false;
    }
}


/* Returns true, if the file_list has unique files. Otherwise prints the duplicates
 * and returns false.
 *
 * FixMe: The algorithm is O(n^2); using a hash may prevent this.
 */
bool file_loader::unique_files(std::vector<std::string> const& file_list) const {

        using boost::locale::format;
        using boost::locale::translate;

        auto const canonical = [](std::string const& filename) {
            return fs::canonical(filename).make_preferred().string();
        };

        auto const print_duplicates = [&](auto const& canonical_filename) {
            const char* delimiter = "";
            for (std::string const& filename : file_list) {
                if (canonical_filename.compare(canonical(filename)) == 0) {
                    os << delimiter << '"' << filename << '"';
                    delimiter = ", ";
                }
            }
        };

        std::map<std::string, std::size_t> occourence;

        for (auto const& filename : file_list) {

            if (!exist_file(filename)) {
                return false;
            }
            ++occourence[canonical(filename)];
        }

        for (auto const [canonical_filename, count] : occourence) {

            if (count > 1) {
                os << format(translate(
                      "Duplicate file \"{1}\", specified as: "))
                      % canonical_filename
                      ;
                print_duplicates(canonical_filename);
                os << "\n";
                return false;
            }
        }

    return true;
}


/* file read method using rdbuf()
 * \see[How to read in a file in C++](
 * https://insanecoding.blogspot.com/2011/11/how-to-read-in-file-in-c.html) */
std::string file_loader::read_file(std::string const& filename) const {

    using boost::locale::format;
    using boost::locale::translate;

    fs::ifstream file{ filename, std::ios::in | std::ios::binary };

    if (!file) {
        throw std::ios_base::failure{
            (format(translate("Error opening file \"{1}\"")) % filename).str()
        };
    }

    std::ostringstream ss { };
    file.unsetf(std::ios::skipws);
    ss << file.rdbuf();

    if (file.fail() && !file.eof()) {
        throw std::ios_base::failure{
            (format(translate("Error reading file \"{1}\"")) % filename).str()
        };
    }

    return ss.str();
}

/* alternative read method using seek
 * \see[How to read in a file in C++](
 * https://insanecoding.blogspot.com/2011/11/how-to-read-in-file-in-c.html) */
std::string file_loader::read_file_alt(std::string const& filename) const {

    using boost::locale::format;
    using boost::locale::translate;

    fs::ifstream file { filename, std::ios::in | std::ios::binary | std::ios::ate };

    if (!file) {
        throw std::ios_base::failure{
            (format(translate("Error opening file \"{1}\"")) % filename).str()
        };
    }

    file.unsetf(std::ios::skipws);

    fs::ifstream::pos_type const size = file.tellg();
    file.seekg(0, std::ios::beg);

    std::string contents { };
    contents.resize(size);

    file.read(&contents[0], size);

    if (file.fail() && !file.eof()) {
        throw std::ios_base::failure{
            (format(translate("Error reading file \"{1}\"")) % filename).str()
        };
    }

    return contents;
}

//< time point of last write occurrence
std::time_t file_loader::timesstamp(std::string const& filename) const {
    return fs::last_write_time(filename);
}

} } // namespace eda.util
