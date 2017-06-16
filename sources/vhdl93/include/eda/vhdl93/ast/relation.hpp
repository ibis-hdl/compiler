/*
 * relation_expression.hpp
 *
 *  Created on: 15.04.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_RELATION_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_RELATION_HPP_


#include <eda/vhdl93/ast/util/namespace_alias.hpp>
#include <eda/vhdl93/ast/util/position_tagged.hpp>

#include <eda/vhdl93/ast/operator_token.hpp>
#include <eda/vhdl93/ast/shift_expression.hpp>
#include <eda/vhdl93/ast/util/optional.hpp>


namespace eda { namespace vhdl93 { namespace ast {


struct relation : position_tagged
{
    struct chunk
    {
        operator_token              relational_operator;
        ast::shift_expression       shift_expression;
    };

    ast::shift_expression           shift_expression;
    optional<chunk>                 rest;
};


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_RELATION_HPP_ */
