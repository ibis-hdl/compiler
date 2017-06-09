/*
 * secondary_unit_declaration.hpp
 *
 *  Created on: 09.06.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_SECONDARY_UNIT_DECLARATION_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_SECONDARY_UNIT_DECLARATION_HPP_


#include <eda/vhdl93/ast/namespace_alias.hpp>
#include <eda/vhdl93/ast/position_tagged.hpp>

#include <eda/vhdl93/ast/identifier.hpp>
#include <eda/vhdl93/ast/physical_literal.hpp>


namespace eda { namespace vhdl93 { namespace ast {


struct secondary_unit_declaration : position_tagged
{
    ast::identifier             identifier;
    ast::physical_literal       physical_literal;
};


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_SECONDARY_UNIT_DECLARATION_HPP_ */
