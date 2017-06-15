/*
 * entity_tag.hpp
 *
 *  Created on: 16.05.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_ENTITY_TAG_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_ENTITY_TAG_HPP_


#include <eda/vhdl93/ast/util/namespace_alias.hpp>

#include <eda/vhdl93/ast/util/nullary.hpp>
#include <eda/vhdl93/ast/simple_name.hpp>
#include <eda/vhdl93/ast/character_literal.hpp>
#include <eda/vhdl93/ast/operator_symbol.hpp>

#include <boost/spirit/home/x3/support/ast/variant.hpp>


namespace eda { namespace vhdl93 { namespace ast {


#if 0
using entity_tag = x3::variant<
    nullary,
    simple_name,
    character_literal,
    operator_symbol
>;
#else
struct entity_tag : x3::variant<
    nullary,
    simple_name,
    character_literal,
    operator_symbol
>
{
    using base_type::base_type;
    using base_type::operator=;
};
#endif


} } } // namespace eda.vhdl93.ast



#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_ENTITY_TAG_HPP_ */
