/*
 * literal.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_LITERAL_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_LITERAL_HPP_


#include <eda/vhdl93/ast/util/namespace_alias.hpp>

#include <eda/vhdl93/ast/util/nullary.hpp>
#include <eda/vhdl93/ast/numeric_literal.hpp>
#include <eda/vhdl93/ast/enumeration_literal.hpp>
#include <eda/vhdl93/ast/string_literal.hpp>
#include <eda/vhdl93/ast/bit_string_literal.hpp>
#include <eda/vhdl93/ast/keyword_token.hpp>

#include <boost/spirit/home/x3/support/ast/variant.hpp>


namespace eda { namespace vhdl93 { namespace ast {


// literal ::=
//        numeric_literal
//      | enumeration_literal
//      | string_literal
//      | bit_string_literal
//      | null
#if 0
using literal = x3::variant<
    nullary,
    bit_string_literal,
    enumeration_literal,
    keyword_token,          // NULL
    numeric_literal,
    string_literal
>;
#else
struct literal : x3::variant<
    nullary,
    numeric_literal,
    enumeration_literal,
    string_literal,
    bit_string_literal,
    keyword_token          // NULL
>
{
    // FixMe: only playground/vhdl_expression_eval requires this!
    literal(literal const&) = default;
    literal& operator=(literal const&) = default;

    using base_type::base_type;
    using base_type::operator=;
};
#endif


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_LITERAL_HPP_ */
