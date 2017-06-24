/*
 * signal_name.hpp
 *
 *  Created on: 14.04.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_SIGNAL_LIST_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_SIGNAL_LIST_HPP_


#include <vector>

#include <boost/spirit/home/x3/support/ast/variant.hpp>
#include <eda/vhdl/ast/keyword_token.hpp>
#include <eda/vhdl/ast/name.hpp>
#include <eda/vhdl/ast/util/namespace_alias.hpp>
#include <eda/vhdl/ast/util/nullary.hpp>


namespace eda { namespace vhdl { namespace ast {


struct signal_list_list : std::vector<ast::name>  { };


// signal_list ::=
//           signal_name { , signal_name }
//         | others
//         | all
#if 0
using signal_list = x3::variant<
    nullary,
    signal_list_list,
    keyword_token           // OTHERS | ALL
>;
#else
struct signal_list : x3::variant<
    nullary,
    signal_list_list,
    keyword_token           // OTHERS | ALL
>
{
    using base_type::base_type;
    using base_type::operator=;
};
#endif


} } } // namespace eda.vhdl.ast


#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_SIGNAL_LIST_HPP_ */
