/*
 * conditional_waveforms.hpp
 *
 *  Created on: 16.06.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_CONDITIONAL_WAVEFORMS_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_CONDITIONAL_WAVEFORMS_HPP_


#include <eda/vhdl93/ast/util/namespace_alias.hpp>
#include <eda/vhdl93/ast/util/position_tagged.hpp>

#include <eda/vhdl93/ast/waveform.hpp>
#include <eda/vhdl93/ast/expression.hpp>
#include <eda/vhdl93/ast/util/optional.hpp>
#include <vector>

#include <boost/spirit/home/x3/support/ast/variant.hpp>


namespace eda { namespace vhdl93 { namespace ast {


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


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_CONDITIONAL_WAVEFORMS_HPP_ */
