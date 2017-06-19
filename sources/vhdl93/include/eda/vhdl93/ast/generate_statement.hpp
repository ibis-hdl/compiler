/*
 * generate_statement.hpp
 *
 *  Created on: 20.06.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_GENERATE_STATEMENT_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_GENERATE_STATEMENT_HPP_


#include <eda/vhdl93/ast/util/namespace_alias.hpp>
#include <eda/vhdl93/ast/util/position_tagged.hpp>

#include <eda/vhdl93/ast/label.hpp>
#include <eda/vhdl93/ast/generation_scheme.hpp>
#include <eda/vhdl93/ast/block_declarative_part.hpp>
#include <eda/vhdl93/ast/concurrent_statement.hpp>
#include <eda/vhdl93/ast/util/optional.hpp>
#include <vector>


namespace eda { namespace vhdl93 { namespace ast {


struct generate_statement : position_tagged
{
    ast::label                              label;
    ast::generation_scheme                  generation_scheme;
    ast::block_declarative_part             block_declarative_parts; // { block_declarative_item }
    std::vector<ast::concurrent_statement>  concurrent_statements;
    optional<ast::label>                    end_label;
};


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_GENERATE_STATEMENT_HPP_ */
