/*
 * signal_assignment_statement.hpp
 *
 *  Created on: 18.05.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_SIGNAL_ASSIGNMENT_STATEMENT_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_SIGNAL_ASSIGNMENT_STATEMENT_HPP_


#include <eda/vhdl93/ast/namespace_alias.hpp>
#include <eda/vhdl93/ast/position_tagged.hpp>

#include <eda/vhdl93/ast/label.hpp>
#include <eda/vhdl93/ast/target.hpp>
#include <eda/vhdl93/ast/delay_mechanism.hpp>
#include <eda/vhdl93/ast/waveform.hpp>
#include <eda/vhdl93/ast/optional.hpp>


namespace eda { namespace vhdl93 { namespace ast {


struct signal_assignment_statement : position_tagged
{
    optional<ast::label>                    label;
    ast::target                             target;
    optional<ast::delay_mechanism>          delay_mechanism;
    ast::waveform                           waveform;
};


} } } // namespace eda.vhdl93.ast



#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_SIGNAL_ASSIGNMENT_STATEMENT_HPP_ */
