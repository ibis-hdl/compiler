/*
 * process_statement.hpp
 *
 *  Created on: 17.06.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_PROCESS_STATEMENT_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_PROCESS_STATEMENT_HPP_


#include <eda/vhdl/ast/util/namespace_alias.hpp>
#include <eda/vhdl/ast/util/position_tagged.hpp>

#include <eda/vhdl/ast/label.hpp>
#include <eda/vhdl/ast/sensitivity_list.hpp>
#include <eda/vhdl/ast/process_declarative_part.hpp>
#include <eda/vhdl/ast/sequence_of_statements.hpp>

#include <eda/vhdl/ast/util/optional.hpp>


namespace eda { namespace vhdl { namespace ast {


using process_statement_part = ast::sequence_of_statements;


struct process_statement : position_tagged
{
    optional<ast::label>            label;
    bool                            postponed;
    ast::sensitivity_list           sensitivity_list;
    ast::process_declarative_part   declarative_part;
    ast::process_statement_part     statement_part;
    bool                            end_postponed;
    optional<ast::label>            end_label;

    process_statement() : postponed{}, end_postponed{}
    { }
};


} } } // namespace eda.vhdl.ast


#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_PROCESS_STATEMENT_HPP_ */
