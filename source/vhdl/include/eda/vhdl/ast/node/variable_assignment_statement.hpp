#pragma once

#include <eda/vhdl/ast/util/position_tagged.hpp>

#include <eda/vhdl/ast/node/label.hpp>
#include <eda/vhdl/ast/node/target.hpp>
#include <eda/vhdl/ast/node/expression.hpp>
#include <eda/vhdl/ast/util/optional.hpp>

namespace eda::vhdl::ast {

struct variable_assignment_statement : position_tagged {
    optional<ast::label> label;
    ast::target target;
    ast::expression expression;
};

}  // namespace eda::vhdl::ast
