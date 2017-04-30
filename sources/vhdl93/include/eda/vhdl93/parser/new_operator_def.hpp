/*
 * operator.hpp
 *
 *  Created on: 18.04.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_PARSER_OPERATOR_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_PARSER_OPERATOR_HPP_


#include <eda/vhdl93/parser/operator.hpp>

#include <eda/vhdl93/parser/spirit_x3.hpp>


/*
 * VHDL operators
 */
namespace eda { namespace vhdl93 { namespace parser {


/*
 * Rule Instances
 */
logical_operator_type const logical_operator { "logical_operator" };
logical_operator_option_type const logical_operator_option { "logical_operator" };
unary_miscellaneous_operator_type const unary_miscellaneous_operator { "miscellaneous_operator" };
multiplying_operator_type const multiplying_operator { "multiplying_operator" };
shift_operator_type const shift_operator { "shift_operator" };


/*
 * Parser operator definitions
 */

struct logical_operator_symbols : x3::symbols<ast::operator_token> {

    logical_operator_symbols() {

        name("logical_operator");

        add("and",  ast::operator_token::and_)
           ("or",   ast::operator_token::or_)
           ("xor",  ast::operator_token::xor_)
           ("xnor", ast::operator_token::xnor)
           ;
    }
} const logical_operator_symbols;

auto const logical_operator_def =
    x3::no_case[ logical_operator_symbols ]
    ;


struct logical_operator_option_symbols : x3::symbols<ast::operator_token> {

    logical_operator_option_symbols() {

        name("logical_operator");

        add("nand", ast::operator_token::nand)
           ("nor",  ast::operator_token::nor)
           ;
    }
} const logical_operator_option_symbols;

auto const logical_operator_option_def =
    x3::no_case[ logical_operator_option_symbols ]
    ;


struct relational_operator_symbols : x3::symbols<ast::operator_token> {

    relational_operator_symbols() {

        name("relational_operator");

        add("=",  ast::operator_token::equal)
           ("/=", ast::operator_token::not_equals)
           ("<",  ast::operator_token::less)
           ("<=", ast::operator_token::less_equals)
           (">",  ast::operator_token::greater)
           (">=", ast::operator_token::greater_equals)
           ;
    }
} const relational_operator;




struct unary_miscellaneous_operator_symbols : x3::symbols<ast::operator_token> {

    unary_miscellaneous_operator_symbols() {

        name("miscellaneous_operator");

        add("abs", ast::operator_token::abs)
           ("not", ast::operator_token::not_)
           ;
    }
} const unary_miscellaneous_operator_symbols;

auto const unary_miscellaneous_operator_def =
    x3::no_case[ unary_miscellaneous_operator_symbols ]
    ;


struct binary_miscellaneous_operator_symbols : x3::symbols<ast::operator_token> {

    binary_miscellaneous_operator_symbols() {

        name("miscellaneous_operator");

        add("**", ast::operator_token::exponent)
           ;
    }
} const binary_miscellaneous_operator;



struct adding_operator_symbols : x3::symbols<ast::operator_token> {

    adding_operator_symbols() {

        name("adding_operator");

        add("+", ast::operator_token::add)
           ("-", ast::operator_token::sub)
           ("&", ast::operator_token::concat)
           ;
    }
} const adding_operator;


struct multiplying_operator_symbols : x3::symbols<ast::operator_token> {

    multiplying_operator_symbols() {

        name("multiplying_operator");

        add("*",   ast::operator_token::mul)
           ("/",   ast::operator_token::div)
           ("mod", ast::operator_token::mod)
           ("rem", ast::operator_token::rem)
           ;
    }
} const multiplying_operator_symbols;

auto const multiplying_operator_def =
    x3::no_case[ multiplying_operator_symbols ]
    ;


struct shift_operator_symbols : x3::symbols<ast::operator_token> {

    shift_operator_symbols() {

        name("shift_operator");

        add("sll", ast::operator_token::sll)
           ("srl", ast::operator_token::srl)
           ("sla", ast::operator_token::sla)
           ("sra", ast::operator_token::sra)
           ("rol", ast::operator_token::rol)
           ("ror", ast::operator_token::ror)
           ;
    }
} const shift_operator_symbols;

auto const shift_operator_def =
    x3::no_case[ shift_operator_symbols ]
    ;


struct sign_operator_symbols : x3::symbols<ast::operator_token> {

    sign_operator_symbols() {

        name("sign_operator");

        add("+", ast::operator_token::sign_pos)
           ("-", ast::operator_token::sign_neg)
           ;
    }
} const sign_operator;


BOOST_SPIRIT_DEFINE(
    logical_operator,
    logical_operator_option,
    unary_miscellaneous_operator,
    multiplying_operator,
    shift_operator
)


} } } // namespace eda.vhdl93.parser


/*
 * VHDL operators API
 */
namespace eda { namespace vhdl93 { namespace parser { namespace api {

    logical_operator_type const& logical_operator()
    {
        return parser::logical_operator;
    }

    logical_operator_option_type const& logical_operator_option()
    {
        return parser::logical_operator_option;
    }

    relational_operator_type const& relational_operator()
    {
        return parser::relational_operator;
    }

    unary_miscellaneous_operator_type const& unary_miscellaneous_operator()
    {
        return parser::unary_miscellaneous_operator;
    }

    binary_miscellaneous_operator_type const& binary_miscellaneous_operator()
    {
        return parser::binary_miscellaneous_operator;
    }

    adding_operator_type const& adding_operator()
    {
        return parser::adding_operator;
    }

    multiplying_operator_type const& multiplying_operator()
    {
        return parser::multiplying_operator;
    }

    shift_operator_type const& shift_operator()
    {
        return parser::shift_operator;
    }

    sign_operator_type const& sign_operator()
    {
        return parser::sign_operator;
    }


} } } } // namespace eda.vhdl93.parser.api


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_PARSER_OPERATOR_HPP_ */
