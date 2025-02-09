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
#include <functional>
#include <cstddef>
#include <cassert>

namespace ibis::util {

///
/// Store a filename and with its contents and maps this tuple to an ID for later use when tagging
/// e.g. the AST etc.
///
class file_mapper {
private:
    ///
    /// The (internal) data type for registry
    ///
    struct entry {
        entry() = default;
        entry(std::string&& filename_, std::string&& contents_)
            : filename{ std::move(filename_) }
            , contents{ std::move(contents_) }
        {
        }
        // NOLINTBEGIN(misc-non-private-member-variables-in-classes)
        std::string filename;  // Todo Check on use of fs::path as filename argument
        std::string contents;
        // NOLINTEND(misc-non-private-member-variables-in-classes)
    };

    using file_registry_type = std::vector<entry>;

    file_registry_type file_registry;

private:
    static constexpr auto MAX_ID = vhdl::ast::position_tagged::MAX_FILE_ID;

public:
    using file_id_type = ibis::vhdl::ast::position_tagged::file_id_type;

public:
    class current_file;

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
    /// @return A proxy which identifies the tuple of 'filename' and 'contents' which
    /// can be referred later.
    ///
    current_file add_file(std::string&& filename, std::string&& contents);

    ///
    /// @overload add_file(std::string_view filename, std::string&& contents)
    ///
    current_file add_file(std::string_view filename, std::string_view contents);

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

private:
    ///
    /// Get an ID
    ///
    std::size_t next_id() const { return file_registry.size(); }
};

///
/// Current file proxy, holding information related to current_file_id
///
class file_mapper::current_file {
    std::reference_wrapper<file_mapper> file_mapper_ref;
    file_id_type /* const */ current_file_id;

public:
    current_file(std::reference_wrapper<file_mapper> ref_self, file_id_type id)
        : file_mapper_ref{ ref_self }
        , current_file_id{ id }
    {
    }

    current_file() = delete;
    ~current_file() = default;

    current_file(current_file&&) = default;
    current_file& operator=(current_file&&) = default;

    // non-copyable, otherwise the assignment of ID with file/contents may go wrong
    current_file(current_file const&) = delete;
    current_file& operator=(current_file const&) = delete;

public:
    file_id_type id() const { return current_file_id; }
    std::string_view file_name() const { return file_mapper_ref.get().file_name(this->id()); }
    std::string_view file_contents() const
    {
        return file_mapper_ref.get().file_contents(this->id());
    }
};

inline file_mapper::current_file file_mapper::add_file(std::string&& filename,
                                                       std::string&& contents)
{
    file_id_type const current_file_id{ next_id() };

    // ToDo OOM error handling (scope_exit would be overkill)
    file_registry.emplace_back(std::move(filename), std::move(contents));

    return { std::ref(*this), current_file_id };
}

inline file_mapper::current_file file_mapper::add_file(std::string_view filename,
                                                       std::string_view contents)
{
    return add_file(std::string{ filename }, std::string{ contents });
}

}  // namespace ibis::util
