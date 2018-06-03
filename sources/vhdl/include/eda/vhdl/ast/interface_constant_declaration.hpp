/*
 * interface_constant_declaration.hpp
 *
 *  Created on: 07.06.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_INTERFACE_CONSTANT_DECLARATION_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_INTERFACE_CONSTANT_DECLARATION_HPP_


#include <eda/vhdl/ast/util/position_tagged.hpp>

#include <eda/vhdl/ast/expression.hpp>
#include <eda/vhdl/ast/identifier_list.hpp>
#include <eda/vhdl/ast/subtype_indication.hpp>
#include <eda/vhdl/ast/util/optional.hpp>


namespace eda { namespace vhdl { namespace ast {


struct interface_constant_declaration : position_tagged
{
    bool                                constant;
    ast::identifier_list                identifier_list;
    bool                                in;
    ast::subtype_indication             subtype_indication;
    optional<ast::expression>           static_expression;

    interface_constant_declaration()
    : constant{}, in{}
    { }
};


} } } // namespace eda.vhdl.ast


#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_INTERFACE_CONSTANT_DECLARATION_HPP_ */
