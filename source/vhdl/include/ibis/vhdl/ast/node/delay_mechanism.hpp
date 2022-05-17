#pragma once

#include <ibis/vhdl/ast/util/position_tagged.hpp>

#include <ibis/vhdl/ast/node/expression.hpp>
#include <ibis/vhdl/ast/node/keyword_token.hpp>
#include <ibis/vhdl/ast/util/optional.hpp>

namespace ibis::vhdl::ast {

struct delay_mechanism : position_tagged {
    optional<ast::expression> time_expression;  // [REJECT ...]
    ast::keyword_token delay_type;              // [TRANSPORT|INERTIAL]
};

}  // namespace ibis::vhdl::ast

//
// Support Spirit.X3's attribute handling.
// FixMe: What about overloading node's operator=() to avoid x3::move_to?
//
namespace boost::spirit::x3::traits {

inline void move_to(ibis::vhdl::ast::keyword_token delay_type,
                    ibis::vhdl::ast::delay_mechanism& delay_mechanism)
{
    delay_mechanism.delay_type = delay_type;
}

}  // namespace boost::spirit::x3::traits
