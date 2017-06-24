/*
 * instantiation_list.hpp
 *
 *  Created on: 17.06.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_INSTANTIATION_LIST_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_INSTANTIATION_LIST_HPP_


#include <vector>

#include <boost/spirit/home/x3/support/ast/variant.hpp>
#include <eda/vhdl/ast/keyword_token.hpp>
#include <eda/vhdl/ast/label.hpp>
#include <eda/vhdl/ast/util/namespace_alias.hpp>
#include <eda/vhdl/ast/util/nullary.hpp>


namespace eda { namespace vhdl { namespace ast {


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


} } } // namespace eda.vhdl.ast


#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_INSTANTIATION_LIST_HPP_ */
