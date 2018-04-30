/*
 * case_statement_alternative.hpp
 *
 *  Created on: 05.06.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_CASE_STATEMENT_ALTERNATIVE_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_CASE_STATEMENT_ALTERNATIVE_HPP_


#include <eda/vhdl/ast/util/position_tagged.hpp>

#include <eda/vhdl/ast/choices.hpp>
#include <eda/vhdl/ast/sequence_of_statements.hpp>


namespace eda { namespace vhdl { namespace ast {


struct case_statement_alternative : position_tagged
{
    ast::choices                    choices;
    ast::sequence_of_statements     sequence_of_statements;
};


} } } // namespace eda.vhdl.ast


#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_CASE_STATEMENT_ALTERNATIVE_HPP_ */
