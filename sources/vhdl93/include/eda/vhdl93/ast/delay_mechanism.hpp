/*
 * delay_mechanism.hpp
 *
 *  Created on: 16.05.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_DELAY_MECHANISM_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_DELAY_MECHANISM_HPP_


#include <eda/vhdl93/ast/namespace_alias.hpp>
#include <eda/vhdl93/ast/position_tagged.hpp>

#include <eda/vhdl93/ast/expression.hpp>
#include <boost/optional.hpp>


namespace eda { namespace vhdl93 { namespace ast {


struct delay_mechanism : position_tagged
{
    enum class delay_type { TRANSPORT_DELAY, INERTIAL_DELAY };

    boost::optional<ast::expression>    time_expression; // [REJECT ...]
    delay_mechanism::delay_type         type;
};


} } } // namespace eda.vhdl93.ast


namespace boost { namespace spirit { namespace x3 { namespace traits {

using delay_mechanism = eda::vhdl93::ast::delay_mechanism;

inline void
move_to(delay_mechanism::delay_type type, delay_mechanism& dest)
{
    dest.type = type;
}

} } } } // boost.spirit.x3.traits


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_DELAY_MECHANISM_HPP_ */
