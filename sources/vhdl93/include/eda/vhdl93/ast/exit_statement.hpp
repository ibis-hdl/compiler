/*
 * exit_statement.hpp
 *
 *  Created on: 05.06.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_EXIT_STATEMENT_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_EXIT_STATEMENT_HPP_


#include <eda/vhdl93/ast/namespace_alias.hpp>
#include <eda/vhdl93/ast/position_tagged.hpp>

#include <eda/vhdl93/ast/label.hpp>
#include <eda/vhdl93/ast/condition.hpp>
#include <eda/vhdl93/ast/optional.hpp>


namespace eda { namespace vhdl93 { namespace ast {


struct exit_statement : position_tagged
{
    optional<ast::label>                label;
    optional<ast::label>                loop_label;
    optional<ast::condition>            condition;
};


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_EXIT_STATEMENT_HPP_ */
