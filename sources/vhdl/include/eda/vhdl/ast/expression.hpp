/*
 * expression.hpp
 *
 *  Created on: 15.04.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_EXPRESSION_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_EXPRESSION_HPP_


#include <eda/vhdl/ast/util/position_tagged.hpp>

#include <eda/vhdl/ast/operator_token.hpp>
#include <eda/vhdl/ast/relation.hpp>
#include <vector>


namespace eda { namespace vhdl { namespace ast {


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


} } } // namespace eda.vhdl.ast


#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_EXPRESSION_HPP_ */
