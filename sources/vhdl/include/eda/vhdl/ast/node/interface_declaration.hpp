/*
 * interface_declaration.hpp
 *
 *  Created on: 07.06.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_INTERFACE_DECLARATION_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_INTERFACE_DECLARATION_HPP_


#include <eda/vhdl/ast/util/variant.hpp>

#include <eda/vhdl/ast/util/nullary.hpp>
#include <eda/vhdl/ast/node/interface_constant_declaration.hpp>
#include <eda/vhdl/ast/node/interface_file_declaration.hpp>
#include <eda/vhdl/ast/node/interface_signal_declaration.hpp>
#include <eda/vhdl/ast/node/interface_variable_declaration.hpp>


namespace eda { namespace vhdl { namespace ast {


using interface_declaration = variant<
    nullary,
    interface_constant_declaration,
    interface_signal_declaration,
    interface_variable_declaration,
    interface_file_declaration
>;


} } } // namespace eda.vhdl.ast


#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_INTERFACE_DECLARATION_HPP_ */