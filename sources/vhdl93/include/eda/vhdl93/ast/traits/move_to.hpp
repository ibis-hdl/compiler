/*
 * move_to.hpp
 *
 *  Created on: 20.05.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_TRAITS_MOVE_TO_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_TRAITS_MOVE_TO_HPP_


#include <eda/vhdl93/ast/delay_mechanism.hpp>


namespace boost { namespace spirit { namespace x3 { namespace traits {


using delay_mechanism = eda::vhdl93::ast::delay_mechanism;


inline void
move_to(delay_mechanism::delay_type type, delay_mechanism& dest)
{
    dest.type = type;
}


} } } } // boost.spirit.x3.traits


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_TRAITS_MOVE_TO_HPP_ */
