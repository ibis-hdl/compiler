#pragma once

#include <eda/vhdl/ast/util/position_tagged.hpp>

#include <eda/vhdl/ast/node/operator_token.hpp>
#include <eda/vhdl/ast/node/simple_expression.hpp>
#include <eda/vhdl/ast/util/optional.hpp>

namespace eda::vhdl::ast {

struct shift_expression : position_tagged {
    struct chunk {
        operator_token shift_operator;
        ast::simple_expression simple_expression;
    };

    ast::simple_expression simple_expression;
    optional<chunk> rest;
};

}  // namespace eda::vhdl::ast
