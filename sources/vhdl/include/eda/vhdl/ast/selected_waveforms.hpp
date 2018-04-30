/*
 * selected_waveforms.hpp
 *
 *  Created on: 04.06.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_SELECTED_WAVEFORMS_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_SELECTED_WAVEFORMS_HPP_


#include <eda/vhdl/ast/util/position_tagged.hpp>

#include <eda/vhdl/ast/waveform.hpp>
#include <eda/vhdl/ast/choices.hpp>
#include <vector>


namespace eda { namespace vhdl { namespace ast {


// Non-BNF, artificial element for selected_waveforms
struct selected_waveform : position_tagged
{
    ast::waveform           waveform;
    ast::choices            choices;
};


struct selected_waveforms : std::vector<selected_waveform> { };


} } } // namespace eda.vhdl.ast


#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_SELECTED_WAVEFORMS_HPP_ */
