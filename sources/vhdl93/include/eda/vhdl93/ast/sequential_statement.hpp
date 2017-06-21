/*
 * sequential_statement.hpp
 *
 *  Created on: 04.06.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_SEQUENTIAL_STATEMENT_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_SEQUENTIAL_STATEMENT_HPP_


#include <eda/vhdl93/ast/util/namespace_alias.hpp>

#include <eda/vhdl93/ast/util/nullary.hpp>
#include <eda/vhdl93/ast/wait_statement.hpp>
#include <eda/vhdl93/ast/assertion_statement.hpp>
#include <eda/vhdl93/ast/report_statement.hpp>
#include <eda/vhdl93/ast/signal_assignment_statement.hpp>
#include <eda/vhdl93/ast/variable_assignment_statement.hpp>
//#include <eda/vhdl93/ast/procedure_call_statement.hpp>
//#include <eda/vhdl93/ast/if_statement.hpp>
#include <eda/vhdl93/ast/case_statement.hpp>
//#include <eda/vhdl93/ast/loop_statement.hpp>
#include <eda/vhdl93/ast/next_statement.hpp>
#include <eda/vhdl93/ast/exit_statement.hpp>
#include <eda/vhdl93/ast/return_statement.hpp>
#include <eda/vhdl93/ast/null_statement.hpp>

#include <boost/spirit/home/x3/support/ast/variant.hpp>


namespace eda { namespace vhdl93 { namespace ast {


struct if_statement;
struct loop_statement;


// sequential_statement ::=                                                [§ 8]
//       wait_statement
//     | assertion_statement
//     | report_statement
//     | signal_assignment_statement
//     | variable_assignment_statement
//     | procedure_call_statement
//     | if_statement
//     | case_statement
//     | loop_statement
//     | next_statement
//     | exit_statement
//     | return_statement
//     | null_statement
struct sequential_statement : x3::variant<
    nullary,
    wait_statement,
    assertion_statement,
    report_statement,
    signal_assignment_statement,
    variable_assignment_statement,
//    procedure_call_statement,
    x3::forward_ast<if_statement>,
    case_statement,
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


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_SEQUENTIAL_STATEMENT_HPP_ */
