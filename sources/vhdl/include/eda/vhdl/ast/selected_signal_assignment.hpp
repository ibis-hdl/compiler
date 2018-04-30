/*
 * selected_signal_assignment.hpp
 *
 *  Created on: 17.06.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_SELECTED_SIGNAL_ASSIGNMENT_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_SELECTED_SIGNAL_ASSIGNMENT_HPP_


#include <eda/vhdl/ast/util/position_tagged.hpp>

#include <eda/vhdl/ast/expression.hpp>
#include <eda/vhdl/ast/target.hpp>
#include <eda/vhdl/ast/options.hpp>
#include <eda/vhdl/ast/selected_waveforms.hpp>


namespace eda { namespace vhdl { namespace ast {


struct selected_signal_assignment : position_tagged
{
    ast::expression             expression;
    ast::target                 target;
    ast::options                options;
    ast::selected_waveforms     selected_waveforms;
};


} } } // namespace eda.vhdl.ast


#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_SELECTED_SIGNAL_ASSIGNMENT_HPP_ */
