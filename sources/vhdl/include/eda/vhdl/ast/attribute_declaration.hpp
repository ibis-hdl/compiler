/*
 * attribute_declaration.hpp
 *
 *  Created on: 14.05.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_ATTRIBUTE_DECLARATION_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_ATTRIBUTE_DECLARATION_HPP_


#include <eda/vhdl/ast/util/namespace_alias.hpp>
#include <eda/vhdl/ast/util/position_tagged.hpp>

#include <eda/vhdl/ast/identifier.hpp>
#include <eda/vhdl/ast/type_mark.hpp>


namespace eda { namespace vhdl { namespace ast {


struct attribute_declaration : position_tagged
{
    ast::identifier             identifier;
    ast::type_mark              type_mark;
};


} } } // namespace eda.vhdl.ast


#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_ATTRIBUTE_DECLARATION_HPP_ */
