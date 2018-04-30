/*
 * conditional_signal_assignment.hpp
 *
 *  Created on: 16.06.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_CONDITIONAL_SIGNAL_ASSIGNMENT_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_CONDITIONAL_SIGNAL_ASSIGNMENT_HPP_


#include <eda/vhdl/ast/util/position_tagged.hpp>

#include <eda/vhdl/ast/target.hpp>
#include <eda/vhdl/ast/options.hpp>
#include <eda/vhdl/ast/conditional_waveforms.hpp>


namespace eda { namespace vhdl { namespace ast {


struct conditional_signal_assignment : position_tagged
{
    ast::target                     target;
    ast::options                    options;
    ast::conditional_waveforms      conditional_waveforms;
};


} } } // namespace eda.vhdl.ast


#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_CONDITIONAL_SIGNAL_ASSIGNMENT_HPP_ */
