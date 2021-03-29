#pragma once

#include <eda/vhdl/ast/util/position_tagged.hpp>

#include <eda/vhdl/ast/node/name.hpp>
#include <eda/vhdl/ast/node/expression.hpp>

namespace eda::vhdl::ast {

struct type_conversion : position_tagged {
    ast::name type_mark;
    ast::expression expression;
};

}  // namespace eda::vhdl::ast
