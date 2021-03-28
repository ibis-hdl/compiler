/*
 * sequential_statement.hpp
 *
 *  Created on: 04.06.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_SEQUENTIAL_STATEMENT_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_SEQUENTIAL_STATEMENT_HPP_


#include <eda/vhdl/ast/util/variant.hpp>

#include <eda/vhdl/ast/util/nullary.hpp>
#include <eda/vhdl/ast/node/assertion_statement.hpp>
#include <eda/vhdl/ast/node/exit_statement.hpp>
#include <eda/vhdl/ast/node/next_statement.hpp>
#include <eda/vhdl/ast/node/null_statement.hpp>
#include <eda/vhdl/ast/node/procedure_call_statement.hpp>
#include <eda/vhdl/ast/node/report_statement.hpp>
#include <eda/vhdl/ast/node/return_statement.hpp>
#include <eda/vhdl/ast/node/signal_assignment_statement.hpp>
#include <eda/vhdl/ast/node/variable_assignment_statement.hpp>
#include <eda/vhdl/ast/node/wait_statement.hpp>


namespace eda { namespace vhdl { namespace ast {


struct if_statement;
struct case_statement;
struct loop_statement;


/**
 * Ast node cyclic dependency as:
 *
 * \dot
 * digraph sequential_statement  {
 *   sequential_statement -> if_statement [ label=<<i>forward</i>>];
 *   if_statement         -> sequence_of_statements;
 *
 *   sequential_statement -> case_statement [ label=<<i>forward</i>>];
 *   case_statement       -> sequence_of_statements;
 *
 *   sequential_statement -> loop_statement [ label=<<i>forward</i>>];
 *   loop_statement       -> sequence_of_statements;
 *
 *   sequence_of_statements -> sequential_statement
 * }
 * \enddot
 */
using sequential_statement = variant<
    nullary,
    wait_statement,
    assertion_statement,
    report_statement,
    signal_assignment_statement,
    variable_assignment_statement,
    procedure_call_statement,
    forward_ast<if_statement>,
    forward_ast<case_statement>,
    forward_ast<loop_statement>,
    next_statement,
    exit_statement,
    return_statement,
    null_statement
>;


} } } // namespace eda.vhdl.ast


#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_SEQUENTIAL_STATEMENT_HPP_ */
