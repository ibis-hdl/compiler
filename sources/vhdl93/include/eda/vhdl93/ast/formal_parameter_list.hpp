/*
 * formal_parameter_list.hpp
 *
 *  Created on: 07.06.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_FORMAL_PARAMETER_LIST_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_FORMAL_PARAMETER_LIST_HPP_


#include <eda/vhdl93/ast/util/namespace_alias.hpp>

#include <eda/vhdl93/ast/interface_list.hpp>
#include <vector>


namespace eda { namespace vhdl93 { namespace ast {


// formal_parameter_list ::= parameter_interface_list
using formal_parameter_list = interface_list;


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_FORMAL_PARAMETER_LIST_HPP_ */
