/*
 * if_statement.hpp
 *
 *  Created on: 20.06.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_IF_STATEMENT_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_IF_STATEMENT_HPP_


#include <eda/vhdl93/ast/util/namespace_alias.hpp>
#include <eda/vhdl93/ast/util/position_tagged.hpp>

#include <eda/vhdl93/ast/label.hpp>
#include <eda/vhdl93/ast/condition.hpp>
#include <eda/vhdl93/ast/sequence_of_statements.hpp>
#include <eda/vhdl93/ast/concurrent_statement.hpp>
#include <eda/vhdl93/ast/util/optional.hpp>
#include <vector>


namespace eda { namespace vhdl93 { namespace ast {


struct if_statement : position_tagged
{
    struct elsif_chunk {
        ast::condition                      condition;
        ast::sequence_of_statements         sequence_of_statements;
    };

    optional<ast::label>            label;
    ast::condition                  if_condition;
    ast::sequence_of_statements     then_sequence_of_statements;
    std::vector<elsif_chunk>        elseif_chunks;
    ast::sequence_of_statements     else_sequence_of_statements;
    optional<ast::label>            end_label;
};


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_IF_STATEMENT_HPP_ */
