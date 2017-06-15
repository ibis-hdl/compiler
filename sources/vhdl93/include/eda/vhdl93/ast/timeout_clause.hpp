/*
 * timeout_clause.hpp
 *
 *  Created on: 13.05.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_TIMEOUT_CLAUSE_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_TIMEOUT_CLAUSE_HPP_


#include <eda/vhdl93/ast/util/namespace_alias.hpp>
#include <eda/vhdl93/ast/position_tagged.hpp>

#include <eda/vhdl93/ast/expression.hpp>


namespace eda { namespace vhdl93 { namespace ast {


struct timeout_clause : position_tagged
{
   ast::expression              time_expression;

   /* FixMe: single-element sequence adaptation bug
    * The single-element sequence adaptation bug still exist in X3, at least
    * shipped with boost 1.64.0, maybe tightened by the optional used at
    * wait_clause rule. */
   timeout_clause() = default;
   timeout_clause(ast::expression&& time_expression)
   : time_expression{ std::move(time_expression) }
   { }
};


} } } // namespace eda.vhdl93.ast



#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_TIMEOUT_CLAUSE_HPP_ */
