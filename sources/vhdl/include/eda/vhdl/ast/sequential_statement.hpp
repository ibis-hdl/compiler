/*
 * sequential_statement.hpp
 *
 *  Created on: 04.06.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_SEQUENTIAL_STATEMENT_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_SEQUENTIAL_STATEMENT_HPP_


#include <boost/spirit/home/x3/support/ast/variant.hpp>
#include <eda/vhdl/ast/assertion_statement.hpp>
#include <eda/vhdl/ast/exit_statement.hpp>
#include <eda/vhdl/ast/next_statement.hpp>
#include <eda/vhdl/ast/null_statement.hpp>
#include <eda/vhdl/ast/procedure_call_statement.hpp>
#include <eda/vhdl/ast/report_statement.hpp>
#include <eda/vhdl/ast/return_statement.hpp>
#include <eda/vhdl/ast/signal_assignment_statement.hpp>
#include <eda/vhdl/ast/util/namespace_alias.hpp>
#include <eda/vhdl/ast/util/nullary.hpp>
#include <eda/vhdl/ast/variable_assignment_statement.hpp>
#include <eda/vhdl/ast/wait_statement.hpp>


namespace eda { namespace vhdl { namespace ast {


struct if_statement;
struct case_statement;
struct loop_statement;


/**
 * Ast node cyclic dependency as:
 *
 * \dot
 * digraph sequential_statement  {
 *   sequential_statement -> if_statement [ label="forward"];
 *   if_statement -> sequence_of_statements;
 *
 *   sequential_statement -> case_statement [ label="forward"];
 *   case_statement -> sequence_of_statements;
 *
 *   sequential_statement -> loop_statement [ label="forward"];
 *   loop_statement -> sequence_of_statements;
 *
 *   sequence_of_statements -> sequential_statement
 * }
 * \enddot
 */
struct sequential_statement : x3::variant<
    nullary,
    wait_statement,
    assertion_statement,
    report_statement,
    signal_assignment_statement,
    variable_assignment_statement,
    procedure_call_statement,
    x3::forward_ast<if_statement>,
    x3::forward_ast<case_statement>,
    x3::forward_ast<loop_statement>,
    next_statement,
    exit_statement,
    return_statement,
    null_statement
>
{
    using base_type::base_type;
    using base_type::operator=;
};


} } } // namespace eda.vhdl.ast


#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_SEQUENTIAL_STATEMENT_HPP_ */
