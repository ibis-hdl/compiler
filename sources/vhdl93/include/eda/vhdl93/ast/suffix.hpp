/*
 * suffix.hpp
 *
 *  Created on: 02.04.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_SUFFIX_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_SUFFIX_HPP_


#include <boost/spirit/home/x3/support/ast/variant.hpp>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct all;
struct character_literal;
struct operator_symbol;
struct simple_name;

struct suffix :
    x3::variant<
        x3::forward_ast<simple_name>,
        x3::forward_ast<character_literal>
        //x3::forward_ast<operator_symbol>,
        //x3::forward_ast<all>,
    >
{
    using base_type::base_type;
    using base_type::operator=;
};


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_SUFFIX_HPP_ */
