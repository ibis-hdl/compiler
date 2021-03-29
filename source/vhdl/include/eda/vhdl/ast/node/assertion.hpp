#pragma once

#include <eda/vhdl/ast/util/position_tagged.hpp>

#include <eda/vhdl/ast/node/condition.hpp>
#include <eda/vhdl/ast/node/expression.hpp>
#include <eda/vhdl/ast/util/optional.hpp>

namespace eda::vhdl::ast {

struct assertion : position_tagged {
    ast::condition condition;
    optional<ast::expression> report;
    optional<ast::expression> severity;
};

}  // namespace eda::vhdl::ast
