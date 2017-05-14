/*
 * attribute_declaration.hpp
 *
 *  Created on: 14.05.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_ATTRIBUTE_DECLARATION_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_ATTRIBUTE_DECLARATION_HPP_


#include <eda/vhdl93/ast/namespace_alias.hpp>
#include <eda/vhdl93/ast/position_tagged.hpp>

#include <eda/vhdl93/ast/identifier.hpp>
#include <eda/vhdl93/ast/type_mark.hpp>


namespace eda { namespace vhdl93 { namespace ast {


struct attribute_declaration : position_tagged
{
    ast::identifier             identifier;
    ast::type_mark              type_mark;
};


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_ATTRIBUTE_DECLARATION_HPP_ */
