/*
 * variable_assignment_statement.hpp
 *
 *  Created on: 06.06.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_VARIABLE_ASSIGNMENT_STATEMENT_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_VARIABLE_ASSIGNMENT_STATEMENT_HPP_


#include <eda/vhdl/ast/util/position_tagged.hpp>

#include <eda/vhdl/ast/label.hpp>
#include <eda/vhdl/ast/target.hpp>
#include <eda/vhdl/ast/expression.hpp>
#include <eda/vhdl/ast/util/optional.hpp>


namespace eda { namespace vhdl { namespace ast {


struct variable_assignment_statement : position_tagged
{
    optional<ast::label>                    label;
    ast::target                             target;
    ast::expression                         expression;
};


} } } // namespace eda.vhdl.ast


#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_VARIABLE_ASSIGNMENT_STATEMENT_HPP_ */
