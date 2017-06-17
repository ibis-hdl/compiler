/*
 * context_clause.hpp
 *
 *  Created on: 17.06.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_CONTEXT_CLAUSE_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_CONTEXT_CLAUSE_HPP_


#include <eda/vhdl93/ast/util/namespace_alias.hpp>

#include <eda/vhdl93/ast/context_item.hpp>
#include <vector>


namespace eda { namespace vhdl93 { namespace ast {


struct context_clause : std::vector<context_item> { };


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_CONTEXT_CLAUSE_HPP_ */
