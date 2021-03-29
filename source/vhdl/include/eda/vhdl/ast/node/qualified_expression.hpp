#pragma once

#include <eda/vhdl/ast/util/position_tagged.hpp>
#include <eda/vhdl/ast/util/variant.hpp>

#include <eda/vhdl/ast/util/nullary.hpp>
#include <eda/vhdl/ast/node/aggregate.hpp>
#include <eda/vhdl/ast/node/expression.hpp>
#include <eda/vhdl/ast/node/name.hpp>

namespace eda::vhdl::ast {

struct qualified_expression : position_tagged {
    ast::name type_mark;
    variant<ast::nullary, ast::expression, ast::aggregate> aggregate_or_expression;
};

}  // namespace eda::vhdl::ast
