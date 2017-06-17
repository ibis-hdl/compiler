/*
 * concurrent_statement.hpp
 *
 *  Created on: 17.06.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_CONCURRENT_STATEMENT_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_CONCURRENT_STATEMENT_HPP_


#include <eda/vhdl93/ast/util/namespace_alias.hpp>

#include <eda/vhdl93/ast/util/nullary.hpp>
//#include <eda/vhdl93/ast/block_statement.hpp>
//#include <eda/vhdl93/ast/process_statement.hpp>
#include <eda/vhdl93/ast/concurrent_procedure_call_statement.hpp>
#include <eda/vhdl93/ast/concurrent_assertion_statement.hpp>
#include <eda/vhdl93/ast/concurrent_signal_assignment_statement.hpp>
//#include <eda/vhdl93/ast/component_instantiation_statement.hpp>
//#include <eda/vhdl93/ast/generate_statement.hpp>

#include <boost/spirit/home/x3/support/ast/variant.hpp>


namespace eda { namespace vhdl93 { namespace ast {


struct concurrent_statement : x3::variant<
    nullary,
    //block_statement,
    //process_statement,
    concurrent_procedure_call_statement,
    concurrent_assertion_statement,
    concurrent_signal_assignment_statement
    //component_instantiation_statement,
    //generate_statement
>
{
    using base_type::base_type;
    using base_type::operator=;
};


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_CONCURRENT_STATEMENT_HPP_ */
