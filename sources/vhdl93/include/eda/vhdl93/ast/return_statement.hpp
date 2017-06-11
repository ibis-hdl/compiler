/*
 * return_statement.hpp
 *
 *  Created on: 05.06.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_RETURN_STATEMENT_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_RETURN_STATEMENT_HPP_


#include <eda/vhdl93/ast/namespace_alias.hpp>
#include <eda/vhdl93/ast/position_tagged.hpp>

#include <eda/vhdl93/ast/label.hpp>
#include <eda/vhdl93/ast/expression.hpp>
#include <eda/vhdl93/ast/optional.hpp>


namespace eda { namespace vhdl93 { namespace ast {


struct return_statement : position_tagged
{
    optional<ast::label>                label;
    optional<ast::expression>           expression;
};


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_RETURN_STATEMENT_HPP_ */
