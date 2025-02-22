//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-or-later
//

#include <ibis/vhdl/ast/numeric_convert/convert_based.hpp>
#include <ibis/vhdl/ast/node/based_literal.hpp>
#include <ibis/concepts.hpp>
#include <ibis/vhdl/ast/util/numeric_base_specifier.hpp>
#include <ibis/vhdl/ast/util/string_span.hpp>
#include <ibis/vhdl/ast/numeric_convert/dbg_trace.hpp>
#include <ibis/vhdl/ast/numeric_convert/detail/convert_util.hpp>
#include <ibis/vhdl/ast/numeric_convert/detail/digits_traits.hpp>
#include <ibis/vhdl/ast/numeric_convert/filter_range.hpp>
#include <ibis/vhdl/diagnostic_handler.hpp>
#include <ibis/vhdl/type.hpp>

#include <ibis/util/cxx_bug_fatal.hpp>

// IWYU replaces a lot of other header, we stay with this one
// #include <boost/spirit/home/x3.hpp>  // IWYU pragma: keep
#include <range/v3/view/join.hpp>
#include <range/v3/range/conversion.hpp>
#include <boost/locale/format.hpp>
#include <boost/locale/message.hpp>

#include <cmath>
#include <iostream>
#include <initializer_list>
#include <iterator>
#include <limits>
#include <numeric>
#include <optional>
#include <string_view>
#include <string>
#include <tuple>
#include <utility>

#include <ibis/namespace_alias.hpp>  // IWYU pragma: keep

namespace ibis::vhdl::ast::detail {

template <typename T>
struct real_policies : x3::ureal_policies<T> {
    static bool const allow_leading_dot = false;
    static bool const allow_trailing_dot = false;
    static bool const expect_dot = false;
};

}  // namespace ibis::vhdl::ast::detail

namespace ibis::vhdl::ast {

static constexpr unsigned BASE10 = 10;

template <ibis::integer IntegerT, ibis::real RealT>
convert_based<IntegerT, RealT>::convert_based(diagnostic_handler_type& diagnostic_handler_)
    : diagnostic_handler{ diagnostic_handler_ }
{
}

template <ibis::integer IntegerT, ibis::real RealT>
std::tuple<bool, typename convert_based<IntegerT, RealT>::integer_type>
convert_based<IntegerT, RealT>::parse_integer(unsigned base,
                                              ast::based_literal const& literal) const
{
    using boost::locale::format;
    using boost::locale::translate;

    // select a concrete parser depending the the base specifier
    auto const parser = [](unsigned base_spec, auto iter_t) {
        using numeric_base_specifier = ast::numeric_base_specifier;
        auto const base_specifier = to_base_specifier(base_spec);

        using iterator_type = decltype(iter_t);
        // clang-format off
        switch (base_specifier) {
            case numeric_base_specifier::base2:
                return detail::uint_parser<iterator_type, integer_type>::base(ast::numeric_base_specifier::base2);
            case numeric_base_specifier::base8:
                return detail::uint_parser<iterator_type, integer_type>::base(ast::numeric_base_specifier::base8);
            case numeric_base_specifier::base10:
                return detail::uint_parser<iterator_type, integer_type>::base(ast::numeric_base_specifier::base10);
            case numeric_base_specifier::base16:
                return detail::uint_parser<iterator_type, integer_type>::base(ast::numeric_base_specifier::base16);
            // definitely wrong enum, the caller has not worked out properly
            [[unlikely]] case numeric_base_specifier::unspecified: [[fallthrough]];
            [[unlikely]] case numeric_base_specifier::unsupported:
                cxx_bug_fatal("unspecified or unsupported base for based literal");
            //
            // *No* default branch: let the compiler generate warning about enumeration
            // value not handled in switch
            //
        }
        // clang-format on

        std::unreachable();
    };

    // convenience alias
    auto const& integer_literal = literal.number.integer_part;
    auto const integer_literal_sv = as_string_view(integer_literal);

    auto range_f = numeric_convert::detail::filter_range(integer_literal);

    if (ranges::distance(range_f) > std::numeric_limits<integer_type>::digits10) {
        diagnostic_handler.parser_error(                     // --
            integer_literal.begin(), integer_literal.end(),  // --
            // TRANSLATORS: error message for numeric target type
            (format(translate("in {1} integer part '{2}' can't fit the numeric type"))  // --
             % node_name % integer_literal_sv)
                .str());
        return { false, 0 };
    }

    auto iter = std::begin(range_f);
    auto const end = std::end(range_f);

    integer_type integer_attribute = 0;
    bool const parse_ok = x3::parse(iter, end, parser(base, iter) >> x3::eoi, integer_attribute);

    if (!parse_ok) {
        diagnostic_handler.parser_error(                     // --
            integer_literal.begin(), integer_literal.end(),  // --
            // TRANSLATORS: error message for numeric target type
            (format(translate("in {1} parse of integer part '{2}' failed"))  // --
             % node_name % integer_literal_sv)
                .str());
        return { false, 0 };
    }

    return { true, integer_attribute };
}

template <ibis::integer IntegerT, ibis::real RealT>
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
                // NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
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
                    default:    // parser's character validation failed
                        cxx_bug_fatal("invalid hex character for based literal");
                }
                // NOLINTEND(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
            };
            // clang-format on

            real_type dig = hex2dec(hex_chr);
            dig /= pow;
            pow *= static_cast<real_type>(base);

            return acc + dig;
        });

    // during accumulation a numeric IEEE754 errors may occur
    if (!std::isnormal(fractional)) {
        diagnostic_handler.numeric_error(                          // --
            fractional_literal.begin(), fractional_literal.end(),  // --
            (format(translate(  // TRANSLATORS: error message for numeric target type
                 "in {1} numeric error occurred during calculation of fractional part '{2}'"))  //
             % node_name % fractional_literal_sv)
                .str());
        return { false, fractional };
    }

    return { true, fractional };
}

template <ibis::integer IntegerT, ibis::real RealT>
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

    auto range_f = numeric_convert::detail::filter_range(exponent_literal);

    // TRANSLATORS: error message for numeric target type
    std::string const error_msg_tr =  // same message template for several error messages
        translate("in {1} the exponent part '{2}' can't fit the {3} type");

    if (ranges::distance(range_f) > std::numeric_limits<exponent_type>::digits10) {
        diagnostic_handler.parser_error(                       // --
            exponent_literal.begin(), exponent_literal.end(),  // --
            (format(translate(error_msg_tr))                   //
             % node_name % exponent_literal_sv)
                .str());
        return { false, exponent_attribute };
    }

    // parse attribute
    auto iter = std::begin(range_f);
    auto const end = std::end(range_f);

    auto const exp = x3::rule<struct _, exponent_type>{ node_name.data() } = x3::int_;

    bool const parse_ok = x3::parse(iter, end, exp >> x3::eoi, exponent_attribute);

    if (!parse_ok) {
        diagnostic_handler.parser_error(                       // --
            exponent_literal.begin(), exponent_literal.end(),  // --
            // TRANSLATORS: error message for numeric target type
            (format(translate("in {1} parse of exponent '{2}' failed"))  // --
             % node_name % exponent_literal_sv)
                .str());
        return { false, exponent_attribute };
    }

    // there are only integer and real types
    using numeric_type_specifier = ast::based_literal::numeric_type_specifier;

    // check on valid exponent numeric range
    if (literal.number.type_specifier == numeric_type_specifier::real) {
        // max. exponent for e.g. double 308 as in 1.0e308
        if (exponent_attribute > std::numeric_limits<real_type>::max_exponent10) {
            diagnostic_handler.parser_error(                       // --
                exponent_literal.begin(), exponent_literal.end(),  // --
                (format(error_msg_tr) % node_name % exponent_literal_sv % "real").str());
            return { false, exponent_attribute };
        }
    }
    else {
        // max. exponent for e.g. 32bit integer 9 as in 1e+9
        if (exponent_attribute > std::numeric_limits<integer_type>::digits10) {
            diagnostic_handler.parser_error(                       // --
                exponent_literal.begin(), exponent_literal.end(),  // --
                (format(error_msg_tr) % node_name % exponent_literal_sv % "integer").str());
            return { false, exponent_attribute };
        }
    }

    return { true, exponent_attribute };
}

template <ibis::integer IntegerT, ibis::real RealT>
std::tuple<bool, double> convert_based<IntegerT, RealT>::parse_real10(
    ast::based_literal const& literal) const
{
    using boost::locale::format;
    using boost::locale::translate;
    using namespace ranges;
    using namespace std::literals::string_view_literals;

    // ranges-v3 concept: [coliru](https://coliru.stacked-crooked.com/a/530a793796999fab)
    // c++20 range concept [coliru](https://coliru.stacked-crooked.com/a/17f844b879507aed)
    auto const real10_literal = {
        // --
        as_string_view(literal.number.integer_part),           // --
        "."sv, as_string_view(literal.number.fractional_part)  // --
    };

    auto range_f = numeric_convert::detail::filter_range(real10_literal | views::join);
    auto iter = std::begin(range_f);
    auto const last = std::end(range_f);

    // use X3's base10 double parser which is well tested
    x3::real_parser<double, detail::real_policies<double>> const real_parser;

    double real = 0;
    bool const parse_ok = x3::parse(iter, last, real_parser >> x3::eoi, real);

    if (!parse_ok) {
        auto const real10_str = range_f | to<std::string>();
        diagnostic_handler.parser_error(                             // --
            literal.number.integer_part.begin(),                     // --
            (format(translate("in {1} parse of real '{2}' failed"))  //--
             % node_name % real10_str)
                .str());
        return { false, 0 };
    }

    return { true, real };
}

template <ibis::integer IntegerT, ibis::real RealT>
typename convert_based<IntegerT, RealT>::return_type convert_based<IntegerT, RealT>::operator()(
    ast::based_literal const& node) const
{
    using boost::locale::format;
    using boost::locale::translate;

    using numeric_type_specifier = ast::based_literal::numeric_type_specifier;

    auto const failure_return_value = [&node]() -> convert_based::return_type {
        // clang-format off
        switch (node.number.type_specifier) {
            case numeric_type_specifier::integer:
                return return_type{ false, integer_type{ 0 } };
            case numeric_type_specifier::real:
                return return_type{ false, real_type{ 0 } };
            // definitely wrong enum - the caller has not worked out properly
            [[unlikely]] case numeric_type_specifier::unspecified:
                cxx_bug_fatal("unspecified numeric type for based literal");
            // *No* default branch: let the compiler generate warning about enumeration
            // value not handled in switch
        }
        // clang-format on

        std::unreachable();
    };

    // ------------------------------------------------------------------------
    // BASE
    unsigned const base = node.base_id;

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

    if (base != BASE10 && node.number.type_specifier == numeric_type_specifier::real) {
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

    if (base == BASE10 && node.number.type_specifier == numeric_type_specifier::real) {
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

    // clang-format off
    switch (node.number.type_specifier) {
        case numeric_type_specifier::integer: {
            integer_type result = integer;
            result *= static_cast<integer_type>(pow);
            return std::tuple{ true, result };
        }
        case numeric_type_specifier::real: {
            real_type result = 0;
            if (base == BASE10) {
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
        // definitely wrong enum - the caller has not worked out properly
        [[unlikely]] case numeric_type_specifier::unspecified:
            cxx_bug_fatal("unspecified numeric type for based literal");
        // *No* default branch: let the compiler generate warning about enumeration
        // value not handled in switch
    }
    // clang-format on

    std::unreachable();
}

}  // namespace ibis::vhdl::ast

// ----------------------------------------------------------------------------
// Explicit template instantiation
// ----------------------------------------------------------------------------
namespace ibis::vhdl::ast {

template class convert_based<intrinsic::unsigned_integer_type, intrinsic::real_type>;

}  // namespace ibis::vhdl::ast
