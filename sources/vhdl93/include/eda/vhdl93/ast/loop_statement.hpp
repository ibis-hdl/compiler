/*
 * loop_statement.hpp
 *
 *  Created on: 19.06.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_LOOP_STATEMENT_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_LOOP_STATEMENT_HPP_


#include <eda/vhdl93/ast/util/namespace_alias.hpp>
#include <eda/vhdl93/ast/util/position_tagged.hpp>

#include <eda/vhdl93/ast/label.hpp>
#include <eda/vhdl93/ast/iteration_scheme.hpp>
#include <eda/vhdl93/ast/sequence_of_statements.hpp>
#include <eda/vhdl93/ast/util/optional.hpp>


namespace eda { namespace vhdl93 { namespace ast {


struct loop_statement : position_tagged
{
    optional<ast::label>            label;
    ast::iteration_scheme           iteration_scheme;
    ast::sequence_of_statements     sequence_of_statements;
    optional<ast::label>            end_label;
};


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_LOOP_STATEMENT_HPP_ */
