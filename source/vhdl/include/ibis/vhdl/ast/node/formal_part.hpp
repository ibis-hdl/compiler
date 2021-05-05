#pragma once

#include <ibis/vhdl/ast/util/position_tagged.hpp>

#include <vector>

namespace ibis::vhdl::ast {

struct name;

/// formal_part                                                 [LRM93 §4.3.2.2]
///
/// @code{.bnf}
/// formal_part ::=
///       formal_designator
///     | function_name ( formal_designator )
///     | type_mark ( formal_designator )
/// @endcode
struct formal_part : position_tagged {
    std::vector<ast::name> context_tied_names;
};

}  // namespace ibis::vhdl::ast
