/*
 * interface_constant_declaration.hpp
 *
 *  Created on: 07.06.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_INTERFACE_CONSTANT_DECLARATION_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_INTERFACE_CONSTANT_DECLARATION_HPP_


#include <eda/vhdl93/ast/namespace_alias.hpp>
#include <eda/vhdl93/ast/position_tagged.hpp>

#include <eda/vhdl93/ast/identifier_list.hpp>
#include <eda/vhdl93/ast/subtype_indication.hpp>
#include <eda/vhdl93/ast/expression.hpp>
#include <boost/optional.hpp>


namespace eda { namespace vhdl93 { namespace ast {


struct interface_constant_declaration : position_tagged
{
    bool                                CONSTANT;
    ast::identifier_list                identifier_list;
    bool                                IN;
    ast::subtype_indication             subtype_indication;
    boost::optional<ast::expression>    static_expression;
};


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_INTERFACE_CONSTANT_DECLARATION_HPP_ */
