/*
 * simple_expression.hpp
 *
 *  Created on: 12.04.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_SIMPLE_EXPRESSION_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_SIMPLE_EXPRESSION_HPP_


#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <boost/spirit/home/x3/support/ast/variant.hpp> // x3::position_tagged

#include <eda/vhdl93/ast/term.hpp>

#include <boost/optional.hpp>

#include <list>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


enum class operator_token;


struct simple_expression_chunk {
    operator_token                      operator_;
    ast::term                           term;
};


struct simple_expression : x3::position_tagged
{
    boost::optional<operator_token>     sign;
    ast::term                           term;
    std::list<simple_expression_chunk>  rest;
};


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_SIMPLE_EXPRESSION_HPP_ */
