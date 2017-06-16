/*
 * case_statement.hpp
 *
 *  Created on: 05.06.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_CASE_STATEMENT_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_CASE_STATEMENT_HPP_


#include <eda/vhdl93/ast/util/namespace_alias.hpp>
#include <eda/vhdl93/ast/util/position_tagged.hpp>

#include <eda/vhdl93/ast/label.hpp>
//#include <eda/vhdl93/ast/case_statement_alternative.hpp>
#include <eda/vhdl93/ast/util/optional.hpp>
#include <vector>


namespace eda { namespace vhdl93 { namespace ast {


struct case_statement_alternative;

struct case_statement : position_tagged
{
    optional<ast::label>                            label;
    ast::expression                                 expression;
    std::vector<ast::case_statement_alternative>    alternatives;
    optional<ast::label>                            end_label;
};


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_CASE_STATEMENT_HPP_ */
