/*
 * expression.hpp
 *
 *  Created on: 15.04.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_EXPRESSION_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_EXPRESSION_HPP_


#include <eda/vhdl93/ast/util/namespace_alias.hpp>
#include <eda/vhdl93/ast/util/position_tagged.hpp>

#include <eda/vhdl93/ast/operator_token.hpp>
#include <eda/vhdl93/ast/relation.hpp>
#include <vector>


namespace eda { namespace vhdl93 { namespace ast {


struct expression : position_tagged
{
    struct chunk
    {
        operator_token              logical_operator;
        ast::relation               relation;
    };

    ast::relation                   relation;
    std::vector<chunk>              rest_list;
};


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_EXPRESSION_HPP_ */
