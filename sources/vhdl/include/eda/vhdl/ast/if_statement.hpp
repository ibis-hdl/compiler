/*
 * if_statement.hpp
 *
 *  Created on: 20.06.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_IF_STATEMENT_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_IF_STATEMENT_HPP_


#include <eda/vhdl/ast/concurrent_statement.hpp>
#include <eda/vhdl/ast/condition.hpp>
#include <eda/vhdl/ast/label.hpp>
#include <eda/vhdl/ast/sequence_of_statements.hpp>
#include <eda/vhdl/ast/util/namespace_alias.hpp>
#include <eda/vhdl/ast/util/optional.hpp>
#include <eda/vhdl/ast/util/position_tagged.hpp>
#include <vector>


namespace eda { namespace vhdl { namespace ast {


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


} } } // namespace eda.vhdl.ast


#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_IF_STATEMENT_HPP_ */
