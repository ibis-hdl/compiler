/*
 * conditional_signal_assignment.hpp
 *
 *  Created on: 16.06.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_CONDITIONAL_SIGNAL_ASSIGNMENT_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_CONDITIONAL_SIGNAL_ASSIGNMENT_HPP_


#include <eda/vhdl93/ast/util/namespace_alias.hpp>
#include <eda/vhdl93/ast/util/position_tagged.hpp>

#include <eda/vhdl93/ast/target.hpp>
#include <eda/vhdl93/ast/options.hpp>
#include <eda/vhdl93/ast/conditional_waveforms.hpp>

#include <boost/spirit/home/x3/support/ast/variant.hpp>


namespace eda { namespace vhdl93 { namespace ast {


struct conditional_signal_assignment : position_tagged
{
    ast::target                     target;
    ast::options                    options;
    ast::conditional_waveforms      conditional_waveforms;
};


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_CONDITIONAL_SIGNAL_ASSIGNMENT_HPP_ */
