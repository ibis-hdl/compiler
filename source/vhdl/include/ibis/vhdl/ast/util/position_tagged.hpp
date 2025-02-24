//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-or-later
//

#pragma once

#include <ibis/util/strong_type.hpp>

#include <cstddef>
#include <limits>

namespace ibis::vhdl::ast {

///
/// Tagged AST node
///
/// Use this to annotate an AST with the iterator position. These ids are used
/// as a key to the @ref position_cache and marks the start and end of an AST node.
///
class position_tagged {
    using underlying_type = std::size_t;

public:
    /// The strong type of file id. This type is opaque to prevent unwanted allocation by accident
    /// or chance, since this type is also used outside the AST node (e.g. position_cache).
    using file_id_type = ibis::util::strong_type<underlying_type, struct position_tagged_file_id>;

    /// The max. ID value of file_id, also identifies uninitialized id
    static constexpr file_id_type MAX_FILE_ID{
        std::numeric_limits<file_id_type::value_type>::max()
    };

public:
    /// Type of position, only used internally, so no need for opaque type.
    using position_id_type = underlying_type;  // ToDo also position_id_type as strong_type

    /// The max. ID value of position_id, also identifies uninitialized id
    static constexpr position_id_type MAX_POSITION_ID{
        std::numeric_limits<position_id_type>::max()
    };

public:
    /// return true if the node is tagged, false otherwise.
    // ToDo: Check/Consider, if assumption of is_tagged() is correct: both id are always tagged!
    bool is_tagged() const { return position_id != MAX_POSITION_ID && file_id != MAX_FILE_ID; }

public:
    /// The file ID (handle) used by position_cache.
    file_id_type file_id{ MAX_FILE_ID };

    /// The position ID of tagged iterator range.
    position_id_type position_id{ MAX_POSITION_ID };
};

}  // namespace ibis::vhdl::ast
