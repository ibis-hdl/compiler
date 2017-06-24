/*
 * shift_expression.hpp
 *
 *  Created on: 14.04.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_SHIFT_EXPRESSION_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_SHIFT_EXPRESSION_HPP_


#include <eda/vhdl/ast/util/namespace_alias.hpp>
#include <eda/vhdl/ast/util/position_tagged.hpp>

#include <eda/vhdl/ast/operator_token.hpp>
#include <eda/vhdl/ast/simple_expression.hpp>
#include <eda/vhdl/ast/util/optional.hpp>


namespace eda { namespace vhdl { namespace ast {


struct shift_expression : position_tagged
{
    struct chunk
    {
        operator_token              shift_operator;
        ast::simple_expression      simple_expression;
    };

    ast::simple_expression          simple_expression;
    optional<chunk>                 rest;
};


} } } // namespace eda.vhdl.ast


#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_SHIFT_EXPRESSION_HPP_ */
