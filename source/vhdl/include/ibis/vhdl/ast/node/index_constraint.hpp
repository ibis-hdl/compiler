#pragma once

#include <ibis/vhdl/ast/node/discrete_range.hpp>
#include <vector>

namespace ibis::vhdl::ast {

struct index_constraint : std::vector<ast::discrete_range> {};

}  // namespace ibis::vhdl::ast
