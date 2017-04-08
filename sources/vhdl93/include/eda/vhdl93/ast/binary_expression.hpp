/*
 * binary_expression.hpp
 *
 *  Created on: 06.04.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_BINARY_EXPRESSION_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_BINARY_EXPRESSION_HPP_


#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


enum class operator_token;
struct operand;


struct binary_expression :  x3::position_tagged
{
    x3::forward_ast<operator_token>     operator_;
    x3::forward_ast<operand>            lhs;
    x3::forward_ast<operand>            rhs;
};


} } } // namespace eda.vhdl93.ast



#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_BINARY_EXPRESSION_HPP_ */
