#pragma once

#include <ibis/vhdl/ast/node/interface_declaration.hpp>
#include <vector>

namespace ibis::vhdl::ast {

// only used in context of interface_list
using interface_element = ast::interface_declaration;

struct interface_list : std::vector<ast::interface_element> {};

}  // namespace ibis::vhdl::ast
