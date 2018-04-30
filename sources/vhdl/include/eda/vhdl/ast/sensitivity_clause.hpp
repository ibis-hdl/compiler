/*
 * sensitivity_clause.hpp
 *
 *  Created on: 13.05.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_SENSITIVITY_CLAUSE_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_SENSITIVITY_CLAUSE_HPP_


#include <eda/vhdl/ast/util/position_tagged.hpp>

#include <eda/vhdl/ast/sensitivity_list.hpp>


namespace eda { namespace vhdl { namespace ast {


struct sensitivity_clause : position_tagged
{
   ast::sensitivity_list        sensitivity_list;

   /* FixMe: single-element sequence adaptation bug
    * The single-element sequence adaptation bug still exist in X3, at least
    * shipped with boost 1.64.0, maybe tightened by the optional used at
    * wait_clause rule. */
   sensitivity_clause() = default;

   sensitivity_clause(ast::sensitivity_list&& sensitivity_list)
   : sensitivity_list{ std::move(sensitivity_list) }
   { }
};


} } } // namespace eda.vhdl.ast


#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_SENSITIVITY_CLAUSE_HPP_ */
