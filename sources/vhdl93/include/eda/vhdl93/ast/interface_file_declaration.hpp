/*
 * interface_file_declaration.hpp
 *
 *  Created on: 07.06.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_INTERFACE_FILE_DECLARATION_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_INTERFACE_FILE_DECLARATION_HPP_


#include <eda/vhdl93/ast/namespace_alias.hpp>
#include <eda/vhdl93/ast/position_tagged.hpp>

#include <eda/vhdl93/ast/identifier_list.hpp>
#include <eda/vhdl93/ast/subtype_indication.hpp>


namespace eda { namespace vhdl93 { namespace ast {


struct interface_file_declaration : position_tagged
{
    ast::identifier_list                identifier_list;
    ast::subtype_indication             subtype_indication;
};


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_INTERFACE_FILE_DECLARATION_HPP_ */
