/*
 * signal_list.hpp
 *
 *  Created on: 14.04.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_SIGNAL_LIST_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_SIGNAL_LIST_HPP_


#include <eda/vhdl/ast/util/variant.hpp>

#include <eda/vhdl/ast/util/nullary.hpp>
#include <eda/vhdl/ast/node/keyword_token.hpp>
#include <eda/vhdl/ast/node/name.hpp>
#include <vector>


namespace eda { namespace vhdl { namespace ast {


struct signal_list_list : std::vector<ast::name>  { };


// signal_list ::=
//           signal_name { , signal_name }
//         | others
//         | all
struct signal_list : variant<
    nullary,
    signal_list_list,
    keyword_token           // OTHERS | ALL
>
{
    using base_type::base_type;
    using base_type::operator=;
};


} } } // namespace eda.vhdl.ast


#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_SIGNAL_LIST_HPP_ */
