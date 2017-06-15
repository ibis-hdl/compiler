/*
 * interface_signal_declaration.hpp
 *
 *  Created on: 07.06.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_INTERFACE_SIGNAL_DECLARATION_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_INTERFACE_SIGNAL_DECLARATION_HPP_


#include <eda/vhdl93/ast/util/namespace_alias.hpp>
#include <eda/vhdl93/ast/position_tagged.hpp>

#include <eda/vhdl93/ast/identifier_list.hpp>
#include <eda/vhdl93/ast/keyword_token.hpp>
#include <eda/vhdl93/ast/subtype_indication.hpp>
#include <eda/vhdl93/ast/expression.hpp>
#include <eda/vhdl93/ast/util/optional.hpp>


namespace eda { namespace vhdl93 { namespace ast {


struct interface_signal_declaration : position_tagged
{
    bool                                SIGNAL;
    ast::identifier_list                identifier_list;
    optional<ast::keyword_token>        mode;
    ast::subtype_indication             subtype_indication;
    bool                                BUS;
    optional<ast::expression>           static_expression;

    interface_signal_declaration()
    : SIGNAL{}, BUS{}
    { }
};


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_INTERFACE_SIGNAL_DECLARATION_HPP_ */
