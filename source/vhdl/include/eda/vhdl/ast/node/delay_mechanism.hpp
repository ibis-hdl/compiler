/*
 * delay_mechanism.hpp
 *
 *  Created on: 16.05.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_DELAY_MECHANISM_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_DELAY_MECHANISM_HPP_


#include <eda/vhdl/ast/util/position_tagged.hpp>

#include <eda/vhdl/ast/node/expression.hpp>
#include <eda/vhdl/ast/node/keyword_token.hpp>
#include <eda/vhdl/ast/util/optional.hpp>


namespace eda { namespace vhdl { namespace ast {


struct delay_mechanism : position_tagged
{
    optional<ast::expression>           time_expression; // [REJECT ...]
    ast::keyword_token                  delay_type;     // [TRANSPORT|INERTIAL]

};


} } } // namespace eda.vhdl.ast


/*
 * Support Spirit.X3's attribute handling.
 * FixMe: What about overloading node's operator=() to avoid x3::move_to?
 */
namespace boost { namespace spirit { namespace x3 { namespace traits {

static inline void
move_to(eda::vhdl::ast::keyword_token delay_type, eda::vhdl::ast::delay_mechanism& delay_mechanism)
{
    delay_mechanism.delay_type = delay_type;
}

} } } } // boost.spirit.x3.traits


#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_DELAY_MECHANISM_HPP_ */
