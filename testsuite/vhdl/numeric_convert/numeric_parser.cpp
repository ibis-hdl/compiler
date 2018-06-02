/*
 * numeric_parser.cpp
 *
 *  Created on: 29.05.2018
 *      Author: olaf
 */

#include <eda/vhdl/parser/grammar_def.hpp>
#include <eda/vhdl/parser/parser_config.hpp>
#include <testsuite/vhdl_numeric_convert/numeric_parser.hpp>

#include <iostream>


namespace x3 = boost::spirit::x3;

namespace parser = eda::vhdl::parser;
namespace ast    = eda::vhdl::ast;


namespace detail {


template<typename AttrType, typename ParserType>
std::tuple<bool, AttrType> parse(ParserType const numeric_parser, std::string const &input, AttrType &attr)
{
    parser::iterator_type iter = std::begin(input);
    parser::iterator_type const end = std::cend(input);

    parser::error_handler_type error_handler(iter, end, std::cerr);

    auto const parser_ = x3::with<x3::error_handler_tag>(std::ref(error_handler)) [
        numeric_parser
    ];

    bool parse_ok = false;

    try {
        parse_ok = x3::phrase_parse(iter, end, parser_, parser::skipper, attr);

        if (parse_ok) {
            if (iter != end) {
                error_handler(iter, "Error! Expecting end of input here: ");
            }
        }
    } catch(x3::expectation_failure<parser::iterator_type> const& e) {
        error_handler(e.where(), "Catched Error! Expecting " + e.which() + " here: ");
    }

    return std::make_tuple(
        parse_ok && (iter == end),
        attr
    );
}


}


namespace testsuite {


std::tuple<bool, ast::bit_string_literal>
parse_bit_string_literal(std::string const &input)
{
    ast::bit_string_literal attr;

    return detail::parse(parser::bit_string_literal, input, attr);
}

std::tuple<bool, ast::decimal_literal>
parse_decimal_literal(std::string const &input)
{
    ast::decimal_literal attr;

    return detail::parse(parser::decimal_literal, input, attr);
}


std::tuple<bool, ast::based_literal>
parse_based_literal(std::string const &input)
{
    ast::based_literal attr;

    return detail::parse(parser::based_literal, input, attr);
}


}


