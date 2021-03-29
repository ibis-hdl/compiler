#pragma once

#include <limits>

namespace eda::vhdl::ast {

/**
 * Tagged AST node
 *
 * Use this to annotate an AST with the iterator position. These ids are used
 * as a key to the position_cache (below) and marks the start and end of an AST
 * node.
 */
struct position_tagged {
    using tag_type = std::size_t;

    static constexpr tag_type MAX_ID = std::numeric_limits<tag_type>::max();

    bool is_tagged() const { return pos_id != MAX_ID && file_id != MAX_ID; }

    tag_type file_id{ MAX_ID };
    tag_type pos_id{ MAX_ID };
};

}  // namespace eda::vhdl::ast
