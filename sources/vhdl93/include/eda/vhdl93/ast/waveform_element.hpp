/*
 * waveform_element.hpp
 *
 *  Created on: 13.05.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_WAVEFORM_ELEMENT_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_WAVEFORM_ELEMENT_HPP_


#include <eda/vhdl93/ast/util/namespace_alias.hpp>
#include <eda/vhdl93/ast/position_tagged.hpp>

#include <eda/vhdl93/ast/expression.hpp>
#include <boost/spirit/home/x3/support/ast/variant.hpp>
#include <eda/vhdl93/ast/util/optional.hpp>


namespace eda { namespace vhdl93 { namespace ast {


struct waveform_element_form : x3::variant<
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


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_WAVEFORM_ELEMENT_HPP_ */
