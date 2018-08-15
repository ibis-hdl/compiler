/*
 * interface_list.hpp
 *
 *  Created on: 07.06.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_INTERFACE_LIST_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_INTERFACE_LIST_HPP_


#include <eda/vhdl/ast/node/interface_declaration.hpp>
#include <vector>


namespace eda { namespace vhdl { namespace ast {


// only used in context of interface_list
using interface_element = ast::interface_declaration;


struct interface_list : std::vector<ast::interface_element> { };


} } } // namespace eda.vhdl.ast


#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_INTERFACE_LIST_HPP_ */
