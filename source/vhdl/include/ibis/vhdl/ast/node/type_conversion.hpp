#pragma once

#include <ibis/vhdl/ast/util/position_tagged.hpp>

#include <ibis/vhdl/ast/node/name.hpp>
#include <ibis/vhdl/ast/node/expression.hpp>

namespace ibis::vhdl::ast {

struct type_conversion : position_tagged {
    ast::name type_mark;
    ast::expression expression;
};

}  // namespace ibis::vhdl::ast
