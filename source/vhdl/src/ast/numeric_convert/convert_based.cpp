//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-or-later
//

#include <ibis/vhdl/ast/numeric_convert/convert_based.hpp>
#include <ibis/vhdl/ast/numeric_convert/filter_range.hpp>
#include <ibis/vhdl/ast/numeric_convert/detail/digits_traits.hpp>

#include <ibis/vhdl/ast/numeric_convert/dbg_trace.hpp>

#include <ibis/vhdl/diagnostic_handler.hpp>

#include <ibis/vhdl/ast/node/based_literal.hpp>
#include <ibis/vhdl/ast/literal_printer.hpp>
#include <ibis/vhdl/type.hpp>

#include <ibis/util/cxx_bug_fatal.hpp>

#include <ibis/namespace_alias.hpp>  // IWYU pragma: keep

#include <ibis/util/compiler/warnings_off.hpp>
// IWYU replaces a lot of other header, we stay with this one
#include <boost/spirit/home/x3.hpp>  // IWYU pragma: keep
#include <ibis/util/compiler/warnings_on.hpp>

#include <range/v3/view/join.hpp>
#include <range/v3/range/conversion.hpp>

#include <ibis/util/compiler/warnings_off.hpp>  // [-Wsign-conversion]
#include <boost/locale/format.hpp>
#include <boost/locale/message.hpp>
#include <ibis/util/compiler/warnings_on.hpp>

#include <fmt/format.h>

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

    // convenience alias
    auto const& base_literal = literal.base;
    auto const base_literal_sv = as_string_view(base_literal);

    /// intermediate integer type for base part
    using base_type = std::uint32_t;
    base_type base_attribute = 0;

    // TRANSLATORS: error message for numeric target type
    std::string const error_msg_tr = translate(
        "in {1} the base specifier '{2}' isn't supported; only 2, 8, 10 and 16!");

    auto range_f = numeric_convert::detail::filter_range(base_literal);

    if(ranges::distance(range_f) > std::numeric_limits<base_type>::digits10) {
        // for some very smart people who fill up with leading zeros
        diagnostic_handler.unsupported(                 // --
            base_literal.begin(), base_literal.end(),   // --
            (format(error_msg_tr) % node_name % base_literal_sv).str());
        return { false, base_attribute };
    }

    auto iter = std::begin(range_f);
    auto const end = std::end(range_f);

    bool const parse_ok = x3::parse(iter, end, x3::uint_ >> x3::eoi, base_attribute);

    if (!parse_ok) {
        diagnostic_handler.parser_error(                // --
            base_literal.begin(), base_literal.end(),   // --
            (format(translate("in {1} parse of base specifier '{2}' failed"))  // --
             % node_name % base_literal_sv).str());
        return { false, base_attribute };
    }

    if (!supported_base(base_attribute)) {
        diagnostic_handler.unsupported(                 // --
            base_literal.begin(), base_literal.end(),   // --
            (format(error_msg_tr) % node_name % base_literal_sv).str());
        return { false, base_attribute };
    }

    return { true, base_attribute };
}

template <typename IntegerT, typename RealT>
std::tuple<bool, std::uint64_t> convert_based<IntegerT, RealT>::parse_integer(
    unsigned base, ast::based_literal const& literal) const
{
    using boost::locale::format;
    using boost::locale::translate;

    // select a concrete parser depending the the base specifier
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

    // convenience alias
    auto const& integer_literal = literal.number.integer_part;
    auto const integer_literal_sv = as_string_view(integer_literal);

    // TRANSLATORS: error message for numeric target type
    std::string const error_msg_tr = translate(
        "in {1} integer part '{2}' can't fit the numeric type");

    auto range_f = numeric_convert::detail::filter_range(integer_literal);

    if(ranges::distance(range_f) > std::numeric_limits<integer_type>::digits10) {
        diagnostic_handler.parser_error(                            // --
            integer_literal.begin(), integer_literal.end(),         // --
            (format(error_msg_tr) % node_name % integer_literal_sv).str());
        return { false, 0 };
    }

    auto iter = std::begin(range_f);
    auto const end = std::end(range_f);

    integer_type integer_attribute = 0;
    bool const parse_ok = x3::parse(iter, end, parser(base, iter) >> x3::eoi, integer_attribute);

    if (!parse_ok) {
        diagnostic_handler.parser_error(                                        // --
            integer_literal.begin(), integer_literal.end(),                     // --
            (format(translate("in {1} parse of integer part '{2}' failed"))     // --
            % node_name % integer_literal_sv).str());
        return { false, 0 };
    }

    return { true, integer_attribute };
}

template <typename IntegerT, typename RealT>
std::tuple<bool, double> convert_based<IntegerT, RealT>::parse_fractional(
    unsigned base, ast::based_literal const& literal) const
{
    using boost::locale::format;
    using boost::locale::translate;

    // convenience alias
    auto const& fractional_literal = literal.number.fractional_part;
    auto const fractional_literal_sv = as_string_view(fractional_literal);

    auto range_f{ numeric_convert::detail::filter_range(fractional_literal) };
    auto iter = std::begin(range_f);
    auto const last = std::end(range_f);

    real_type pow = base;

    // naive implementation of fractional part calculation
    auto const fractional =
        std::accumulate(iter, last, 0.0, [&pow, base](real_type acc, char hex_chr) {
            // We trust on VHDL parser's 1st pass to simplify converting char to their integer
            // value, hence no checks are required.
            // Also, see [What's the fastest way to convert hex to integer in C++?](
            // https://stackoverflow.com/questions/34365746/whats-the-fastest-way-to-convert-hex-to-integer-in-c)
            // here we let the compiler decide how o optimize
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
            real_type dig = hex2dec(hex_chr);
            dig /= pow;
            pow *= static_cast<real_type>(base);
            return acc + dig;
        });

    // during accumulation a numeric IEEE754 errors may occur
    if (!std::isnormal(fractional)) {
        diagnostic_handler.numeric_error(                           // --
            fractional_literal.begin(), fractional_literal.end(),   // --
            (format(translate(                                      // --
                "in {1} numeric error occurred during calculation of fractional part '{2}'"))  // --
                % node_name % fractional_literal_sv).str());
        return { false, fractional };
    }

    return { true, fractional };
}

template <typename IntegerT, typename RealT>
std::tuple<bool, std::int32_t> convert_based<IntegerT, RealT>::parse_exponent(
    ast::based_literal const& literal) const
{
    using boost::locale::format;
    using boost::locale::translate;

    // intermediate integer type for exponent part
    // type is unsigned for based, signed for real
    using exponent_type = std::int32_t;
    exponent_type exponent_attribute = 0;

    // convenience alias
    auto const& exponent_literal = literal.number.exponent;
    auto const exponent_literal_sv = as_string_view(exponent_literal);

    // optional exponent is empty
    if (exponent_literal.empty()) {
        // no need to parse
        return { true, exponent_attribute };
    }

    // TRANSLATORS: error message for numeric target type
    std::string const error_msg_tr = translate("in {1} the exponent part '{2}' can't fit the {3} type");

    auto range_f = numeric_convert::detail::filter_range(exponent_literal);

    if(ranges::distance(range_f) > std::numeric_limits<exponent_type>::digits10) {
        diagnostic_handler.parser_error(                        // --
            exponent_literal.begin(), exponent_literal.end(),   // --
            (format(error_msg_tr) % node_name % exponent_literal_sv).str());
        return { false, exponent_attribute };
    }

    // parse attribute
    auto iter = std::begin(range_f);
    auto const end = std::end(range_f);

    auto const exp = x3::rule<struct _, exponent_type>{ node_name.data() } = x3::int_;

    bool const parse_ok = x3::parse(iter, end, exp >> x3::eoi, exponent_attribute);

    if (!parse_ok) {
        diagnostic_handler.parser_error(                                    // --
            exponent_literal.begin(), exponent_literal.end(),               // --
            (format(translate("in {1} parse of exponent '{2}' failed"))     // --
            % node_name % exponent_literal_sv).str());
        return { false, exponent_attribute };
    }

    // there are only integer and real types
    using numeric_type_specifier = ast::based_literal::numeric_type_specifier;
    static_assert(static_cast<unsigned>(numeric_type_specifier::COUNT) == 2, "unexpected count of type specifier");

    // check on valid exponent numeric range
    if (literal.number.type_specifier == numeric_type_specifier::real) {
        // max. exponent for e.g. double 308 as in 1.0e308
        if(exponent_attribute > std::numeric_limits<real_type>::max_exponent10) {
            diagnostic_handler.parser_error(                        // --
                exponent_literal.begin(), exponent_literal.end(),   // --
                (format(error_msg_tr) % node_name % exponent_literal_sv % "real").str());
            return { false, exponent_attribute };
        }
    }
    else {
        // max. exponent for e.g. 32bit integer 9 as in 1e+9
        if(exponent_attribute > std::numeric_limits<integer_type>::digits10) {
            diagnostic_handler.parser_error(                        // --
                exponent_literal.begin(), exponent_literal.end(),   // --
                (format(error_msg_tr) % node_name % exponent_literal_sv % "integer").str());
            return { false, exponent_attribute };
        }
    }

    return { true, exponent_attribute };
}

template <typename IntegerT, typename RealT>
std::tuple<bool, double> convert_based<IntegerT, RealT>::parse_real10(
    ast::based_literal const& literal) const
{
    using boost::locale::format;
    using boost::locale::translate;
    using namespace ranges;
    using namespace std::literals::string_view_literals;

    // ranges-v3 concept: [coliru](https://coliru.stacked-crooked.com/a/530a793796999fab)
    // c++20 range concept [coliru](https://coliru.stacked-crooked.com/a/17f844b879507aed)
    auto const real10_literal = {                               // --
        as_string_view(literal.number.integer_part),            // --
        "."sv , as_string_view(literal.number.fractional_part)  // --
    };

    auto range_f = numeric_convert::detail::filter_range(real10_literal | views::join);
    auto iter = std::begin(range_f);
    auto const end = std::end(range_f);

    // use X3's base10 double parser which is well tested
    x3::real_parser<double, detail::real_policies<double>> const real_parser;

    double real = 0;
    bool const parse_ok = x3::parse(iter, end, real_parser >> x3::eoi, real);

    if (!parse_ok) {
        auto const real10_str = range_f | to<std::string>();
        diagnostic_handler.parser_error(                                             // --
            literal.number.integer_part.begin(),                                     // --
            (format(translate("in {1} parse of real '{2}' failed"))  //--
             % node_name % real10_str).str());
        return std::tuple{ false, 0 };
    }

    return std::tuple{ true, real };
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

    // ------------------------------------------------------------------------
    // BASE
    //std::uint32_t base = 0;
    auto const [base_ok, base] = parse_base(node);

    if (!base_ok) {
        // parse error rendering done before
        return failure_return_value();
    }

    // ------------------------------------------------------------------------
    // INTEGER
    auto const [int_ok, integer] = parse_integer(base, node);

    if (!int_ok) {
        // parse error rendering done before
        return failure_return_value();
    }

    // ------------------------------------------------------------------------
    // FRACTIONAL (only for based real)
    real_type fractional = 0;

    if (base != 10U && node.numeric_type() == numeric_type_specifier::real) {
        bool parse_ok = false;
        std::tie(parse_ok, fractional) = parse_fractional(base, node);

        if (!parse_ok) {
            // parse error rendering done before
            return failure_return_value();
        }
    }

    // ------------------------------------------------------------------------
    // base 10 real numeric parser
    real_type real10 = 0;

    if (base == 10U && node.numeric_type() == numeric_type_specifier::real) {
        bool parse_ok = false;
        std::tie(parse_ok, real10) = parse_real10(node);

        if (!parse_ok) {
            // parse error rendering done before
            return failure_return_value();
        }
    }

    // ------------------------------------------------------------------------
    // EXPONENT
    auto const [exp_ok, exponent] = parse_exponent(node);

    if (!exp_ok) {
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
