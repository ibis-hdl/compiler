/*
 * timeout_clause.hpp
 *
 *  Created on: 13.05.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_TIMEOUT_CLAUSE_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_TIMEOUT_CLAUSE_HPP_


#include <eda/vhdl/ast/util/position_tagged.hpp>

#include <eda/vhdl/ast/expression.hpp>


namespace eda { namespace vhdl { namespace ast {


struct timeout_clause : position_tagged
{
   ast::expression              time_expression;

   /* Spirit.X3 single-element sequence adaptation bug fix
    * [Spirit Qi attribute propagation issue with single-member struct](
    * https://stackoverflow.com/questions/19823413/spirit-qi-attribute-propagation-issue-with-single-member-struct?answertab=active#tab-top) */
   timeout_clause() = default;

   timeout_clause(ast::expression&& time_expression_)
   : time_expression{ std::move(time_expression_) }
   { }
};


} } } // namespace eda.vhdl.ast



#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_TIMEOUT_CLAUSE_HPP_ */
