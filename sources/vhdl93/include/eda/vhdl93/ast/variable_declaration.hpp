/*
 * variable_declaration.hpp
 *
 *  Created on: 17.06.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_VARIABLE_DECLARATION_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_VARIABLE_DECLARATION_HPP_


#include <eda/vhdl93/ast/util/namespace_alias.hpp>
#include <eda/vhdl93/ast/util/position_tagged.hpp>

#include <eda/vhdl93/ast/identifier_list.hpp>
#include <eda/vhdl93/ast/subtype_indication.hpp>
#include <eda/vhdl93/ast/expression.hpp>
#include <eda/vhdl93/ast/util/optional.hpp>


namespace eda { namespace vhdl93 { namespace ast {


struct variable_declaration : position_tagged
{
    bool                            shared;
    ast::identifier_list            identifier_list;
    ast::subtype_indication         subtype_indication;
    optional<ast::expression>       expression;
};


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_VARIABLE_DECLARATION_HPP_ */
