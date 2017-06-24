/*
 * concurrent_signal_assignment_statement.hpp
 *
 *  Created on: 17.06.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_CONCURRENT_SIGNAL_ASSIGNMENT_STATEMENT_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_CONCURRENT_SIGNAL_ASSIGNMENT_STATEMENT_HPP_


#include <eda/vhdl/ast/util/namespace_alias.hpp>
#include <eda/vhdl/ast/util/position_tagged.hpp>

#include <eda/vhdl/ast/label.hpp>
#include <eda/vhdl/ast/conditional_signal_assignment.hpp>
#include <eda/vhdl/ast/selected_signal_assignment.hpp>


namespace eda { namespace vhdl { namespace ast {


struct concurrent_signal_assignment_statement : position_tagged
{
    optional<ast::label>                label;
    bool                                postponed;
    x3::variant<
        ast::conditional_signal_assignment,
        ast::selected_signal_assignment
    >                                   signal_assignment;

    concurrent_signal_assignment_statement() : postponed{}
    { }
};


} } } // namespace eda.vhdl.ast


#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_CONCURRENT_SIGNAL_ASSIGNMENT_STATEMENT_HPP_ */
