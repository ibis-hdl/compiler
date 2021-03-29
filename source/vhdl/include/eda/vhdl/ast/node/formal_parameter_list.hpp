#pragma once

#include <eda/vhdl/ast/node/interface_list.hpp>

namespace eda::vhdl::ast {

// formal_parameter_list ::= parameter_interface_list
using formal_parameter_list = interface_list;

}  // namespace eda::vhdl::ast
