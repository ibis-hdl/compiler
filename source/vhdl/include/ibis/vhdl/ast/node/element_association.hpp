#pragma once

#include <ibis/vhdl/ast/util/position_tagged.hpp>

#include <ibis/vhdl/ast/node/choices.hpp>
#include <ibis/vhdl/ast/node/expression.hpp>

namespace ibis::vhdl::ast {

struct element_association : position_tagged {
    ast::choices choices;
    ast::expression expression;
};

}  // namespace ibis::vhdl::ast
