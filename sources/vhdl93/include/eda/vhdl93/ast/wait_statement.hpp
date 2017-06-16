/*
 * wait_statement.hpp
 *
 *  Created on: 13.05.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_WAIT_STATEMENT_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_WAIT_STATEMENT_HPP_


#include <eda/vhdl93/ast/util/namespace_alias.hpp>
#include <eda/vhdl93/ast/util/position_tagged.hpp>

#include <eda/vhdl93/ast/label.hpp>
#include <eda/vhdl93/ast/sensitivity_clause.hpp>
#include <eda/vhdl93/ast/condition_clause.hpp>
#include <eda/vhdl93/ast/timeout_clause.hpp>
#include <eda/vhdl93/ast/util/optional.hpp>


namespace eda { namespace vhdl93 { namespace ast {


struct wait_statement : position_tagged
{
   optional<ast::label>                     label;
   optional<ast::sensitivity_clause>        sensitivity_clause;
   optional<ast::condition_clause>          condition_clause;
   optional<ast::timeout_clause>            timeout_clause;
};


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_WAIT_STATEMENT_HPP_ */
