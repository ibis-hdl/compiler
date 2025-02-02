//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-or-later
//

#pragma once

#include <algorithm>
#include <ctime>
#include <iosfwd>
#include <optional>
#include <string>
#include <vector>
#include <expected>
#include <filesystem>

#include <ibis/namespace_alias.hpp>  // IWYU pragma: keep

namespace ibis {
namespace fs = std::filesystem;
}

namespace ibis::util {

///
/// Utility class for file reading.
///
class file_loader {
public:
    ///
    /// Construct a new file loader object.
    ///
    /// @param os_ the stream to write error messages on failure.
    ///
    /// The quiteness is gathered from settings "quiet".
    ///
    explicit file_loader(std::ostream& os_);

    ~file_loader() = default;

    file_loader(file_loader const&) = delete;
    file_loader const& operator=(file_loader const&) = delete;

    file_loader(file_loader&&) = delete;
    file_loader const& operator=(file_loader&&) = delete;

public:
    ///
    /// Check on existence of the file and if it is a regular file.
    ///
    /// @param filename The file to test
    /// @return true if it exist and is a regular file
    /// @return false otherwise
    ///
    bool exist_file(fs::path const& filename) const;

    ///
    /// Check on existence of the list of files and if they are regular files.
    ///
    /// @param file_list List of file to test
    /// @return true if all files pass @ref exist_file()
    /// @return false otherwise
    ///
    bool exist_files(std::vector<fs::path> const& file_list) const
    {
        return std::all_of(file_list.begin(), file_list.end(),
                           [this](fs::path const& f) { return exist_file(f); });
    }

    ///
    /// Detect duplicate files in the list and, if intended, prints the list. It detect duplicates
    /// even if the path notation is different, e.g. "/home/jail", "../jail".
    ///
    /// @param fs_path_list List of file to test
    /// @return true if the \p fs_path_list has unique files.
    /// @return false otherwise, prints the duplicates
    ///
    /// The implementation concept based on can be found at
    /// @see[Wandbox](https://wandbox.org/permlink/n0WLazXzJ61WNQg9)
    /// @todo The algorithm is O(n^2); using a hashmap may prevent this.
    ///
    bool unique_files(std::vector<fs::path> const& fs_path_list) const;

    ///
    /// file read method using rdbuf().
    ///
    /// @param filename the file to read into buffer string
    /// @return std::optional<std::string> on success with contents of the
    /// file in a string. Otherwise a default constructed std::optional.
    /// @see[How to read in a file in C++](
    /// https://insanecoding.blogspot.com/2011/11/how-to-read-in-file-in-c.html)
    ///
    std::expected<std::string, std::error_code> read_file(fs::path const& filename) const;

    ///
    /// alternative read method using seek().
    ///
    /// @param filename the file to read into buffer string
    /// @return std::optional<std::string> on success with contents of the
    /// file in a string. Otherwise a default constructed std::optional.
    /// @see [How to read in a file in C++](
    ///        https://insanecoding.blogspot.com/2011/11/how-to-read-in-file-in-c.html)
    /// @see [How do I read an entire file into a std::string in C++?](
    ///       https://stackoverflow.com/questions/116038/how-do-i-read-an-entire-file-into-a-stdstring-in-c)
    ///
    std::expected<std::string, std::error_code> read_file_alt(fs::path const& filename) const;

    ///
    /// Time point of last write occurrence. If the time cannot be determined, returns
    /// (std::time_t)(-1). This allows to skip files which are compiled before (and cached).
    ///
    std::time_t timesstamp(fs::path const& filename) const;

private:
    std::ostream& os;
    bool const quiet;
};

}  // namespace ibis::util
