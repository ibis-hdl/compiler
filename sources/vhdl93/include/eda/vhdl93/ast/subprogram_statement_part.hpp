/*
 * subprogram_statement_part.hpp
 *
 *  Created on: 06.06.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_SUBPROGRAM_STATEMENT_PART_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_SUBPROGRAM_STATEMENT_PART_HPP_


#include <eda/vhdl93/ast/namespace_alias.hpp>
#include <eda/vhdl93/ast/position_tagged.hpp>

#include <eda/vhdl93/ast/sequence_of_statements.hpp>
#include <vector>


namespace eda { namespace vhdl93 { namespace ast {


using subprogram_statement_part = sequence_of_statements;


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_SUBPROGRAM_STATEMENT_PART_HPP_ */
