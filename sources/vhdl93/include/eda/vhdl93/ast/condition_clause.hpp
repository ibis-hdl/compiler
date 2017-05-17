/*
 * condition_clause.hpp
 *
 *  Created on: 13.05.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_CONDITION_CLAUSE_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_CONDITION_CLAUSE_HPP_


#include <eda/vhdl93/ast/namespace_alias.hpp>
#include <eda/vhdl93/ast/position_tagged.hpp>

#include <eda/vhdl93/ast/condition.hpp>
#include <vector>


namespace eda { namespace vhdl93 { namespace ast {


struct condition_clause : position_tagged
{
   ast::condition           condition;

   /* FixMe: single-element sequence adaptation bug
    * The single-element sequence adaptation bug still exist in X3, at least
    * shipped with boost 1.64.0, maybe tightened by the optional used at
    * wait_clause rule. */
   condition_clause() = default;
   condition_clause(ast::condition&& condition_)
   {
       condition = std::move(condition_);
   }
};


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_CONDITION_CLAUSE_HPP_ */