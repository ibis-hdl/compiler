/*
 * architecture_statement_part.hpp
 *
 *  Created on: 21.06.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_ARCHITECTURE_STATEMENT_PART_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_ARCHITECTURE_STATEMENT_PART_HPP_


#include <eda/vhdl/ast/node/concurrent_statement.hpp>
#include <vector>


namespace eda { namespace vhdl { namespace ast {


struct architecture_statement_part : std::vector<ast::concurrent_statement> { };


} } } // namespace eda.vhdl.ast


#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_ARCHITECTURE_STATEMENT_PART_HPP_ */
