/*
 * group_constituent_list.hpp
 *
 *  Created on: 20.06.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_GROUP_CONSTITUENT_LIST_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_GROUP_CONSTITUENT_LIST_HPP_


#include <eda/vhdl93/ast/util/namespace_alias.hpp>

#include <eda/vhdl93/ast/util/nullary.hpp>
#include <eda/vhdl93/ast/name.hpp>
#include <eda/vhdl93/ast/character_literal.hpp>
#include <vector>

#include <boost/spirit/home/x3/support/ast/variant.hpp>


namespace eda { namespace vhdl93 { namespace ast {


struct group_constituent : x3::variant<
    ast::nullary,
    ast::name,
    ast::character_literal
>
{
    using base_type::base_type;
    using base_type::operator=;
};


struct group_constituent_list : std::vector<ast::group_constituent> { };


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_GROUP_CONSTITUENT_LIST_HPP_ */
