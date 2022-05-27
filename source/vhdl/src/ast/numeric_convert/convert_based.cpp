#include <ibis/vhdl/ast/numeric_convert/convert_based.hpp>
#include <ibis/vhdl/ast/numeric_convert/filter_range.hpp>
#include <ibis/vhdl/ast/numeric_convert/dbg_trace.hpp>

#include <ibis/vhdl/diagnostic_handler.hpp>

#include <ibis/vhdl/ast/node/based_literal.hpp>
#include <ibis/vhdl/ast/literal_printer.hpp>
#include <ibis/vhdl/type.hpp>

#include <ibis/util/cxx_bug_fatal.hpp>
#include <ibis/compiler/compiler_support.hpp>

#include <ibis/namespace_alias.hpp>  // IWYU pragma: keep

#include <ibis/compiler/warnings_off.hpp>
// IWYU replaces a lot of other header, we stay with this one
#include <boost/spirit/home/x3.hpp>  // IWYU pragma: keep
#include <ibis/compiler/warnings_on.hpp>

#include <boost/range/join.hpp>

#include <ibis/compiler/warnings_off.hpp>  // [-Wsign-conversion]
#include <boost/locale/format.hpp>
#include <boost/locale/message.hpp>
#include <ibis/compiler/warnings_on.hpp>

#include <cmath>
#include <algorithm>
#include <limits>
#include <iterator>
#include <numeric>  // accumulate
#include <string>
#include <string_view>
#include <type_traits>
#include <iostream>

namespace ibis::vhdl::ast::detail {

template <typename T>
struct real_policies : x3::ureal_policies<T> {
    static bool const allow_leading_dot = false;
    static bool const allow_trailing_dot = false;
    static bool const expect_dot = false;
};

}  // namespace ibis::vhdl::ast::detail

namespace /* anonymous */ {

namespace x3 = boost::spirit::x3;

template <typename T, typename IteratorT = ibis::vhdl::parser::iterator_type>
auto const as = [](auto derived_parser) {
    return x3::any_parser<IteratorT, T>{ x3::as_parser(derived_parser) };
};

using namespace std::literals;
auto const literal_name = "based literal"sv;

}  // namespace

namespace ibis::vhdl::ast {

template <typename IntegerT, typename RealT>
convert_based<IntegerT, RealT>::convert_based(diagnostic_handler_type& diagnostic_handler_)
    : diagnostic_handler{ diagnostic_handler_ }
{
}

template <typename IntegerT, typename RealT>
std::tuple<bool, std::uint32_t> convert_based<IntegerT, RealT>::parse_base(
    ast::based_literal const& literal) const
{
    using boost::locale::format;
    using boost::locale::translate;

    auto const range_f = numeric_convert::detail::filter_range(literal.base);
    auto iter = std::cbegin(range_f);
    auto const end = std::cend(range_f);

    std::uint32_t base = 0;
    // base is in decimal notation
    bool const parse_ok = x3::parse(iter, end, x3::uint_ >> x3::eoi, base);

    if (!parse_ok) {
        // parse failed - can't fit the target_type, iter is rewind to begin.
        diagnostic_handler.parser_error(                                                // --
            literal.base.begin(),                                                       // --
            (format(translate("in {1} the base specifier can't fit the numeric type"))  // --
             % literal_name)
                .str());
        return std::tuple{ false, 0 };
    }

    return std::tuple{ parse_ok && (iter == end), base };
}

template <typename IntegerT, typename RealT>
std::tuple<bool, std::uint64_t> convert_based<IntegerT, RealT>::parse_integer(
    unsigned base, ast::based_literal const& literal) const
{
    using boost::locale::format;
    using boost::locale::translate;

    auto const parse = [&](unsigned base, auto const& integer_part) {
        auto const parser = [](unsigned base_spec, auto iter_t) {
            using iterator_type = decltype(iter_t);
            switch (base_spec) {
                case 2: {
                    using parser_type = x3::uint_parser<integer_type, 2>;
                    parser_type const parse_bin = parser_type{};
                    return as<integer_type, iterator_type>(parse_bin);
                }
                case 8: {
                    using parser_type = x3::uint_parser<integer_type, 8>;
                    parser_type const parse_oct = parser_type{};
                    return as<integer_type, iterator_type>(parse_oct);
                }
                case 10: {
                    using parser_type = x3::uint_parser<integer_type, 10>;
                    parser_type const parse_dec = parser_type{};
                    return as<integer_type, iterator_type>(parse_dec);
                }
                case 16: {
                    using parser_type = x3::uint_parser<integer_type, 16>;
                    parser_type const parse_hex = parser_type{};
                    return as<integer_type, iterator_type>(parse_hex);
                }
                default:  // cxx_unreachable_bug
                    cxx_unreachable_bug_triggered();
            }
        };

        auto const range_f = numeric_convert::detail::filter_range(integer_part);
        auto iter = std::cbegin(range_f);
        auto const end = std::cend(range_f);

        std::uint64_t integer = 0;
        bool const parse_ok = x3::parse(iter, end, parser(base, iter) >> x3::eoi, integer);

        if (!parse_ok) {
            // parse failed - can't fit the target_type, iter is rewind to begin.
            diagnostic_handler.parser_error(                                              // --
                literal.number.integer_part.begin(),                                      // --
                (format(translate("in {1} the integer part can't fit the numeric type"))  // --
                 % literal_name)
                    .str());
            return std::tuple{ false, integer };
        }

        return std::tuple{ parse_ok && (iter == end), integer };
    };

    return parse(base, literal.number.integer_part);
}

template <typename IntegerT, typename RealT>
std::tuple<bool, double> convert_based<IntegerT, RealT>::parse_fractional(
    unsigned base, ast::based_literal const& literal) const
{
    using boost::locale::format;
    using boost::locale::translate;

    auto range_f{ numeric_convert::detail::filter_range(literal.number.fractional_part) };
    auto iter = std::cbegin(range_f);
    auto const last = std::cend(range_f);

    double pow = base;

    // FixMe: there are no (parser) checks, we depend on VHDL parser!

    // naive implementation of fractional part calculation
    auto const fractional =
        std::accumulate(iter, last, 0.0, [&pow, base](double acc, char hex_chr) {
            // We trust on VHDL parser's 1st pass to simplify converting char to their integer
            // value, hence no checks are required.
            // ToDo: Std. C++ and Spirit.X3 offers utilities for converting chars - maybe use them.
            // clang-format off
            auto const hex2dec = [](char chr) {
                switch (chr) {
                    case '0':   return  0;
                    case '1':   return  1;
                    case '2':   return  2;
                    case '3':   return  3;
                    case '4':   return  4;
                    case '5':   return  5;
                    case '6':   return  6;
                    case '7':   return  7;
                    case '8':   return  8;
                    case '9':   return  9;
                    case 'a':   [[fallthrough]];
                    case 'A':   return 10;
                    case 'b':   [[fallthrough]];
                    case 'B':   return 11;
                    case 'c':   [[fallthrough]];
                    case 'C':   return 12;
                    case 'd':   [[fallthrough]];
                    case 'D':   return 13;
                    case 'e':   [[fallthrough]];
                    case 'E':   return 14;
                    case 'f':   [[fallthrough]];
                    case 'F':   return 15;
                    default:    cxx_unreachable_bug_triggered();
                }
            };
            // clang-format on
            double dig = hex2dec(hex_chr);
            dig /= pow;
            pow *= static_cast<double>(base);
            return acc + dig;
        });

    // during accumulation a numeric IEEE754 errors may occur
    if (!std::isnormal(fractional)) {
        diagnostic_handler.numeric_error(                                                 // --
            literal.number.fractional_part.begin(),                                       // --
            (format(translate(                                                            // --
                 "in {1} numeric error occurred during calculation of fractional part"))  // --
             % literal_name)
                .str());
        return std::tuple{ false, fractional };
    }

    return std::tuple{ true, fractional };
}

template <typename IntegerT, typename RealT>
std::tuple<bool, std::int32_t> convert_based<IntegerT, RealT>::parse_exponent(
    ast::based_literal const& literal) const
{
    using boost::locale::format;
    using boost::locale::translate;

    if (literal.number.exponent.empty()) {
        // no need to parse
        return std::tuple{ true, 0 };
    }

    auto const range_f = numeric_convert::detail::filter_range(literal.number.exponent);
    auto iter = std::cbegin(range_f);
    auto const end = std::cend(range_f);

    using x3::char_;
    using x3::int_;  // exponent is in decimal notation

    // IEEE1076-93 Ch. 13.4, specifies for decimal_literal the forbidden
    // negative sign for the exponent of integer types.
    // Note: rule valid for based integer and real!
    auto const exp = x3::rule<struct _, std::int32_t>{} = x3::omit[char_("Ee")] >> int_;

    std::int32_t exponent = 0;
    bool const parse_ok = x3::parse(iter, end, exp >> x3::eoi, exponent);

    if (!parse_ok) {
        // parse failed - can't fit the target_type, iter is rewind to begin.
        diagnostic_handler.parser_error(                                               // --
            literal.number.exponent.begin(),                                           // --
            (format(translate("in {1} the exponent part can't fit the numeric type"))  // --
             % literal_name)
                .str());
        return std::tuple{ false, 0 };
    }

    // XXX Check on valid range

    using numeric_type_specifier = ast::based_literal::numeric_type_specifier;

    // The top-level VHDL parser is strict enough so that this will not happen this time.
    if (literal.number.type_specifier == numeric_type_specifier::integer) {
        // internal error: our top-level VHDL parser has failed
        assert(exponent >= 0  // --
               && "An exponent for a based integer literal must not have a minus sign.");
    }

    return std::tuple{ parse_ok && (iter == end), exponent };
}

template <typename IntegerT, typename RealT>
std::tuple<bool, double> convert_based<IntegerT, RealT>::parse_real10(
    ast::based_literal const& literal) const
{
    using boost::locale::format;
    using boost::locale::translate;

    // it's better to use X3's base10 double parser to avoid maschine's epsilon errors
    // FixMe: Candidate for C++20 range
    static std::string const dot{ "." };
    auto const range =
        boost::join(boost::join(literal.number.integer_part, dot), literal.number.fractional_part);
    auto const range_f = numeric_convert::detail::filter_range(range);
    auto iter = std::cbegin(range_f);
    auto const end = std::cend(range_f);

    x3::real_parser<double, detail::real_policies<double>> const real_parser;

    double real = 0;
    bool const parse_ok = x3::parse(iter, end, real_parser >> x3::eoi, real);

    if (!parse_ok) {
        // parse failed - can't fit the target_type, iter is rewind to begin.
        diagnostic_handler.parser_error(                                             // --
            literal.number.integer_part.begin(),                                     // --
            (format(translate("in {1} the real number can't fit the numeric type"))  //--
             % literal_name)
                .str());

        return std::tuple{ false, 0 };
    }

    return std::tuple{ parse_ok && (iter == end), real };
}

template <typename IntegerT, typename RealT>
bool convert_based<IntegerT, RealT>::supported_base(unsigned base) const
{
    // clang-format off
    switch (base) {
        // NOLINTNEXTLINE(bugprone-branch-clone)
        case 2:  [[fallthrough]];
        case 8:  [[fallthrough]];
        case 10: [[fallthrough]];
        case 16: return true;
        default: return false;
    }
    // clang-format on
}

template <typename IntegerT, typename RealT>
typename convert_based<IntegerT, RealT>::return_type convert_based<IntegerT, RealT>::operator()(
    ast::based_literal const& node) const
{
    using boost::locale::format;
    using boost::locale::translate;

    using numeric_type_specifier = ast::based_literal::numeric_type_specifier;

    auto const failure_return_value = [&node]() -> convert_based::return_type {
        switch (node.numeric_type()) {
            case numeric_type_specifier::integer: {
                return std::tuple{ false, integer_type(0) };
            }
            case numeric_type_specifier::real: {
                return std::tuple{ false, real_type(0) };
            }
            default:  // unreachable_bug_triggered
                cxx_unreachable_bug_triggered();
        }
    };

    bool parse_ok = false;

    // ------------------------------------------------------------------------
    // BASE
    std::uint32_t base = 0;
    std::tie(parse_ok, base) = parse_base(node);

    if (!parse_ok) {
        // parse error rendering done before
        return failure_return_value();
    }
    if (!supported_base(base)) {
        diagnostic_handler.unsupported(  // --
            node.base.begin(),           // --
            (format(translate("in {1} the base specifier of \'{2}\' isn't supported; "
                              "only 2, 8, 10 and 16!"))  // --
             % literal_name                              // {1}
             % base)                                     // {2}
                .str());
        return failure_return_value();
    }

    // ------------------------------------------------------------------------
    // INTEGER
    std::uint64_t integer = 0;

    std::tie(parse_ok, integer) = parse_integer(base, node);

    if (!parse_ok) {
        // parse error rendering done before
        return failure_return_value();
    }

    // ------------------------------------------------------------------------
    // FRACTIONAL (only for based real)
    double fractional = 0;

    if (base != 10U && node.numeric_type() == numeric_type_specifier::real) {
        std::tie(parse_ok, fractional) = parse_fractional(base, node);

        if (!parse_ok) {
            // parse error rendering done before
            return failure_return_value();
        }
    }

    // ------------------------------------------------------------------------
    // base 10 real numeric parser using spirit.X3
    double real10 = 0;

    if (base == 10U && node.numeric_type() == numeric_type_specifier::real) {
        std::tie(parse_ok, real10) = parse_real10(node);

        if (!parse_ok) {
            // parse error rendering done before
            return failure_return_value();
        }
    }

    // ------------------------------------------------------------------------
    // EXPONENT
    std::int32_t exponent = 0;
    std::tie(parse_ok, exponent) = parse_exponent(node);

    if (!parse_ok) {
        // parse error rendering done before
        return failure_return_value();
    }

    // FixMe: Check range of exponent to avoid overflows

    // ------------------------------------------------------------------------
    // combine parts to result

    double const pow = std::pow(base, exponent);

    using numeric_type_specifier = ast::based_literal::numeric_type_specifier;

    switch (node.numeric_type()) {
        case numeric_type_specifier::integer: {
            integer_type result = integer;
            result *= static_cast<integer_type>(pow);
            return std::tuple{ true, result };
        }
        case numeric_type_specifier::real: {
            real_type result = 0;
            if (base == 10) {
                result = real10;
            }
            else {
                // FixMe: uint64 may be more exact as double can represent exactly!
                result = static_cast<double>(integer);
                result += fractional;
            }
            result *= pow;

            return std::tuple{ true, result };
        }
        default:  // unreachable_bug_triggered
            cxx_unreachable_bug_triggered();
    }
}

}  // namespace ibis::vhdl::ast

// ----------------------------------------------------------------------------
// Explicit template instantiation
// ----------------------------------------------------------------------------
namespace ibis::vhdl::ast {

template class convert_based<intrinsic::signed_integer_type, intrinsic::real_type>;

}  // namespace ibis::vhdl::ast
