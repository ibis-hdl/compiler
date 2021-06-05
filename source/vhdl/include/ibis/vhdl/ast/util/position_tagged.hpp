#pragma once

#include <limits>

#include <strong_type/strong_type.hpp>

namespace ibis::vhdl::ast {

///
/// Tagged AST node
///
/// Use this to annotate an AST with the iterator position. These ids are used
/// as a key to the position_cache (below) and marks the start and end of an AST
/// node.
///
struct position_tagged {
    /// the basic underlaying type
    using base_tag_type = std::size_t;

    /// The strong type of file id. This type is opaque to prevent unwanted allocation by accident
    /// or chance, since this type is also used outside the AST node and position_cache.
    using file_tag_type = strong::type<base_tag_type, struct position_tagged_, strong::ordered>;

    /// Type of position, used internally, so no need for opaque type.
    using pos_tag_type = base_tag_type;

    /// The max. ID value of file_id respectively pod_id.
    static constexpr base_tag_type MAX_ID = std::numeric_limits<base_tag_type>::max();

    /// return true if the node is tagged, false otherwise.
    bool is_tagged() const { return pos_id != MAX_ID && value_of(file_id) != MAX_ID; }

    /// The file ID (handle) used by position_cache.
    file_tag_type file_id{ MAX_ID };

    /// The position ID of tagged iterator range.
    pos_tag_type pos_id{ MAX_ID };
};

}  // namespace ibis::vhdl::ast
