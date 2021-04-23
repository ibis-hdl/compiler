#pragma once

#include <ibis/vhdl/ast/node/identifier.hpp>
#include <vector>

namespace ibis::vhdl::ast {

struct identifier_list : std::vector<ast::identifier> {
};

}  // namespace ibis::vhdl::ast
