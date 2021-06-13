#include <testsuite/vhdl/numeric_convert/numeric_parser.hpp>

#include <ibis/vhdl/parser/parser_config.hpp>
#include <ibis/vhdl/parser/grammar_def.hpp>

#include <ibis/vhdl/parser/error_handler.hpp>
#include <ibis/vhdl/parser/context.hpp>

#include <iostream>

namespace testsuite {

template <typename IteratorT>
std::tuple<bool, ast::bit_string_literal> literal_parser<IteratorT>::bit_string_literal(
    position_proxy& position_cache_proxy) const
{
    auto const parser = ibis::vhdl::parser::bit_string_literal;
    ast::bit_string_literal attr;

    return parse(parser, attr, position_cache_proxy);
}

template <typename IteratorT>
std::tuple<bool, ast::decimal_literal> literal_parser<IteratorT>::decimal_literal(
    position_proxy& position_cache_proxy) const
{
    auto const parser = ibis::vhdl::parser::decimal_literal;
    ast::decimal_literal attr;

    return parse(parser, attr, position_cache_proxy);
}

template <typename IteratorT>
std::tuple<bool, ast::based_literal> literal_parser<IteratorT>::based_literal(
    position_proxy& position_cache_proxy) const
{
    auto const parser = ibis::vhdl::parser::based_literal;
    ast::based_literal attr;

    return parse(parser, attr, position_cache_proxy);
}

template <typename IteratorT>
template <typename ParserType, typename AttrType>
std::tuple<bool, AttrType> literal_parser<IteratorT>::parse(ParserType const& numeric_parser,
                                                            AttrType& attr,
                                                            position_proxy& position_cache_proxy) const
{
    parser::context ctx;
    parser::error_handler_type error_handler{ std::cerr, ctx, position_cache_proxy };

    // clang-format off
    auto const parser =
        x3::with<parser::position_cache_tag>(std::ref(position_cache_proxy))[
            x3::with<parser::error_handler_tag>(std::ref(error_handler))[
                numeric_parser
            ]
        ];
    // clang-format on

    auto [iter, end] = position_cache_proxy.range();

    // using different iterator_types causes linker errors, see e.g.
    // [linking errors while separate parser using boost spirit x3](
    //  https://stackoverflow.com/questions/40496357/linking-errors-while-separate-parser-using-boost-spirit-x3)
    //
    static_assert(std::is_same_v<decltype(iter), parser::iterator_type>,
                  "iterator types must be the same");

    bool parse_ok = false;

    try {
        parse_ok = x3::phrase_parse(iter, end, parser, parser::skipper, attr);

        if (parse_ok) {
            if (iter != end) {
                error_handler(iter,
                              "Full Match Error! "
                              "unparsed input left:\n" +
                                  std::string(iter, end));
            }
        }
    }
    catch (x3::expectation_failure<parser::iterator_type> const& e) {
        error_handler(e.where(), "Caught expectation_failure! Expecting " + e.which() + " here: '" +
                                     std::string(e.where(), end) + "'\n");
    }

    return std::tuple{ parse_ok && (iter == end), attr };
}

}  // namespace testsuite

//
// Explicit template instantiation
//
namespace testsuite {

template class literal_parser<parser::iterator_type>;

}
