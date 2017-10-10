/*
 * generic_clause.hpp
 *
 *  Created on: 07.06.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_GENERIC_CLAUSE_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_GENERIC_CLAUSE_HPP_


#include <eda/vhdl/ast/util/namespace_alias.hpp>

#include <eda/vhdl/ast/interface_list.hpp>
#include <vector>


namespace eda { namespace vhdl { namespace ast {


struct generic_clause : position_tagged
{
    ast::interface_list     generic_list;
};


} } } // namespace eda.vhdl.ast


#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_GENERIC_CLAUSE_HPP_ */