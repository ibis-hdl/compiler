/*
 * shift_expression.hpp
 *
 *  Created on: 14.04.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_SHIFT_EXPRESSION_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_SHIFT_EXPRESSION_HPP_


#include <eda/vhdl93/ast/namespace_alias.hpp>
#include <eda/vhdl93/ast/position_tagged.hpp>

#include <eda/vhdl93/ast/operator_token.hpp>
#include <eda/vhdl93/ast/simple_expression.hpp>
#include <boost/optional.hpp>


namespace eda { namespace vhdl93 { namespace ast {


struct shift_expression : position_tagged
{
    struct chunk
    {
        operator_token              operator_;
        ast::simple_expression      simple_expression;
    };

    ast::simple_expression          simple_expression;
    boost::optional<chunk>          rest;
};


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_SHIFT_EXPRESSION_HPP_ */
