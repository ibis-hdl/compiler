#pragma once

#include <ibis/vhdl/ast/node/range.hpp>

namespace ibis::vhdl::ast {

// Following the BNF, the range_constraint differs only from range_constraint
// by the leading keyword RANGE, hence from AST's point of view it's simply a
// range ...
// Further, a range as such is used otherwise in the BNF as specifier for other
// rules.
// Hence, the BNF is reading much simpler by defining the range_constraint as
// an own AST node (syntactical sugar).
using range_constraint = ast::range;

}  // namespace ibis::vhdl::ast
