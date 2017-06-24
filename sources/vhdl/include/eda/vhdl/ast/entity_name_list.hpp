/*
 * entity_name_list.hpp
 *
 *  Created on: 16.05.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_ENTITY_NAME_LIST_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_ENTITY_NAME_LIST_HPP_


#include <eda/vhdl/ast/util/namespace_alias.hpp>

#include <eda/vhdl/ast/entity_designator.hpp>
#include <eda/vhdl/ast/util/nullary.hpp>
#include <eda/vhdl/ast/keyword_token.hpp>

#include <boost/spirit/home/x3/support/ast/variant.hpp>
#include <vector>


namespace eda { namespace vhdl { namespace ast {


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


} } } // namespace eda.vhdl.ast


#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_ENTITY_NAME_LIST_HPP_ */
