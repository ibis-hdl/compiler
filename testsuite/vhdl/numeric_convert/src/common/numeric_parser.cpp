/*
 * numeric_parser.cpp
 *
 *  Created on: 29.05.2018
 *      Author: olaf
 */

#include <testsuite/vhdl_numeric_convert/numeric_parser.hpp>

#include <eda/vhdl/parser/parser_config.hpp>
#include <eda/vhdl/parser/grammar_def.hpp>

#include <iostream>


namespace testsuite {

template<typename IteratorT>
std::tuple<bool, ast::bit_string_literal>
literal_parser<IteratorT>::bit_string_literal(position_proxy const& cache) const
{
    auto const parser = vhdl::parser::bit_string_literal;
    ast::bit_string_literal attr;

    return parse(parser, attr, cache);
}


template<typename IteratorT>
std::tuple<bool, ast::decimal_literal>
literal_parser<IteratorT>::decimal_literal(position_proxy const& cache) const
{
    auto const parser = vhdl::parser::decimal_literal;
    ast::decimal_literal attr;

    return parse(parser, attr, cache);
}


template<typename IteratorT>
std::tuple<bool, ast::based_literal>
literal_parser<IteratorT>::based_literal(position_proxy const& cache) const
{
    auto const parser = vhdl::parser::based_literal;
    ast::based_literal attr;

    return parse(parser, attr, cache);
}


template<typename IteratorT>
template<typename ParserType, typename AttrType>
std::tuple<bool, AttrType> literal_parser<IteratorT>::parse(
    ParserType const& numeric_parser, AttrType& attr,
    position_proxy const& cache_proxy) const
{
    parser::error_handler_type error_handler{ std::cerr, cache_proxy };

    auto const parser =
        x3::with<parser::error_handler_tag>(std::ref(error_handler)) [
            numeric_parser
        ];

    auto [iter, end] = cache_proxy.range();

#if 1
#if defined(__clang__) // GCC fails here
        /* using different iterator_types causes linker errors, see e.g.
         * [linking errors while separate parser using boost spirit x3](
         *  https://stackoverflow.com/questions/40496357/linking-errors-while-separate-parser-using-boost-spirit-x3) */
        static_assert(std::is_same<decltype(iter), parser::iterator_type>::value,
                      "iterator types must be the same"
        );
#endif
#endif

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
                                 + std::string(e.where(), end) + "'\n");
    }

    return std::make_tuple(
        parse_ok && (iter == end),
        attr
    );
}

} // namespace testsuite


/*
 * Explicit template instantiation
 */
namespace testsuite {

template class literal_parser<parser::iterator_type>;

} // namespace testsuite
