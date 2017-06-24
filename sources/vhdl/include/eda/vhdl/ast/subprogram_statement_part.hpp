/*
 * subprogram_statement_part.hpp
 *
 *  Created on: 06.06.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_SUBPROGRAM_STATEMENT_PART_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_SUBPROGRAM_STATEMENT_PART_HPP_


#include <eda/vhdl/ast/util/namespace_alias.hpp>
#include <eda/vhdl/ast/util/position_tagged.hpp>

#include <eda/vhdl/ast/sequence_of_statements.hpp>
#include <vector>


namespace eda { namespace vhdl { namespace ast {


using subprogram_statement_part = sequence_of_statements;


} } } // namespace eda.vhdl.ast


#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_SUBPROGRAM_STATEMENT_PART_HPP_ */
