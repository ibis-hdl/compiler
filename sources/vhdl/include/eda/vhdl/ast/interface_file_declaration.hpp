/*
 * interface_file_declaration.hpp
 *
 *  Created on: 07.06.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_INTERFACE_FILE_DECLARATION_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_INTERFACE_FILE_DECLARATION_HPP_


#include <eda/vhdl/ast/identifier_list.hpp>
#include <eda/vhdl/ast/subtype_indication.hpp>
#include <eda/vhdl/ast/util/namespace_alias.hpp>
#include <eda/vhdl/ast/util/position_tagged.hpp>


namespace eda { namespace vhdl { namespace ast {


struct interface_file_declaration : position_tagged
{
    ast::identifier_list                identifier_list;
    ast::subtype_indication             subtype_indication;
};


} } } // namespace eda.vhdl.ast


#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_INTERFACE_FILE_DECLARATION_HPP_ */
