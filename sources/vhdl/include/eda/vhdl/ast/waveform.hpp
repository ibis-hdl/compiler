/*
 * waveform.hpp
 *
 *  Created on: 13.05.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_WAVEFORM_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_WAVEFORM_HPP_


#include <eda/vhdl/ast/util/namespace_alias.hpp>
#include <eda/vhdl/ast/util/position_tagged.hpp>

#include <eda/vhdl/ast/waveform_element.hpp>
#include <vector>
#include <boost/spirit/home/x3/support/ast/variant.hpp>


namespace eda { namespace vhdl { namespace ast {


struct waveform_element_list : std::vector<waveform_element> { };


struct waveform : x3::variant<
    waveform_element_list,
    ast::keyword_token  // UNAFFECTED
>
{
    using base_type::base_type;
    using base_type::operator=;
};


} } } // namespace eda.vhdl.ast



#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_WAVEFORM_HPP_ */
