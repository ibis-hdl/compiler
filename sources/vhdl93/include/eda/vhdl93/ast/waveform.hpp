/*
 * waveform.hpp
 *
 *  Created on: 13.05.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_WAVEFORM_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_WAVEFORM_HPP_


#include <eda/vhdl93/ast/util/namespace_alias.hpp>
#include <eda/vhdl93/ast/util/position_tagged.hpp>

#include <eda/vhdl93/ast/waveform_element.hpp>
#include <vector>
#include <boost/spirit/home/x3/support/ast/variant.hpp>


namespace eda { namespace vhdl93 { namespace ast {


struct waveform_element_list : std::vector<waveform_element> { };


struct waveform : x3::variant<
    waveform_element_list,
    ast::keyword_token  // UNAFFECTED
>
{
    using base_type::base_type;
    using base_type::operator=;
};


} } } // namespace eda.vhdl93.ast



#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_WAVEFORM_HPP_ */
