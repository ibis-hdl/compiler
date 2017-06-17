/*
 * selected_signal_assignment.hpp
 *
 *  Created on: 17.06.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_SELECTED_SIGNAL_ASSIGNMENT_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_SELECTED_SIGNAL_ASSIGNMENT_HPP_


#include <eda/vhdl93/ast/util/namespace_alias.hpp>
#include <eda/vhdl93/ast/util/position_tagged.hpp>

#include <eda/vhdl93/ast/expression.hpp>
#include <eda/vhdl93/ast/options.hpp>
#include <eda/vhdl93/ast/selected_waveforms.hpp>


namespace eda { namespace vhdl93 { namespace ast {


struct selected_signal_assignment : position_tagged
{
    ast::expression             expression;
    ast::options                options;
    ast::selected_waveforms     selected_waveforms;
};


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_SELECTED_SIGNAL_ASSIGNMENT_HPP_ */
