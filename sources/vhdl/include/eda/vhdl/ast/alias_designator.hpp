/*
 * alias_designator.hpp
 *
 *  Created on: 11.05.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_ALIAS_DESIGNATOR_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_ALIAS_DESIGNATOR_HPP_


#include <eda/vhdl/ast/util/namespace_alias.hpp>

#include <eda/vhdl/ast/util/nullary.hpp>
#include <eda/vhdl/ast/identifier.hpp>
#include <eda/vhdl/ast/character_literal.hpp>
#include <eda/vhdl/ast/operator_symbol.hpp>

#include <boost/spirit/home/x3/support/ast/variant.hpp>


namespace eda { namespace vhdl { namespace ast {

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

} } } // namespace eda.vhdl.ast


#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_ALIAS_DESIGNATOR_HPP_ */
