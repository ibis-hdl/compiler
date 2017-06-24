/*
 * simple_expression.hpp
 *
 *  Created on: 12.04.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_SIMPLE_EXPRESSION_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_SIMPLE_EXPRESSION_HPP_


#include <eda/vhdl/ast/util/namespace_alias.hpp>
#include <eda/vhdl/ast/util/position_tagged.hpp>

#include <eda/vhdl/ast/operator_token.hpp>
#include <eda/vhdl/ast/term.hpp>
#include <eda/vhdl/ast/util/optional.hpp>
#include <vector>


namespace eda { namespace vhdl { namespace ast {


struct simple_expression : position_tagged
{
    struct chunk {
        operator_token                  adding_operator;
        ast::term                       term;
    };

    optional<operator_token>            sign;
    ast::term                           term;
    std::vector<chunk>                  rest_list;
};


} } } // namespace eda.vhdl.ast


#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_SIMPLE_EXPRESSION_HPP_ */
