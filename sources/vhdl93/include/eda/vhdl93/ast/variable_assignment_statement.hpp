/*
 * variable_assignment_statement.hpp
 *
 *  Created on: 06.06.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_VARIABLE_ASSIGNMENT_STATEMENT_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_VARIABLE_ASSIGNMENT_STATEMENT_HPP_


#include <eda/vhdl93/ast/namespace_alias.hpp>
#include <eda/vhdl93/ast/position_tagged.hpp>

#include <eda/vhdl93/ast/label.hpp>
#include <eda/vhdl93/ast/target.hpp>
#include <eda/vhdl93/ast/expression.hpp>
#include <eda/vhdl93/ast/optional.hpp>


namespace eda { namespace vhdl93 { namespace ast {


struct variable_assignment_statement : position_tagged
{
    optional<ast::label>                    label;
    ast::target                             target;
    ast::expression                         expression;
};


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_VARIABLE_ASSIGNMENT_STATEMENT_HPP_ */
