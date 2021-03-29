#pragma once

#include <eda/vhdl/ast/util/position_tagged.hpp>

#include <eda/vhdl/ast/node/choices.hpp>
#include <eda/vhdl/ast/node/expression.hpp>

namespace eda::vhdl::ast {

struct element_association : position_tagged {
    ast::choices choices;
    ast::expression expression;
};

}  // namespace eda::vhdl::ast
