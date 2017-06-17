/*
 * instantiation_list.hpp
 *
 *  Created on: 17.06.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_INSTANTIATION_LIST_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_INSTANTIATION_LIST_HPP_


#include <eda/vhdl93/ast/util/namespace_alias.hpp>

#include <eda/vhdl93/ast/util/nullary.hpp>
#include <eda/vhdl93/ast/label.hpp>
#include <vector>

#include <boost/spirit/home/x3/support/ast/variant.hpp>


namespace eda { namespace vhdl93 { namespace ast {


using instantiation_label_list = std::vector<ast::label>;


struct instantiation_list : x3::variant<
    nullary,
    instantiation_label_list,
    keyword_token               // OTHERS | ALL
>
{
    using base_type::base_type;
    using base_type::operator=;
};


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_INSTANTIATION_LIST_HPP_ */
