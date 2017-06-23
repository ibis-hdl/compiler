/*
 * block_statement.hpp
 *
 *  Created on: 19.06.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_BLOCK_STATEMENT_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_BLOCK_STATEMENT_HPP_


#include <eda/vhdl93/ast/util/namespace_alias.hpp>
#include <eda/vhdl93/ast/util/position_tagged.hpp>

#include <eda/vhdl93/ast/label.hpp>
#include <eda/vhdl93/ast/expression.hpp>
#include <eda/vhdl93/ast/block_header.hpp>
#include <eda/vhdl93/ast/block_declarative_part.hpp>
#include <eda/vhdl93/ast/block_statement_part.hpp>
#include <eda/vhdl93/ast/util/optional.hpp>


namespace eda { namespace vhdl93 { namespace ast {


struct block_statement : position_tagged
{
    ast::label                      label;
    optional<ast::expression>       guard_expression;
    ast::block_header               header;
    ast::block_declarative_part     declarative_part;
    ast::block_statement_part       statement_part;
    optional<ast::label>            end_label;
};


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_BLOCK_STATEMENT_HPP_ */