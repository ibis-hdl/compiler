#pragma once

#include <ibis/vhdl/ast/util/position_tagged.hpp>

#include <ibis/vhdl/ast/node/label.hpp>
#include <ibis/vhdl/ast/node/expression.hpp>
#include <ibis/vhdl/ast/util/optional.hpp>

namespace ibis::vhdl::ast {

struct return_statement : position_tagged {
    optional<ast::label> label;
    optional<ast::expression> expression;
};

}  // namespace ibis::vhdl::ast
