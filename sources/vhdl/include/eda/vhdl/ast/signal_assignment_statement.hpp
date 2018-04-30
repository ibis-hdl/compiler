/*
 * signal_assignment_statement.hpp
 *
 *  Created on: 18.05.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_SIGNAL_ASSIGNMENT_STATEMENT_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_SIGNAL_ASSIGNMENT_STATEMENT_HPP_


#include <eda/vhdl/ast/util/position_tagged.hpp>

#include <eda/vhdl/ast/delay_mechanism.hpp>
#include <eda/vhdl/ast/label.hpp>
#include <eda/vhdl/ast/target.hpp>
#include <eda/vhdl/ast/util/optional.hpp>
#include <eda/vhdl/ast/waveform.hpp>


namespace eda { namespace vhdl { namespace ast {


struct signal_assignment_statement : position_tagged
{
    optional<ast::label>                    label;
    ast::target                             target;
    optional<ast::delay_mechanism>          delay_mechanism;
    ast::waveform                           waveform;
};


} } } // namespace eda.vhdl.ast



#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_SIGNAL_ASSIGNMENT_STATEMENT_HPP_ */
