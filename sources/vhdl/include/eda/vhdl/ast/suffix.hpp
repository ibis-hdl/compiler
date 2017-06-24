/*
 * suffix.hpp
 *
 *  Created on: 02.04.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_SUFFIX_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_SUFFIX_HPP_


#include <eda/vhdl/ast/util/namespace_alias.hpp>

#include <eda/vhdl/ast/util/nullary.hpp>
#include <eda/vhdl/ast/keyword_token.hpp>
#include <eda/vhdl/ast/character_literal.hpp>
#include <eda/vhdl/ast/operator_symbol.hpp>
#include <eda/vhdl/ast/simple_name.hpp>

#include <boost/spirit/home/x3/support/ast/variant.hpp>


namespace eda { namespace vhdl { namespace ast {

#if 0
using suffix = x3::variant<
    nullary,
    simple_name,
    character_literal,
    operator_symbol,
    keyword_token
>;
#else
struct suffix : x3::variant<
    nullary,
    simple_name,
    character_literal,
    operator_symbol,
    keyword_token
>
{
    using base_type::base_type;
    using base_type::operator=;
};
#endif

} } } // namespace eda.vhdl.ast


#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_SUFFIX_HPP_ */
