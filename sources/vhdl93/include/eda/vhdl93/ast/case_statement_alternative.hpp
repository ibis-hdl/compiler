/*
 * case_statement_alternative.hpp
 *
 *  Created on: 05.06.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_CASE_STATEMENT_ALTERNATIVE_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_CASE_STATEMENT_ALTERNATIVE_HPP_


#include <eda/vhdl93/ast/util/namespace_alias.hpp>
#include <eda/vhdl93/ast/position_tagged.hpp>

#include <eda/vhdl93/ast/choices.hpp>
#include <eda/vhdl93/ast/sequence_of_statements.hpp>


namespace eda { namespace vhdl93 { namespace ast {


struct case_statement_alternative : position_tagged
{
    ast::choices                    choices;
    ast::sequence_of_statements     sequence_of_statements;
};


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_CASE_STATEMENT_ALTERNATIVE_HPP_ */
