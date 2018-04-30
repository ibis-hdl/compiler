/*
 * sequence_of_statements.hpp
 *
 *  Created on: 05.06.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_SEQUENCE_OF_STATEMENTS_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_SEQUENCE_OF_STATEMENTS_HPP_


#include <eda/vhdl/ast/sequential_statement.hpp>
#include <vector>


namespace eda { namespace vhdl { namespace ast {


struct sequence_of_statements : std::vector<ast::sequential_statement> { };


} } } // namespace eda.vhdl.ast


#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_SEQUENCE_OF_STATEMENTS_HPP_ */
