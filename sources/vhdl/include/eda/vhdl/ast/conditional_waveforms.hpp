/*
 * conditional_waveforms.hpp
 *
 *  Created on: 16.06.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_CONDITIONAL_WAVEFORMS_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_CONDITIONAL_WAVEFORMS_HPP_


#include <eda/vhdl/ast/util/position_tagged.hpp>

#include <eda/vhdl/ast/expression.hpp>
#include <eda/vhdl/ast/util/optional.hpp>
#include <eda/vhdl/ast/waveform.hpp>
#include <vector>


namespace eda { namespace vhdl { namespace ast {


struct conditional_waveforms : position_tagged
{
    struct chunk
    {
        ast::waveform                           waveform;
        ast::expression                         condition;
    };

    std::vector<chunk>                          chunks;
    ast::waveform                               waveform;
    optional<ast::expression>                   condition;
};


} } } // namespace eda.vhdl.ast


#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_CONDITIONAL_WAVEFORMS_HPP_ */
