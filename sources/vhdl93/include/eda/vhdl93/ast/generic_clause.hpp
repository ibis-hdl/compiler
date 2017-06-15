/*
 * generic_clause.hpp
 *
 *  Created on: 07.06.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_GENERIC_CLAUSE_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_GENERIC_CLAUSE_HPP_


#include <eda/vhdl93/ast/util/namespace_alias.hpp>

#include <eda/vhdl93/ast/interface_list.hpp>
#include <vector>


namespace eda { namespace vhdl93 { namespace ast {


struct generic_clause : position_tagged
{
    ast::interface_list     generic_list;
};


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_GENERIC_CLAUSE_HPP_ */
