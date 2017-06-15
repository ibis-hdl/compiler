/*
 * interface_declaration.hpp
 *
 *  Created on: 07.06.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_INTERFACE_DECLARATION_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_INTERFACE_DECLARATION_HPP_


#include <eda/vhdl93/ast/util/namespace_alias.hpp>

#include <eda/vhdl93/ast/util/nullary.hpp>
#include <eda/vhdl93/ast/interface_constant_declaration.hpp>
#include <eda/vhdl93/ast/interface_signal_declaration.hpp>
#include <eda/vhdl93/ast/interface_variable_declaration.hpp>
#include <eda/vhdl93/ast/interface_file_declaration.hpp>

#include <boost/spirit/home/x3/support/ast/variant.hpp>


namespace eda { namespace vhdl93 { namespace ast {


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


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_INTERFACE_DECLARATION_HPP_ */
