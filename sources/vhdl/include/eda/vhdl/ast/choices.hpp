/*
 * choice.hpp
 *
 *  Created on: 04.06.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_CHOICES_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_CHOICES_HPP_


#include <eda/vhdl/ast/util/namespace_alias.hpp>

#include <eda/vhdl/ast/util/nullary.hpp>
#include <eda/vhdl/ast/simple_name.hpp>
#include <eda/vhdl/ast/discrete_range.hpp>
#include <eda/vhdl/ast/simple_expression.hpp>
#include <eda/vhdl/ast/keyword_token.hpp>
#include <vector>

#include <boost/spirit/home/x3/support/ast/variant.hpp>


namespace eda { namespace vhdl { namespace ast {


// only use by choices, hence no own header
struct choice : x3::variant<
    nullary,
    simple_name,
    discrete_range,
    simple_expression,
    keyword_token       // OTHERS
>
{
    using base_type::base_type;
    using base_type::operator=;
};


struct choices : std::vector<choice> { };


} } } // namespace eda.vhdl.ast


#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_CHOICES_HPP_ */
