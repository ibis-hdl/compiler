#pragma once

#include <eda/vhdl/ast/util/position_tagged.hpp>
#include <eda/vhdl/ast/util/variant.hpp>

#include <eda/vhdl/ast/node/attribute_name.hpp>
#include <eda/vhdl/ast/node/simple_expression.hpp>
#include <eda/vhdl/ast/node/keyword_token.hpp>

namespace eda::vhdl::ast {

using range_attribute_name = ast::attribute_name;

struct range_expression : position_tagged {
    ast::simple_expression lhs;
    ast::keyword_token direction;
    ast::simple_expression rhs;
};

struct range : variant<range_attribute_name, range_expression> {
    using base_type::base_type;
    using base_type::operator=;
};

}  // namespace eda::vhdl::ast
