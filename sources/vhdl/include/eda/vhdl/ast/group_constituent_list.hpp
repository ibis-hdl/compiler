/*
 * group_constituent_list.hpp
 *
 *  Created on: 20.06.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_GROUP_CONSTITUENT_LIST_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_GROUP_CONSTITUENT_LIST_HPP_


#include <eda/vhdl/ast/util/variant.hpp>

#include <eda/vhdl/ast/util/nullary.hpp>
#include <eda/vhdl/ast/name.hpp>
#include <eda/vhdl/ast/character_literal.hpp>
#include <vector>


namespace eda { namespace vhdl { namespace ast {


using group_constituent = variant<
    ast::nullary,
    ast::name,
    ast::character_literal
>;


using group_constituent_list = std::vector<ast::group_constituent>;


} } } // namespace eda.vhdl.ast


#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_GROUP_CONSTITUENT_LIST_HPP_ */
