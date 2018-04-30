/*
 * waveform_element.hpp
 *
 *  Created on: 13.05.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_WAVEFORM_ELEMENT_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_WAVEFORM_ELEMENT_HPP_


#include <eda/vhdl/ast/util/position_tagged.hpp>

#include <eda/vhdl/ast/expression.hpp>
#include <eda/vhdl/ast/util/variant.hpp>
#include <eda/vhdl/ast/util/optional.hpp>


namespace eda { namespace vhdl { namespace ast {


struct waveform_element_form : variant<
    ast::expression,
    ast::keyword_token  // NULL
>
{
    using base_type::base_type;
    using base_type::operator=;
};


struct waveform_element : position_tagged
{

    waveform_element_form               form;
    optional<ast::expression>           time_expression;

};


} } } // namespace eda.vhdl.ast


#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_WAVEFORM_ELEMENT_HPP_ */
