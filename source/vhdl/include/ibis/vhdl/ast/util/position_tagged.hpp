//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-or-later
//

#pragma once

#include <limits>

#include <strong_type/strong_type.hpp>

namespace ibis::vhdl::ast {

///
/// Tagged AST node
///
/// Use this to annotate an AST with the iterator position. These ids are used
/// as a key to the @ref position_cache and marks the start and end of an AST node.
///
/// FixMe: Using the right approach with class and read-only access by function to member file_id
/// and position_id the compile time of grammar.cpp increases dramatically. Maybe due to use of
/// opaque type strong::type??
struct position_tagged {
    /// the basic underlying type
    using underlying_type = std::size_t;

    /// The max. ID value of file_id respectively pod_id.
    static constexpr underlying_type MAX_ID = std::numeric_limits<underlying_type>::max();

    /// The strong type of file id. This type is opaque to prevent unwanted allocation by accident
    /// or chance, since this type is also used outside the AST node and position_cache.
    using file_id_type = strong::type<underlying_type, struct position_tagged_,  // --
                                      strong::ordered, strong::equality>;

    /// Type of position, used internally, so no need for opaque type.
    using position_id_type = underlying_type;

    /// return true if the node is tagged, false otherwise.
    bool is_tagged() const { return position_id != MAX_ID && value_of(file_id) != MAX_ID; }

    /// The file ID (handle) used by position_cache.
    file_id_type file_id{ MAX_ID };

    /// The position ID of tagged iterator range.
    position_id_type position_id{ MAX_ID };
};

}  // namespace ibis::vhdl::ast
