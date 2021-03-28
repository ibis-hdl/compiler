/*
 * element_declaration.hpp
 *
 *  Created on: 09.06.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_ELEMENT_DECLARATION_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_ELEMENT_DECLARATION_HPP_


#include <eda/vhdl/ast/util/position_tagged.hpp>

#include <eda/vhdl/ast/node/identifier_list.hpp>
#include <eda/vhdl/ast/node/subtype_indication.hpp>


namespace eda { namespace vhdl { namespace ast {


struct element_declaration : position_tagged
{
    ast::identifier_list            identifier_list;
    ast::subtype_indication         element_subtype_definition;
};


} } } // namespace eda.vhdl.ast


#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_ELEMENT_DECLARATION_HPP_ */
