/*
 * operators.hpp
 *
 *  Created on: 18.04.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_PARSER_OPERATORS_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_PARSER_OPERATORS_HPP_

#include <eda/vhdl93/parser/spirit_x3.hpp>

#include <eda/vhdl93/parser/namespace_alias.hpp>
#include <eda/vhdl93/ast/operator_token.hpp>



namespace eda { namespace vhdl93 { namespace parser {


/*
 * Parser helper
 */
template<typename T>
auto as_type = [](auto p) { return x3::rule<struct _, T>{ "as" } = x3::as_parser(p); };


/*
 * Parser operator definitions
 */

struct logical_operator_symbols : x3::symbols<ast::operator_token> {

    logical_operator_symbols() {

        name("logical_operator");

        add("and",  ast::operator_token::AND)
           ("or",   ast::operator_token::OR)
           ("xor",  ast::operator_token::XOR)
           ("xnor", ast::operator_token::XNOR)
           ;
    }
} const logical_operator_symbols;

auto const logical_operator = as_type<ast::operator_token>(
        x3::no_case[ logical_operator_symbols ]
    );


struct logical_operator_option_symbols : x3::symbols<ast::operator_token> {

    logical_operator_option_symbols() {

        name("logical_operator");

        add("nand", ast::operator_token::NAND)
           ("nor",  ast::operator_token::NOR)
           ;
    }
} const logical_operator_option_symbols;

auto const logical_operator_option = as_type<ast::operator_token>(
        x3::no_case[ logical_operator_option_symbols ]
    );


struct relational_operator_symbols : x3::symbols<ast::operator_token> {

    relational_operator_symbols() {

        name("relational_operator");

        add("=",  ast::operator_token::EQUAL)
           ("/=", ast::operator_token::NOT_EQUALS)
           ("<",  ast::operator_token::LESS)
           ("<=", ast::operator_token::LESS_EQUALS)
           (">",  ast::operator_token::GREATER)
           (">=", ast::operator_token::GREATER_EQUALS)
           ;
    }
} const relational_operator;


struct unary_miscellaneous_operator_symbols : x3::symbols<ast::operator_token> {

    unary_miscellaneous_operator_symbols() {

        name("miscellaneous_operator");

        add("abs", ast::operator_token::ABS)
           ("not", ast::operator_token::NOT)
           ;
    }
} const unary_miscellaneous_operator_symbols;

auto const unary_miscellaneous_operator = as_type<ast::operator_token>(
        x3::no_case[ unary_miscellaneous_operator_symbols ]
    );


struct binary_miscellaneous_operator_symbols : x3::symbols<ast::operator_token> {

    binary_miscellaneous_operator_symbols() {

        name("miscellaneous_operator");

        add("**", ast::operator_token::EXPONENT)
           ;
    }
} const binary_miscellaneous_operator;


struct adding_operator_symbols : x3::symbols<ast::operator_token> {

    adding_operator_symbols() {

        name("adding_operator");

        add("+", ast::operator_token::ADD)
           ("-", ast::operator_token::SUB)
           ("&", ast::operator_token::CONCAT)
           ;
    }
} const adding_operator;


struct multiplying_operator_symbols : x3::symbols<ast::operator_token> {

    multiplying_operator_symbols() {

        name("multiplying_operator");

        add("*",   ast::operator_token::MUL)
           ("/",   ast::operator_token::DIV)
           ("mod", ast::operator_token::MOD)
           ("rem", ast::operator_token::REM)
           ;
    }
} const multiplying_operator_symbols;

auto const multiplying_operator = as_type<ast::operator_token>(
        x3::no_case[ multiplying_operator_symbols ]
    );


struct shift_operator_symbols : x3::symbols<ast::operator_token> {

    shift_operator_symbols() {

        name("shift_operator");

        add("sll", ast::operator_token::SLL)
           ("srl", ast::operator_token::SRL)
           ("sla", ast::operator_token::SLA)
           ("sra", ast::operator_token::SRA)
           ("rol", ast::operator_token::ROL)
           ("ror", ast::operator_token::ROR)
           ;
    }
} const shift_operator_symbols;

auto const shift_operator = as_type<ast::operator_token>(
        x3::no_case[ shift_operator_symbols ]
    );


struct sign_operator_symbols : x3::symbols<ast::operator_token> {

    sign_operator_symbols() {

        name("sign_operator");

        add("+", ast::operator_token::SIGN_POS)
           ("-", ast::operator_token::SIGN_NEG)
           ;
    }
} const sign;


} } } // namespace eda.vhdl93.parser



#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_PARSER_OPERATORS_HPP_ */
