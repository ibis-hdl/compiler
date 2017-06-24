/*
 * identifier_list.hpp
 *
 *  Created on: 02.04.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_IDENTIFIER_LIST_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_IDENTIFIER_LIST_HPP_


#include <eda/vhdl/ast/util/namespace_alias.hpp>
#include <eda/vhdl/ast/util/position_tagged.hpp>

#include <eda/vhdl/ast/identifier.hpp>
#include <vector>


namespace eda { namespace vhdl { namespace ast {


struct identifier_list : std::vector<ast::identifier> { };


} } } // namespace eda.vhdl.ast


#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_IDENTIFIER_LIST_HPP_ */
