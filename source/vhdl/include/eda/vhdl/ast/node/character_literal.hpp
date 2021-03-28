/*
 * character_literal.hpp
 *
 *  Created on: 22.03.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_CHARACTER_LITERAL_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_CHARACTER_LITERAL_HPP_


#include <eda/vhdl/ast/util/position_tagged.hpp>


namespace eda { namespace vhdl { namespace ast {


struct character_literal : position_tagged
{
    char    literal;
};


} } } // namespace eda.vhdl.ast


#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_CHARACTER_LITERAL_HPP_ */
