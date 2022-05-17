#pragma once

#include <ibis/vhdl/ast/node/enumeration_literal.hpp>
#include <vector>

namespace ibis::vhdl::ast {

struct enumeration_type_definition : std::vector<enumeration_literal> {};

}  // namespace ibis::vhdl::ast
