/*
 * concurrent_statement.hpp
 *
 *  Created on: 17.06.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_CONCURRENT_STATEMENT_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_CONCURRENT_STATEMENT_HPP_


#include <eda/vhdl/ast/util/variant.hpp>

#include <eda/vhdl/ast/util/nullary.hpp>
#include <eda/vhdl/ast/block_statement.hpp>
#include <eda/vhdl/ast/process_statement.hpp>
#include <eda/vhdl/ast/concurrent_procedure_call_statement.hpp>
#include <eda/vhdl/ast/concurrent_assertion_statement.hpp>
#include <eda/vhdl/ast/concurrent_signal_assignment_statement.hpp>
#include <eda/vhdl/ast/component_instantiation_statement.hpp>
#include <eda/vhdl/ast/generate_statement.hpp>


namespace eda { namespace vhdl { namespace ast {


struct concurrent_statement : variant<
    ast::nullary,
    ast::block_statement,
    ast::process_statement,
    ast::concurrent_procedure_call_statement,
    ast::concurrent_assertion_statement,
    ast::concurrent_signal_assignment_statement,
    ast::component_instantiation_statement,
    ast::generate_statement
>
{
    using base_type::base_type;
    using base_type::operator=;
};


} } } // namespace eda.vhdl.ast


#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_CONCURRENT_STATEMENT_HPP_ */
