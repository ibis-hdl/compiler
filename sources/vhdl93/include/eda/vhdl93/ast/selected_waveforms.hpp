/*
 * selected_waveforms.hpp
 *
 *  Created on: 04.06.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_SELECTED_WAVEFORMS_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_SELECTED_WAVEFORMS_HPP_


#include <eda/vhdl93/ast/namespace_alias.hpp>
#include <eda/vhdl93/ast/position_tagged.hpp>

#include <eda/vhdl93/ast/waveform.hpp>
#include <eda/vhdl93/ast/choices.hpp>
#include <vector>


namespace eda { namespace vhdl93 { namespace ast {


// Non-BNF, artificial element for selected_waveforms
struct selected_waveform : position_tagged
{
    ast::waveform           waveform;
    ast::choices            choices;
};


struct selected_waveforms : std::vector<selected_waveform> { };


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_SELECTED_WAVEFORMS_HPP_ */
