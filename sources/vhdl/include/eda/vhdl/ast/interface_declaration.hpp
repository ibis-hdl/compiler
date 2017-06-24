/*
 * interface_declaration.hpp
 *
 *  Created on: 07.06.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_INTERFACE_DECLARATION_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_INTERFACE_DECLARATION_HPP_


#include <boost/spirit/home/x3/support/ast/variant.hpp>
#include <eda/vhdl/ast/interface_constant_declaration.hpp>
#include <eda/vhdl/ast/interface_file_declaration.hpp>
#include <eda/vhdl/ast/interface_signal_declaration.hpp>
#include <eda/vhdl/ast/interface_variable_declaration.hpp>
#include <eda/vhdl/ast/util/namespace_alias.hpp>
#include <eda/vhdl/ast/util/nullary.hpp>


namespace eda { namespace vhdl { namespace ast {


struct interface_declaration : x3::variant<
    nullary,
    interface_constant_declaration,
    interface_signal_declaration,
    interface_variable_declaration,
    interface_file_declaration
>
{
    using base_type::base_type;
    using base_type::operator=;
};


} } } // namespace eda.vhdl.ast


#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_INTERFACE_DECLARATION_HPP_ */
