#pragma once

#include <eda/vhdl/ast/util/position_tagged.hpp>

#include <eda/vhdl/ast/node/operator_token.hpp>
#include <eda/vhdl/ast/node/shift_expression.hpp>
#include <eda/vhdl/ast/util/optional.hpp>

namespace eda::vhdl::ast {

struct relation : position_tagged {
    struct chunk {
        operator_token relational_operator;
        ast::shift_expression shift_expression;
    };

    ast::shift_expression shift_expression;
    optional<chunk> rest;
};

}  // namespace eda::vhdl::ast
