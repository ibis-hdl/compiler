/*
 * loop_statement.hpp
 *
 *  Created on: 19.06.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_LOOP_STATEMENT_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_LOOP_STATEMENT_HPP_


#include <eda/vhdl/ast/util/namespace_alias.hpp>
#include <eda/vhdl/ast/util/position_tagged.hpp>

#include <eda/vhdl/ast/label.hpp>
#include <eda/vhdl/ast/iteration_scheme.hpp>
#include <eda/vhdl/ast/sequence_of_statements.hpp>
#include <eda/vhdl/ast/util/optional.hpp>


namespace eda { namespace vhdl { namespace ast {


struct loop_statement : position_tagged
{
    optional<ast::label>            label;
    optional<ast::iteration_scheme> iteration_scheme;
    ast::sequence_of_statements     sequence_of_statements;
    optional<ast::label>            end_label;
};


} } } // namespace eda.vhdl.ast


#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_LOOP_STATEMENT_HPP_ */
