/*
 * sequence_of_statements.hpp
 *
 *  Created on: 05.06.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_SEQUENCE_OF_STATEMENTS_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_SEQUENCE_OF_STATEMENTS_HPP_


#include <eda/vhdl93/ast/util/namespace_alias.hpp>
#include <eda/vhdl93/ast/util/position_tagged.hpp>

#include <eda/vhdl93/ast/sequential_statement.hpp>
#include <vector>


namespace eda { namespace vhdl93 { namespace ast {


struct sequence_of_statements : std::vector<ast::sequential_statement> { };


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_SEQUENCE_OF_STATEMENTS_HPP_ */
