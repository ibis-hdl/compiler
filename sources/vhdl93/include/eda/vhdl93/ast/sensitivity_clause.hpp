/*
 * sensitivity_clause.hpp
 *
 *  Created on: 13.05.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_SENSITIVITY_CLAUSE_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_SENSITIVITY_CLAUSE_HPP_


#include <eda/vhdl93/ast/namespace_alias.hpp>
#include <eda/vhdl93/ast/position_tagged.hpp>

#include <eda/vhdl93/ast/name.hpp>
#include <vector>

namespace eda { namespace vhdl93 { namespace ast {


using sensitivity_list = std::vector<ast::name>;


struct sensitivity_clause : position_tagged
{
   ast::sensitivity_list        sensitivity_list;
};


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_SENSITIVITY_CLAUSE_HPP_ */
