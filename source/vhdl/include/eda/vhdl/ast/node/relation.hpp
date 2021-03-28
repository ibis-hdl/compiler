/*
 * relation_expression.hpp
 *
 *  Created on: 15.04.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_RELATION_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_RELATION_HPP_


#include <eda/vhdl/ast/util/position_tagged.hpp>

#include <eda/vhdl/ast/node/operator_token.hpp>
#include <eda/vhdl/ast/node/shift_expression.hpp>
#include <eda/vhdl/ast/util/optional.hpp>


namespace eda { namespace vhdl { namespace ast {


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


} } } // namespace eda.vhdl.ast


#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_RELATION_HPP_ */
