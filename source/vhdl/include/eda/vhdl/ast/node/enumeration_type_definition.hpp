#pragma once

#include <eda/vhdl/ast/node/enumeration_literal.hpp>
#include <vector>

namespace eda::vhdl::ast {

struct enumeration_type_definition : std::vector<enumeration_literal> {
};

}  // namespace eda::vhdl::ast
