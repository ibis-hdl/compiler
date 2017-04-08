/*
 * literal.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_LITERAL_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_LITERAL_HPP_


#include <boost/spirit/home/x3/support/ast/variant.hpp>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct bit_string_literal;
struct enumeration_literal;
enum class keyword_token;
struct numeric_literal;
struct string_literal;

struct literal :
    x3::variant<
        x3::forward_ast<bit_string_literal>,
        x3::forward_ast<enumeration_literal>,
        x3::forward_ast<keyword_token>,
        x3::forward_ast<numeric_literal>,
        x3::forward_ast<string_literal>
    >
{
    using base_type::base_type;
    using base_type::operator=;
};


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_LITERAL_HPP_ */
