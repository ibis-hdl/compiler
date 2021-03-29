#pragma once

#include <eda/vhdl/ast/util/variant.hpp>

#include <eda/vhdl/ast/util/nullary.hpp>
#include <eda/vhdl/ast/node/discrete_range.hpp>
#include <eda/vhdl/ast/node/expression.hpp>

namespace eda::vhdl::ast {

struct index_specification
    : variant<ast::nullary, ast::discrete_range,
              ast::expression  // static_expression
              > {
    using base_type::base_type;
    using base_type::operator=;
};

}  // namespace eda::vhdl::ast
