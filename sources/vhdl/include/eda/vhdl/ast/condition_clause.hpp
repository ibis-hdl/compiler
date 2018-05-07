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

   /* Spirit.X3 single-element sequence adaptation bug fix
    * [Spirit Qi attribute propagation issue with single-member struct](
    * https://stackoverflow.com/questions/19823413/spirit-qi-attribute-propagation-issue-with-single-member-struct?answertab=active#tab-top) */
   condition_clause() = default;

   condition_clause(ast::condition&& condition)
   : condition{ std::move(condition) }
   { }
};


} } } // namespace eda.vhdl.ast


#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_CONDITION_CLAUSE_HPP_ */
