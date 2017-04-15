/*
 * relation_expression.hpp
 *
 *  Created on: 15.04.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_RELATION_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_RELATION_HPP_


#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <boost/spirit/home/x3/support/ast/variant.hpp> // x3::position_tagged

#include <eda/vhdl93/ast/operator_token.hpp>
#include <eda/vhdl93/ast/shift_expression.hpp>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct relation /* expression */ : x3::position_tagged
{
    shift_expression        lhs;
    operator_token          operator_;
    shift_expression        rhs;
};


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_RELATION_HPP_ */
