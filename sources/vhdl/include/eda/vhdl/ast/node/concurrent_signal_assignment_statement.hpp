/*
 * concurrent_signal_assignment_statement.hpp
 *
 *  Created on: 17.06.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_CONCURRENT_SIGNAL_ASSIGNMENT_STATEMENT_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_CONCURRENT_SIGNAL_ASSIGNMENT_STATEMENT_HPP_


#include <eda/vhdl/ast/util/position_tagged.hpp>
#include <eda/vhdl/ast/util/variant.hpp>

#include <eda/vhdl/ast/node/label.hpp>
#include <eda/vhdl/ast/node/conditional_signal_assignment.hpp>
#include <eda/vhdl/ast/node/selected_signal_assignment.hpp>


namespace eda { namespace vhdl { namespace ast {


struct concurrent_signal_assignment_statement : position_tagged
{
    optional<ast::label>                label;
    bool                                postponed;
    variant<
        ast::conditional_signal_assignment,
        ast::selected_signal_assignment
    >                                   signal_assignment;

    concurrent_signal_assignment_statement()
    : postponed{}
    { }
};


} } } // namespace eda.vhdl.ast


#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_CONCURRENT_SIGNAL_ASSIGNMENT_STATEMENT_HPP_ */
