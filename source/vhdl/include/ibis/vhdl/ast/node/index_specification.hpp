#pragma once

#include <ibis/vhdl/ast/util/variant.hpp>

#include <ibis/vhdl/ast/util/nullary.hpp>
#include <ibis/vhdl/ast/node/discrete_range.hpp>
#include <ibis/vhdl/ast/node/expression.hpp>

namespace ibis::vhdl::ast {

struct index_specification
    : variant<ast::nullary, ast::discrete_range,
              ast::expression  // static_expression
              > {
    using base_type::base_type;
    using base_type::operator=;
};

}  // namespace ibis::vhdl::ast
