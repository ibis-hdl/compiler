/*
 * architecture_statement_part.hpp
 *
 *  Created on: 21.06.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_ARCHITECTURE_STATEMENT_PART_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_ARCHITECTURE_STATEMENT_PART_HPP_


#include <eda/vhdl93/ast/util/namespace_alias.hpp>

#include <eda/vhdl93/ast/concurrent_statement.hpp>
#include <vector>


namespace eda { namespace vhdl93 { namespace ast {


struct architecture_statement_part : std::vector<ast::concurrent_statement> { };


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_ARCHITECTURE_STATEMENT_PART_HPP_ */
