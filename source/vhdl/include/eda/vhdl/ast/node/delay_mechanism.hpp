#pragma once

#include <eda/vhdl/ast/util/position_tagged.hpp>

#include <eda/vhdl/ast/node/expression.hpp>
#include <eda/vhdl/ast/node/keyword_token.hpp>
#include <eda/vhdl/ast/util/optional.hpp>

namespace eda::vhdl::ast {

struct delay_mechanism : position_tagged {
    optional<ast::expression> time_expression;  // [REJECT ...]
    ast::keyword_token delay_type;              // [TRANSPORT|INERTIAL]
};

}  // namespace eda::vhdl::ast

/*
 * Support Spirit.X3's attribute handling.
 * FixMe: What about overloading node's operator=() to avoid x3::move_to?
 */
namespace boost::spirit::x3::traits {

static inline void move_to(eda::vhdl::ast::keyword_token delay_type,
                           eda::vhdl::ast::delay_mechanism& delay_mechanism)
{
    delay_mechanism.delay_type = delay_type;
}

}  // namespace boost::spirit::x3::traits
