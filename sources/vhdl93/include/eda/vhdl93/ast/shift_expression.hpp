/*
 * shift_expression.hpp
 *
 *  Created on: 14.04.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_SHIFT_EXPRESSION_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_SHIFT_EXPRESSION_HPP_


#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <boost/spirit/home/x3/support/ast/variant.hpp> // x3::position_tagged

#include <eda/vhdl93/ast/operator_token.hpp>
#include <eda/vhdl93/ast/simple_expression.hpp>

#include <boost/optional.hpp>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct shift_expression_chunk
{
    operator_token                  operator_;
    ast::simple_expression          simple_expression;
};


struct shift_expression : x3::position_tagged
{
    ast::simple_expression          simple_expression;
    boost::optional<shift_expression_chunk> chunk;
};


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_SHIFT_EXPRESSION_HPP_ */
