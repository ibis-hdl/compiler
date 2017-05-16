/*
 * entity_name_list.hpp
 *
 *  Created on: 16.05.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_ENTITY_NAME_LIST_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_ENTITY_NAME_LIST_HPP_


#include <eda/vhdl93/ast/namespace_alias.hpp>

#include <eda/vhdl93/ast/entity_designator.hpp>
#include <eda/vhdl93/ast/nullary.hpp>
#include <eda/vhdl93/ast/keyword_token.hpp>

#include <boost/spirit/home/x3/support/ast/variant.hpp>
#include <vector>


namespace eda { namespace vhdl93 { namespace ast {


struct entity_designator_list : std::vector<ast::entity_designator> { };


#if 0
using entity_name_list = x3::variant<
    nullary,
    entity_designator_list,
    keyword_token
>;
#else
struct entity_name_list : x3::variant<
    nullary,
    entity_designator_list,
    keyword_token           // OTHERS | ALL
>
{
    using base_type::base_type;
    using base_type::operator=;
};
#endif


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_ENTITY_NAME_LIST_HPP_ */
