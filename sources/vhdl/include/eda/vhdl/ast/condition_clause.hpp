/*
 * condition_clause.hpp
 *
 *  Created on: 13.05.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_CONDITION_CLAUSE_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_CONDITION_CLAUSE_HPP_


#include <eda/vhdl/ast/util/position_tagged.hpp>

#include <eda/vhdl/ast/condition.hpp>
#include <vector>


namespace eda { namespace vhdl { namespace ast {


struct condition_clause : position_tagged
{
   ast::condition               condition;

   /* FixMe: X3 single-element sequence adaptation bug
    * The single-element sequence adaptation bug still exist in X3, at least
    * shipped with boost 1.64.0, maybe tightened by the optional used at
    * wait_clause rule. */
   condition_clause() = default;

   condition_clause(ast::condition&& condition)
   : condition{ std::move(condition) }
   { }
};


} } } // namespace eda.vhdl.ast


#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_CONDITION_CLAUSE_HPP_ */
