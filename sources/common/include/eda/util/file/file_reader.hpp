/*
 * file_reader.hpp
 *
 *  Created on: 31.07.2018
 *      Author: olaf
 */

#ifndef SOURCES_COMMON_INCLUDE_EDA_UTIL_FILE_FILE_READER_HPP_
#define SOURCES_COMMON_INCLUDE_EDA_UTIL_FILE_FILE_READER_HPP_

#include <string>
#include <vector>
#include <algorithm>
#include <optional>

#include <ctime>

#include <iosfwd>


namespace boost { namespace filesystem {
	struct path;
} }

namespace eda {
	class settings;
}


namespace eda { namespace util {


class file_loader
{
public:
	explicit file_loader(std::ostream& os_, eda::settings const& setting);

    file_loader(file_loader const&) = delete;
    file_loader const& operator=(file_loader const&) = delete;

public:
    bool exist_file(std::string const& filename) const;

    bool exist_files(std::vector<std::string> const& file_list) const {

        return std::all_of(file_list.begin(), file_list.end(),
                           [this](std::string const& f) { return exist_file(f); });
    }

    // concept at https://wandbox.org/permlink/n0WLazXzJ61WNQg9
    bool unique_files(std::vector<std::string> const& file_list) const;

    /* file read method using rdbuf()
     * \see[How to read in a file in C++](
     * https://insanecoding.blogspot.com/2011/11/how-to-read-in-file-in-c.html) */
    std::optional<std::string> read_file(std::string const& filename) const;

    /* file read method using rdbuf()
     * \see[How to read in a file in C++](
     * https://insanecoding.blogspot.com/2011/11/how-to-read-in-file-in-c.html) */
    std::optional<std::string> read_file(boost::filesystem::path const& filename) const;

    /* alternative read method using seek
     * \see[How to read in a file in C++](
     * https://insanecoding.blogspot.com/2011/11/how-to-read-in-file-in-c.html) */
    std::optional<std::string> read_file_alt(std::string const& filename) const;

    /* time point of last write occurrence. If the time cannot be determined,
     *  returns (std::time_t)(-1). */
    std::time_t timesstamp(std::string const& filename) const;

private:
    std::ostream& 									os;
    bool const										quiet;
};


} } // namespace eda.util


#endif /* SOURCES_COMMON_INCLUDE_EDA_UTIL_FILE_FILE_READER_HPP_ */
