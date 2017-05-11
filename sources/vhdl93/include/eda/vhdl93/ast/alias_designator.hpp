/*
 * alias_designator.hpp
 *
 *  Created on: 11.05.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_ALIAS_DESIGNATOR_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_ALIAS_DESIGNATOR_HPP_


#include <eda/vhdl93/ast/namespace_alias.hpp>

#include <eda/vhdl93/ast/nullary.hpp>
#include <eda/vhdl93/ast/identifier.hpp>
#include <eda/vhdl93/ast/character_literal.hpp>
#include <eda/vhdl93/ast/operator_symbol.hpp>

#include <boost/spirit/home/x3/support/ast/variant.hpp>


namespace eda { namespace vhdl93 { namespace ast {

#if 0
using alias_designator = x3::variant<
    nullary,
    identifier,
    character_literal,
    operator_symbol
>;
#else
struct alias_designator : x3::variant<
    nullary,
    identifier,
    character_literal,
    operator_symbol
>
{
    using base_type::base_type;
    using base_type::operator=;
};
#endif

} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_ALIAS_DESIGNATOR_HPP_ */
