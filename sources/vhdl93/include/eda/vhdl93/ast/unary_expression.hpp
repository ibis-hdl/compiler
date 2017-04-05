/*
 * unary_expression.hpp
 *
 *  Created on: 05.04.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_UNARY_EXPRESSION_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_UNARY_EXPRESSION_HPP_


#include <boost/spirit/home/x3/support/ast/variant.hpp>
#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


enum class operator_token;
struct operand;


struct unary_expression :  x3::position_tagged
{
    x3::forward_ast<operator_token>     operator_;
    x3::forward_ast<operand>            operand_;
};


} } } // namespace eda.vhdl93.ast



#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_UNARY_EXPRESSION_HPP_ */
