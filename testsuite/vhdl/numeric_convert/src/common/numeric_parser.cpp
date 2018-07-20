/*
 * numeric_parser.cpp
 *
 *  Created on: 29.05.2018
 *      Author: olaf
 */

#include <testsuite/vhdl_numeric_convert/numeric_parser.hpp>

#include <eda/vhdl/parser/grammar_def.hpp>
#include <eda/vhdl/parser/parser_config.hpp>

#include <iostream>


namespace testsuite {

namespace detail {


template<typename AttrType, typename ParserType>
std::tuple<bool, AttrType> parse(ParserType const &numeric_parser, std::string const &input, AttrType &attr)
{
    parser::iterator_type iter = std::begin(input);
    parser::iterator_type end  = std::end(input);

    /* using different iterator_types causes linker errors, see e.g.
     * [linking errors while separate parser using boost spirit x3](
     *  https://stackoverflow.com/questions/40496357/linking-errors-while-separate-parser-using-boost-spirit-x3) */
    static_assert(std::integral_constant<bool,
               std::is_same<decltype(iter), parser::iterator_type>::value
            && std::is_same<decltype(end),  parser::iterator_type>::value
        >::value,
        "iterator types must be the same"
    );

    parser::position_cache<parser::iterator_type> position_cache(input);
    parser::error_handler_type error_handler(std::cerr, position_cache);

    auto const parser =
        x3::with<parser::error_handler_tag>(std::ref(error_handler)) [
            numeric_parser
        ];

    bool parse_ok = false;

    try {
        parse_ok = x3::phrase_parse(iter, end, parser, parser::skipper, attr);

        if (parse_ok) {
            if (iter != end) {
                error_handler(iter, "Full Match Error! "
                                    "unparsed input left:\n"
                                    + std::string(iter, end));
            }
        }
    } catch(x3::expectation_failure<parser::iterator_type> const& e) {
        error_handler(e.where(), "Caught expectation_failure! Expecting "
                                 + e.which() + " here: '"
                                 + std::string(e.where(), input.end()) + "'\n");
    }

    return std::make_tuple(
        parse_ok && (iter == end),
        attr
    );
}


} // namespace detail


std::tuple<bool, ast::bit_string_literal>
parse_bit_string_literal(std::string const &input)
{
    auto const parser = parser::bit_string_literal;
    ast::bit_string_literal attr;

    return detail::parse(parser, input, attr);
}


std::tuple<bool, ast::decimal_literal>
parse_decimal_literal(std::string const &input)
{
    auto const parser = parser::decimal_literal;
    ast::decimal_literal attr;

    return detail::parse(parser, input, attr);
}


std::tuple<bool, ast::based_literal>
parse_based_literal(std::string const &input)
{
    auto const parser = parser::based_literal;
    ast::based_literal attr;

    return detail::parse(parser, input, attr);
}


} // namespace testsuite


