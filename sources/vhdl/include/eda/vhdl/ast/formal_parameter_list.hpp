/*
 * formal_parameter_list.hpp
 *
 *  Created on: 07.06.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_FORMAL_PARAMETER_LIST_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_FORMAL_PARAMETER_LIST_HPP_


#include <eda/vhdl/ast/interface_list.hpp>


namespace eda { namespace vhdl { namespace ast {


// formal_parameter_list ::= parameter_interface_list
using formal_parameter_list = interface_list;


} } } // namespace eda.vhdl.ast


#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_FORMAL_PARAMETER_LIST_HPP_ */
