/*
 * signal_name.hpp
 *
 *  Created on: 14.04.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_SIGNAL_LIST_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_SIGNAL_LIST_HPP_


#include <eda/vhdl93/ast/namespace_alias.hpp>

#include <eda/vhdl93/ast/nullary.hpp>
#include <eda/vhdl93/ast/name.hpp>
#include <eda/vhdl93/ast/keyword_token.hpp>
#include <list>

#include <boost/spirit/home/x3/support/ast/variant.hpp>


namespace eda { namespace vhdl93 { namespace ast {


struct signal_list_names
{
    std::list<ast::name>        list;
};


using signal_list = x3::variant<
	nullary,
	signal_list_names,
	keyword_token           // OTHERS | ALL
>;


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_SIGNAL_LIST_HPP_ */
