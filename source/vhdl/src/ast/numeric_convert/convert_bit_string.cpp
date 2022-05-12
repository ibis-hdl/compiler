#include <ibis/vhdl/ast/numeric_convert/convert_bit_string.hpp>
#include <ibis/vhdl/ast/numeric_convert/filter_range.hpp>
#include <ibis/vhdl/ast/numeric_convert/dbg_trace.hpp>

#include <ibis/vhdl/diagnostic_handler.hpp>

#include <ibis/vhdl/ast/node/bit_string_literal.hpp>
#include <ibis/vhdl/ast/util/string_span.hpp>

#include <ibis/vhdl/ast/literal_printer.hpp>
#include <ibis/vhdl/type.hpp>

#include <ibis/util/cxx_bug_fatal.hpp>
#include <ibis/compiler/compiler_support.hpp>

#include <ibis/namespace_alias.hpp>  // IWYU pragma: keep

// IWYU replaces a lot of other header, we stay with this one
#include <boost/spirit/home/x3.hpp>  // IWYU pragma: keep

#include <boost/locale/format.hpp>
#include <boost/locale/message.hpp>

#include <cmath>
#include <algorithm>
#include <limits>
#include <iterator>
#include <numeric>  // accumulate
#include <string>
#include <string_view>
#include <type_traits>
#include <iostream>

namespace /* anonymous */ {

namespace x3 = boost::spirit::x3;

template <typename T, typename IteratorT = ibis::vhdl::parser::iterator_type>
auto const as = [](auto p) { return x3::any_parser<IteratorT, T>{ x3::as_parser(p) }; };

using namespace std::literals;
auto const literal_name = "bit string literal"sv;

}  // namespace

namespace ibis::vhdl::ast {

template <typename IntegerT>
convert_bit_string<IntegerT>::convert_bit_string(diagnostic_handler_type& diagnostic_handler_)
    : report_error{ diagnostic_handler_ }
{
}

template <typename IntegerT>
typename convert_bit_string<IntegerT>::return_type convert_bit_string<IntegerT>::operator()(
    ast::bit_string_literal const& node) const
{
    using boost::locale::format;
    using boost::locale::translate;

    auto const parse = [&](ast::bit_string_literal::base_specifier base, auto const& literal) {
        using base_specifier = ast::bit_string_literal::base_specifier;
        auto const parser = [](base_specifier base_spec, auto iter_t) {
            using iterator_type = decltype(iter_t);
            switch (base_spec) {
                case base_specifier::bin: {
                    using parser_type = x3::uint_parser<integer_type, 2>;
                    parser_type const parse_bin = parser_type{};
                    return as<integer_type, iterator_type>(parse_bin);
                }
                case base_specifier::oct: {
                    using parser_type = x3::uint_parser<integer_type, 8>;
                    parser_type const parse_oct = parser_type{};
                    return as<integer_type, iterator_type>(parse_oct);
                }
                case base_specifier::hex: {
                    using parser_type = x3::uint_parser<integer_type, 16>;
                    parser_type const parse_hex = parser_type{};
                    return as<integer_type, iterator_type>(parse_hex);
                }
                default:  // cxx_unreachable_bug
                    cxx_unreachable_bug_triggered();
            }
        };

        auto const range_f = numeric_convert::detail::filter_range(literal);
        auto iter = std::cbegin(range_f);
        auto const end = std::cend(range_f);

        integer_type attribute = 0;

        bool parse_ok = x3::parse(iter, end, parser(base, iter) >> x3::eoi, attribute);

        if constexpr ((false)) {
            dbg_trace(literal, range_f, parse_ok, attribute);
        }

        if (!parse_ok) {
            using error_type = typename vhdl::diagnostic_handler<parser::iterator_type>::error_type;
            auto constexpr parser_error = error_type::parser;

            // parse failed - can't fit the integer_type, iter is rewind to begin.
            report_error(              // --
                node.literal.begin(),  // --
                (format(translate("in {1} the integer number can't fit the numeric type")) %
                 literal_name)
                    .str(),
                parser_error);
            std::tuple{ false, 0 };
        }

        return std::tuple{ parse_ok && (iter == end), attribute };
    };

    return parse(node.base_type, node.literal);
}

}  // namespace ibis::vhdl::ast

// ----------------------------------------------------------------------------
// Explicit template instantiation
// ----------------------------------------------------------------------------
namespace ibis::vhdl::ast {

template class convert_bit_string<intrinsic::signed_integer_type>;

}  // namespace ibis::vhdl::ast