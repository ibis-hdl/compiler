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
#include <boost/optional.hpp>

#include <list>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


enum class operator_token;
struct term;


struct simple_expression_rest {
    operator_token                  operator_;
    term                            term;
};


struct simple_expression : x3::position_tagged
{
    boost::optional<operator_token> sign;
    term                            term;
    std::list<simple_expression_rest> rest;
};


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_SIMPLE_EXPRESSION_HPP_ */
