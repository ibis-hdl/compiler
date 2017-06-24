/*
 * generate_statement.hpp
 *
 *  Created on: 20.06.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_GENERATE_STATEMENT_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_GENERATE_STATEMENT_HPP_


#include <eda/vhdl/ast/block_declarative_part.hpp>
#include <eda/vhdl/ast/generation_scheme.hpp>
#include <eda/vhdl/ast/label.hpp>
#include <eda/vhdl/ast/util/namespace_alias.hpp>
#include <eda/vhdl/ast/util/optional.hpp>
#include <eda/vhdl/ast/util/position_tagged.hpp>
#include <vector>


namespace eda { namespace vhdl { namespace ast {


struct concurrent_statement;


/**
 * Ast node cyclic dependency as:
 *
 * \dot
 *  digraph generate_statement  {
 *   concurrent_statement -> generate_statement;
 *   generate_statement -> concurrent_statement [ label="forward"];
 * }
 * \enddot
 */
struct generate_statement : position_tagged
{
    ast::label                              label;
    ast::generation_scheme                  generation_scheme;
    ast::block_declarative_part             block_declarative_parts; // { block_declarative_item }
    std::vector<ast::concurrent_statement>  concurrent_statements;
    optional<ast::label>                    end_label;
};


} } } // namespace eda.vhdl.ast


#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_GENERATE_STATEMENT_HPP_ */
