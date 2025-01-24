//
// Copyright (c) 2017-2025 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-or-later
//

#pragma once

#include <ibis/vhdl/ast/util/position_tagged.hpp>

#include <string>
#include <string_view>
#include <vector>
#include <utility>
#include <cassert>
#include <cstdint>

namespace ibis::util {

///
/// Store a filename and with its contents and maps this tuple to an ID for later use when tagging
/// e.g. the AST etc.
///
class file_mapper {
    struct entry {
        entry() = default;
        entry(std::string_view filename_, std::string&& contents_)
            : filename{ filename_ }
            , contents{ std::move(contents_) }
        {
        }
        std::string filename;  // Todo Check on use of fs::path as filename argument
        std::string contents;
    };

    using file_registry_type = std::vector<entry>;

public:
    using file_id_type = vhdl::ast::position_tagged::file_id_type;

public:
    file_mapper() = default;
    ~file_mapper() = default;

    file_mapper(file_mapper&&) = default;
    file_mapper& operator=(file_mapper&&) = default;

    file_mapper(file_mapper const&) = delete;
    file_mapper& operator=(file_mapper const&) = delete;

public:
    std::size_t file_count() const { return file_registry.size(); }

public:
    ///
    /// Maps a filename to contents.
    ///
    /// @param filename The file name as is it's shown e.g. by the error handler
    /// @param contents String holding the file contents
    /// @return A file_id which identifies the tuple of 'filename' and 'contents' which
    /// can be referred later.
    ///
    file_id_type add_file(std::string_view filename, std::string&& contents)
    {
        file_id_type file_id{ next_id() };
        // ToDo OOM error handling (scope_exit would be overkill)
        file_registry.emplace_back(filename, std::move(contents));
        return file_id;
    }

    ///
    /// @overload proxy add_file(std::string_view filename, std::string&& contents)
    ///
    file_id_type add_file(std::string_view filename, std::string_view contents)
    {
        return add_file(filename, std::string{ contents });
    }

public:
    ///
    /// Get the file name.
    ///
    /// @param file_id ID of actually processed file.
    /// @return The filename as string view.
    ///
    std::string_view file_name(file_id_type file_id) const
    {
        assert(valid_id(file_id) && "file_id out of range!");
        return file_registry[file_id].filename;
    }

    ///
    /// Get the file contents.
    ///
    /// @param file_id ID of actually processed file.
    /// @return A string view representing of the file contents.
    ///
    std::string_view file_contents(file_id_type file_id) const
    {
        assert(valid_id(file_id) && "file_id out of range!");
        return file_registry[file_id].contents;
    }

public:
    ///
    /// Check if a given file ID is valid
    ///
    bool valid_id(file_id_type id) const { return std::cmp_less(id.get(), file_registry.size()); }

    ///
    /// Get an ID
    ///
    std::size_t next_id() const { return file_registry.size(); }

private:
    file_registry_type file_registry;
};

}  // namespace ibis::util
