/*
 * block_statement_part.hpp
 *
 *  Created on: 19.06.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_BLOCK_STATEMENT_PART_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_BLOCK_STATEMENT_PART_HPP_


#include <eda/vhdl/ast/util/namespace_alias.hpp>

//FORWARD #include <eda/vhdl/ast/concurrent_statement.hpp>
#include <vector>


namespace eda { namespace vhdl { namespace ast {


struct concurrent_statement;


/**
 * Ast node cyclic dependency as:
 *
 * \dot
 * digraph concurrent_statement  {
 *   concurrent_statement -> block_statement;
 *   block_statement -> block_statement_part;
 *   block_statement_part -> concurrent_statement [label="forward"];
 * }
 * \enddot
 */
struct block_statement_part : std::vector<ast::concurrent_statement> { };


} } } // namespace eda.vhdl.ast


#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_BLOCK_STATEMENT_PART_HPP_ */
