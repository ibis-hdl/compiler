/*
 * context_clause.hpp
 *
 *  Created on: 17.06.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_CONTEXT_CLAUSE_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_CONTEXT_CLAUSE_HPP_


#include <eda/vhdl/ast/util/namespace_alias.hpp>

#include <eda/vhdl/ast/context_item.hpp>
#include <vector>


namespace eda { namespace vhdl { namespace ast {


struct context_clause : std::vector<context_item> { };


} } } // namespace eda.vhdl.ast


#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_CONTEXT_CLAUSE_HPP_ */
