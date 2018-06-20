/*
 * entity_statement_part.hpp
 *
 *  Created on: 19.06.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_ENTITY_STATEMENT_PART_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_ENTITY_STATEMENT_PART_HPP_


#include <eda/vhdl/ast/util/variant.hpp>

#include <eda/vhdl/ast/util/nullary.hpp>
#include <eda/vhdl/ast/concurrent_assertion_statement.hpp>
#include <eda/vhdl/ast/concurrent_procedure_call_statement.hpp>
#include <eda/vhdl/ast/process_statement.hpp>
#include <vector>


namespace eda { namespace vhdl { namespace ast {


using entity_statement = variant<
    ast::nullary,
    ast::concurrent_assertion_statement,
    ast::concurrent_procedure_call_statement,   // passive_concurrent_procedure_call_statement
    ast::process_statement                      // passive_process_statement
>;


struct entity_statement_part : std::vector<ast::entity_statement> { };


} } } // namespace eda.vhdl.ast


#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_ENTITY_STATEMENT_PART_HPP_ */
