/*
 * simple_expression.hpp
 *
 *  Created on: 12.04.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_SIMPLE_EXPRESSION_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_SIMPLE_EXPRESSION_HPP_


#include <eda/vhdl93/ast/namespace_alias.hpp>
#include <eda/vhdl93/ast/position_tagged.hpp>

#include <eda/vhdl93/ast/operator_token.hpp>
#include <eda/vhdl93/ast/term.hpp>
#include <boost/optional.hpp>
#include <vector>


namespace eda { namespace vhdl93 { namespace ast {


struct simple_expression : position_tagged
{
    struct chunk {
        operator_token                  operator_;
        ast::term                       term;
    };

    boost::optional<operator_token>     sign;
    ast::term                           term;
    std::vector<chunk>                  rest_list;
};


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_SIMPLE_EXPRESSION_HPP_ */
