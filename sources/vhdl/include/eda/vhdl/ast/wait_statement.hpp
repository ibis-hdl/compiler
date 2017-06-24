/*
 * wait_statement.hpp
 *
 *  Created on: 13.05.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_WAIT_STATEMENT_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_WAIT_STATEMENT_HPP_


#include <eda/vhdl/ast/condition_clause.hpp>
#include <eda/vhdl/ast/label.hpp>
#include <eda/vhdl/ast/sensitivity_clause.hpp>
#include <eda/vhdl/ast/timeout_clause.hpp>
#include <eda/vhdl/ast/util/namespace_alias.hpp>
#include <eda/vhdl/ast/util/optional.hpp>
#include <eda/vhdl/ast/util/position_tagged.hpp>


namespace eda { namespace vhdl { namespace ast {


struct wait_statement : position_tagged
{
   optional<ast::label>                     label;
   optional<ast::sensitivity_clause>        sensitivity_clause;
   optional<ast::condition_clause>          condition_clause;
   optional<ast::timeout_clause>            timeout_clause;
};


} } } // namespace eda.vhdl.ast


#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_WAIT_STATEMENT_HPP_ */
