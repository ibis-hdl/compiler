/*
 * entity_statement_part.hpp
 *
 *  Created on: 19.06.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_ENTITY_STATEMENT_PART_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_ENTITY_STATEMENT_PART_HPP_


#include <eda/vhdl93/ast/util/namespace_alias.hpp>

#include <eda/vhdl93/ast/util/nullary.hpp>
#include <eda/vhdl93/ast/concurrent_assertion_statement.hpp>
#include <eda/vhdl93/ast/concurrent_procedure_call_statement.hpp>
#include <eda/vhdl93/ast/process_statement.hpp>
#include <vector>

#include <boost/spirit/home/x3/support/ast/variant.hpp>


namespace eda { namespace vhdl93 { namespace ast {


struct entity_statement : x3::variant<
    ast::nullary,
    ast::concurrent_assertion_statement,
    ast::concurrent_procedure_call_statement,   // passive_concurrent_procedure_call_statement
    ast::process_statement                      // passive_process_statement
>
{
    using base_type::base_type;
    using base_type::operator=;
};


struct entity_statement_part : std::vector<ast::entity_statement> { };


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_ENTITY_STATEMENT_PART_HPP_ */
