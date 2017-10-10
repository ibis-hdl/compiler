/*
 * literal.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_LITERAL_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_LITERAL_HPP_


#include <eda/vhdl/ast/util/namespace_alias.hpp>

#include <eda/vhdl/ast/util/nullary.hpp>
#include <eda/vhdl/ast/numeric_literal.hpp>
#include <eda/vhdl/ast/enumeration_literal.hpp>
#include <eda/vhdl/ast/string_literal.hpp>
#include <eda/vhdl/ast/bit_string_literal.hpp>
#include <eda/vhdl/ast/keyword_token.hpp>

#include <boost/spirit/home/x3/support/ast/variant.hpp>


namespace eda { namespace vhdl { namespace ast {


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


} } } // namespace eda.vhdl.ast


#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_LITERAL_HPP_ */