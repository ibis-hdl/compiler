/*
 * file_reader.hpp
 *
 *  Created on: 31.07.2018
 *      Author: olaf
 */

#ifndef SOURCES_COMMON_INCLUDE_EDA_UTIL_FILE_FILE_READER_HPP_
#define SOURCES_COMMON_INCLUDE_EDA_UTIL_FILE_FILE_READER_HPP_

#include <eda/namespace_alias.hpp> // IWYU pragma: keep

#include <algorithm>
#include <ctime>
#include <iosfwd>
#include <optional>
#include <string>
#include <vector>

namespace boost {
namespace filesystem {

class path;

} // namespace filesystem
} // namespace boost

namespace eda {

class settings;

} // namespace eda

namespace eda {
namespace util {

class file_loader {
public:
    explicit file_loader(std::ostream& os_, eda::settings const& setting);
    ~file_loader() = default;

    file_loader(file_loader const&) = delete;
    file_loader const& operator=(file_loader const&) = delete;

    file_loader(file_loader&&) = delete;
    file_loader const& operator=(file_loader&&) = delete;

public:
    bool exist_file(std::string const& filename) const;

    bool exist_files(std::vector<std::string> const& file_list) const
    {

        return std::all_of(file_list.begin(), file_list.end(),
            [this](std::string const& f) { return exist_file(f); });
    }

    /**
     * Returns true, if the \p file_list has unique files. Otherwise prints the
     * duplicates and returns false.
     *
     * The implementation concept based on can be found at
     * \see[Wandbox}(https://wandbox.org/permlink/n0WLazXzJ61WNQg9)
     *
     * FixMe: The algorithm is O(n^2); using a hash may prevent this. */
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
    static std::optional<std::string> read_file_alt(std::string const& filename);

    /* Time point of last write occurrence. If the time cannot be determined,
     * returns (std::time_t)(-1).
     * This allows to skip files which are compiled before (and cached). */
    std::time_t timesstamp(std::string const& filename) const;

private:
    // clang-format off
    std::ostream&                                   os;
    bool const                                      quiet;
    // clang-format on
};

} // namespace util
} // namespace eda

#endif /* SOURCES_COMMON_INCLUDE_EDA_UTIL_FILE_FILE_READER_HPP_ */
