/*
 * signal_name.hpp
 *
 *  Created on: 14.04.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_SIGNAL_LIST_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_SIGNAL_LIST_HPP_


#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>

#include <eda/vhdl93/ast/nullary.hpp>
#include <eda/vhdl93/ast/name.hpp>
#include <eda/vhdl93/ast/keyword_token.hpp>

#include <list>


namespace eda { namespace vhdl93 { namespace ast {


// ToDo: derive signal_name from ast::name, which gives compile errors
#if 0
struct signal_name : ast::name
{
    // XXX DOESN'T COMPILE
    using base_type::base_type;
    using base_type::operator=;
};

struct signal_list_names
{
    std::list<signal_name>      list;
};
#else


struct signal_list_names
{
    std::list<ast::name>        list;
};
#endif


struct signal_list :
    x3::variant<
        nullary,
        signal_list_names,
        keyword_token
    >
{
    using base_type::base_type;
    using base_type::operator=;
};


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_SIGNAL_LIST_HPP_ */
