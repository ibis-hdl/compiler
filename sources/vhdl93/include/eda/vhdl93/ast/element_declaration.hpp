/*
 * element_declaration.hpp
 *
 *  Created on: 09.06.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_ELEMENT_DECLARATION_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_ELEMENT_DECLARATION_HPP_


#include <eda/vhdl93/ast/util/namespace_alias.hpp>

#include <eda/vhdl93/ast/identifier_list.hpp>
#include <eda/vhdl93/ast/element_subtype_definition.hpp>


namespace eda { namespace vhdl93 { namespace ast {


struct element_declaration : position_tagged
{
    ast::identifier_list            identifier_list;
    ast::element_subtype_definition element_subtype_definition;
};


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_ELEMENT_DECLARATION_HPP_ */
