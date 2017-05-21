/*
 * discrete_range.hpp
 *
 *  Created on: 21.05.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_DISCRETE_RANGE_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_DISCRETE_RANGE_HPP_


#include <eda/vhdl93/ast/namespace_alias.hpp>

#include <eda/vhdl93/ast/nullary.hpp>
#include <eda/vhdl93/ast/range.hpp>
#include <eda/vhdl93/ast/subtype_indication.hpp>

#include <boost/spirit/home/x3/support/ast/variant.hpp>


namespace eda { namespace vhdl93 { namespace ast {


using discrete_subtype_indication = ast::subtype_indication;


struct discrete_range : x3::variant<
    discrete_subtype_indication,
    range
>
{
    using base_type::base_type;
    using base_type::operator=;
};


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_DISCRETE_RANGE_HPP_ */
