/*
 * waveform.hpp
 *
 *  Created on: 13.05.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_WAVEFORM_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_WAVEFORM_HPP_


#include <eda/vhdl/ast/util/variant.hpp>

#include <eda/vhdl/ast/node/waveform_element.hpp>
#include <vector>


namespace eda { namespace vhdl { namespace ast {


struct waveform_element_list : std::vector<waveform_element> { };


struct waveform : variant<
    waveform_element_list,
    ast::keyword_token  // UNAFFECTED
>
{
    using base_type::base_type;
    using base_type::operator=;
};


} } } // namespace eda.vhdl.ast



#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_WAVEFORM_HPP_ */
