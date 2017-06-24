/*
 * interface_variable_declaration.hpp
 *
 *  Created on: 07.06.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_INTERFACE_VARIABLE_DECLARATION_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_INTERFACE_VARIABLE_DECLARATION_HPP_


#include <eda/vhdl/ast/expression.hpp>
#include <eda/vhdl/ast/identifier_list.hpp>
#include <eda/vhdl/ast/keyword_token.hpp>
#include <eda/vhdl/ast/subtype_indication.hpp>
#include <eda/vhdl/ast/util/namespace_alias.hpp>
#include <eda/vhdl/ast/util/optional.hpp>
#include <eda/vhdl/ast/util/position_tagged.hpp>


namespace eda { namespace vhdl { namespace ast {


struct interface_variable_declaration : position_tagged
{
    bool                                VARIABLE;
    ast::identifier_list                identifier_list;
    optional<ast::keyword_token>        mode;
    ast::subtype_indication             subtype_indication;
    optional<ast::expression>           static_expression;

    interface_variable_declaration()
    : VARIABLE{}
    { }
};


} } } // namespace eda.vhdl.ast


#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_INTERFACE_VARIABLE_DECLARATION_HPP_ */
