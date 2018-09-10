/*
 * numeric_convert.cpp
 *
 *  Created on: 26.05.2018
 *      Author: olaf
 */

#include <eda/vhdl/ast/numeric_convert.hpp>

#include <eda/vhdl/ast/node/based_literal.hpp>
#include <eda/vhdl/ast/node/bit_string_literal.hpp>
#include <eda/vhdl/ast/node/decimal_literal.hpp>

#include <eda/support/boost/locale.hpp>
#include <eda/support/boost/spirit_x3.hpp>
#include <eda/util/cxx_bug_fatal.hpp>
#include <eda/vhdl/ast/literal_printer.hpp>
#include <eda/vhdl/parser/parser_config.hpp>
#include <eda/vhdl/type.hpp>

#include <boost/iterator/filter_iterator.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/range/join.hpp>

#include <cassert>
#include <iostream>
#include <iterator>
#include <numeric> // accumulate
#include <string_view>
#include <type_traits>

namespace eda {
namespace vhdl {
namespace ast {
namespace parser {

namespace detail {

/*
 * Note:
 *
 * VDL decimal literals does allow exponents on integers, to simplify evaluating
 * a x3 real parser with policies is used. The correct 2nd pass parsing and hence
 * correct converting depends on correct parsing of the VHDL grammar, since the
 * exponent of integer doesn't allow a negative sign.
 */

/*
 * real types and their parsers
 */
template <typename T> struct integer_policies : x3::ureal_policies<T> {
    // clang-format off
    static bool const allow_leading_dot =  false;
    static bool const allow_trailing_dot = false;
    static bool const expect_dot =         false;
    // clang-format on
};

template <typename T> struct real_policies : x3::ureal_policies<T> {
    // clang-format off
    static bool const allow_leading_dot =  false;
    static bool const allow_trailing_dot = false;
    static bool const expect_dot =         false;
    // clang-format on
};

using value_type = numeric_convert::value_type; // double

x3::real_parser<value_type, detail::real_policies<value_type>> real_base10;

/*
 * integer types and their parsers
 */
using unsigned_integer = eda::vhdl::intrinsic::unsigned_integer_type;
using signed_integer = eda::vhdl::intrinsic::unsigned_integer_type;

x3::real_parser<unsigned_integer, detail::integer_policies<unsigned_integer>> uint_base10;

// decimal parser signed/unsigned
using uint_parser_type = x3::uint_parser<unsigned_integer, 10>;
using int_parser_type = x3::int_parser<signed_integer, 10>;

// uint_parser_type const uint_ = { }; *** not used ***
int_parser_type const int_ = {};

// binary parser bin/oct/hex
using bin_parser_type = x3::uint_parser<unsigned_integer, 2>;
using oct_parser_type = x3::uint_parser<unsigned_integer, 8>;
using hex_parser_type = x3::uint_parser<unsigned_integer, 16>;

bin_parser_type const bin = {};
oct_parser_type const oct = {};
hex_parser_type const hex = {};

auto const exponent = x3::rule<struct _, unsigned_integer>{} =
    // clang-format off
        x3::omit[
             x3::char_("Ee")
        ]
    >> int_ // signed
    ;
// clang-format on
} // namespace detail

/*
 * Utility for debugging
 */
namespace dbg_util {

template <typename RangeType, typename RangeFiltType, typename AttributeType>
void trace_report(RangeType const& range, RangeFiltType const& range_f, bool parse_ok,
    AttributeType attribute, unsigned line, std::string const& function)
{
    // clang-format off
    std::cout << __FILE__ << ":" << line << " "
              << function << "('" << range << "')"
              << " -> ['" << range_f << "']: "
              << std::boolalpha
              << "parse_ok = "     << parse_ok
              << ", attribute = "  << attribute << '\n';
    // clang-format on
}

} // namespace dbg_util

// clang-format off
#define TRACE(range, range_f, parse_ok, attribute)                             \
    dbg_util::trace_report(range, range_f, parse_ok, attribute, __LINE__, __FUNCTION__)
// clang-format on

/**
 * Parse literal primitives. Mainly the task of this class is to handle the
 * underline separator inside the literals.
 *
 * As mentioned, trust in the correct VHDL grammar rules which feeds this numeric
 * primitive_parser. This allows to use 'sloppy' rules to convert from
 * strings to numeric values.
 *
 * Treat all of x3's attribute type as double for simplification, otherwise
 * one has to handle with different return types using C++ lambdas.
 */
struct primitive_parser {
    struct bin {
    };
    struct oct {
    };
    struct dec {
    };
    struct hex {
    };
    struct real {
    };
    struct exp {
    };

    /**
     * The type, to which all literals will be converted. */
    using attribute_type = double;

    /**
     * Return the numeric value of the literal
     */
    using return_value = std::tuple<bool, attribute_type>;

    template <typename RangeType>
    return_value operator()(RangeType const& range, primitive_parser::bin /*unused*/) const
    {
        detail::unsigned_integer attribute{};

        bool const parse_ok = parse(range, detail::bin, attribute);

        return std::make_tuple(parse_ok, attribute);
    }

    template <typename RangeType>
    return_value operator()(RangeType const& range, primitive_parser::oct /*unused*/) const
    {
        detail::unsigned_integer attribute{};

        bool const parse_ok = parse(range, detail::oct, attribute);

        return std::make_tuple(parse_ok, attribute);
    }

    template <typename RangeType>
    return_value operator()(RangeType const& range, primitive_parser::dec /*unused*/) const
    {
        detail::unsigned_integer attribute{};

        bool const parse_ok = parse(range, detail::uint_base10, attribute);

        return std::make_tuple(parse_ok, attribute);
    }

    template <typename RangeType>
    return_value operator()(RangeType const& range, primitive_parser::hex /*unused*/) const
    {
        detail::unsigned_integer attribute{};

        bool const parse_ok = parse(range, detail::hex, attribute);

        return std::make_tuple(parse_ok, attribute);
    }

    template <typename RangeType>
    return_value operator()(RangeType const& range, primitive_parser::real /*unused*/) const
    {
        double attribute{};

        bool const parse_ok = parse(range, detail::real_base10, attribute);

        return std::make_tuple(parse_ok, attribute);
    }

    template <typename RangeType>
    return_value operator()(RangeType const& range, primitive_parser::exp /*unused*/) const
    {
        detail::signed_integer attribute{};

        bool const parse_ok = parse(range, detail::exponent, attribute);

        return std::make_tuple(parse_ok, attribute);
    }

    template <typename RangeType, typename ParserType, typename AttributeType>
    bool parse(RangeType const& range, ParserType const& parser, AttributeType& attribute) const
    {
        /* Note, simply using an approach like
         * \code{.cpp}
         * auto const skipper = x3::rule<...> {} = x3::char_('_');
         * x3::phrase_parse(..., skipper, attribute);
         * \endcode
         * doesn't work since the skipper is used the build lexeme (tokenize)
         * the input. Hence, the input must be filtered before parsed.
         * Alternative solution shown at
         * [Using boost::spirit::qi to parse numbers with separators](
         * https://stackoverflow.com/questions/29132809/using-boostspiritqi-to-parse-numbers-with-separators?answertab=active#tab-top)
         * looks even more complicated. */
        auto const range_f{ filter_range(range) };
        auto iter = std::begin(range_f);
        auto const end = std::cend(range_f);

        /* Note, parser matches the end of input (eoi) - trust in Spirit.X3
         * numeric parsers and top level VHDL parser. If it fails it's probably
         * due to numeric overflow. The same information we would be gathered by
         * evaluation of an 'full_match' boolean flag as shown by Spirit's
         * test_parser() tests - something has been left unparsed. */
        bool const parse_ok = x3::parse(iter, end, parser >> x3::eoi, attribute);

        TRACE(range, range_f, parse_ok, attribute);

        return parse_ok;
    }

    template <typename RangeType> static auto filter_range(RangeType const& range)
    {
        struct separator_predicate {
            bool operator()(char x) { return '_' != x; }
        };

        // clang-format off
        return boost::make_iterator_range(
            boost::make_filter_iterator(separator_predicate{},
                    range.begin(), range.end()),
            boost::make_filter_iterator(separator_predicate{},
                    range.end())
        );
        // clang-format on
    }
};

} // namespace parser
} // namespace ast
} // namespace vhdl
} // namespace eda

namespace eda {
namespace vhdl {
namespace ast {

namespace detail {

/*
 * Integer Types and Parsers
 */
using unsigned_integer = eda::vhdl::intrinsic::unsigned_integer_type;
using signed_integer = eda::vhdl::intrinsic::unsigned_integer_type;
using real = eda::vhdl::intrinsic::real_type;

/**
 * Helper class to calculate fractional parts of binary numbers like bin,
 * oct and hex.  */
struct frac {
    using numeric_type = double;

    numeric_type const base;
    numeric_type pow;

    explicit frac(numeric_type base_)
        : base{ base_ }
        , pow{ base_ }
    {
    }

    static unsigned digit(char ch)
    {
        /* Spirit.X3 offers utilities for converting chars, but we trust on VHDL
         * parser's 1st pass and can simplify this (hence speed up due not required
         * checks on correct arguments).  */
        switch (ch) {
            // clang-format off
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
            // clang-format on
            default:
                cxx_unreachable_bug_triggered();
        }
    }

    numeric_type operator()(numeric_type acc, char ch)
    {
        /* Fixme: The algorithm isn't smart to cover the failure cases like
         * over- and underflow. */
        numeric_type digit = frac::digit(ch);
        digit /= pow;
        pow *= base;
        numeric_type const result = acc + digit;

        return result;
    }
};

} // namespace detail

auto const primitive_parse{ parser::primitive_parser{} };

/**
 * constructs the numeroc_convert util, errors are reported on os_.
 */
numeric_convert::numeric_convert(std::ostream& os_)
    : os{ os_ }
{
    // until we got all templates, check for correct types
    static_assert(std::integral_constant<bool,
                      std::is_same_v<numeric_convert::value_type, detail::real>>::value,
        "iterator types must be the same");
}

/**
 * numeric_convert's private error reporting utility to unify error messages
 */
struct numeric_convert::report_error {
    std::ostream& os;
    static constexpr detail::unsigned_integer MAX_VALUE{
        std::numeric_limits<detail::unsigned_integer>::max()
    };

    explicit report_error(std::ostream& os_)
        : os{ os_ }
    {
    }

    template <typename LiteralType>
    void overflow_message(std::string const& literal_type, LiteralType const& literal) const
    {
        using boost::locale::format;
        using boost::locale::translate;

        // clang-format off
        os << format(translate( // TRANSLATORS: Literal Type and passed Value
            "Conversion of VHDL {1} \'{2}\' failed due to numeric overflow "
            "(MAX_VALUE = {3})"
            ))
            % literal_type
            % literal_printer(literal)
            % MAX_VALUE
           << '\n';
        // clang-format on
    }

    void overflow(ast::bit_string_literal const& literal) const
    {
        static char const type[]{ "bit string literal" };
        overflow_message(type, literal);
    }

    void overflow(ast::decimal_literal const& literal) const
    {
        static char const type[]{ "decimal literal" };
        overflow_message(type, literal);
    }

    void overflow(ast::based_literal const& literal) const
    {
        static char const type[]{ "based literal" };
        overflow_message(type, literal);
    }

    template <typename StringViewT> void unkown_parser_error(StringViewT const& what) const
    {
        using boost::locale::format;
        using boost::locale::translate;

        // clang-format off
        os << format(translate(
            "An unknown error occurred during parsing of \'{1}\'."
            ))
            % what
           << '\n';
        // clang-format on
    }

    template <typename StringViewT> void unsupported_base(StringViewT const& base_literal) const
    {
        using boost::locale::format;
        using boost::locale::translate;

        // clang-format off
        os << format(translate(
            "Base specifier \'{1}\' isn't supported. "
            "Supported are only 2, 8, 10 and 16!"
            ))
            % base_literal
           << '\n';
        // clang-format on
    }
};

/*******************************************************************************
 * bit_string_literal
 */
numeric_convert::return_type numeric_convert::operator()(
    ast::bit_string_literal const& literal) const
{
    using parser::primitive_parser;
    using base_specifier = ast::bit_string_literal::base_specifier;

    auto const parse = [](ast::bit_string_literal const& literal_) {
        switch (literal_.base_type) {
            case base_specifier::bin: {
                return primitive_parse(literal_.literal, primitive_parser::bin{});
            }
            case base_specifier::oct: {
                return primitive_parse(literal_.literal, primitive_parser::oct{});
            }
            case base_specifier::hex: {
                return primitive_parse(literal_.literal, primitive_parser::hex{});
            }
            default:
                cxx_unreachable_bug_triggered();
        }
    };

    auto const[parse_ok, result] = parse(literal);

    if (!parse_ok) {
        report_error{ os }.overflow(literal);
    }

    return std::make_tuple(parse_ok, result);
}

/*******************************************************************************
 * decimal_literal
 */
numeric_convert::return_type numeric_convert::operator()(ast::decimal_literal const& literal) const
{
    using parser::primitive_parser;
    using kind_specifier = ast::decimal_literal::kind_specifier;

    auto const parse = [](ast::decimal_literal const& literal_) {
        switch (literal_.kind_type) {
            case kind_specifier::integer: {
                return primitive_parse(literal_.literal, primitive_parser::dec{});
            }
            case kind_specifier::real: {
                return primitive_parse(literal_.literal, primitive_parser::real{});
            }
            default:
                cxx_unreachable_bug_triggered();
        }
    };

    auto const[parse_ok, result] = parse(literal);

    if (!parse_ok) {
        report_error{ os }.overflow(literal);
    }

    return std::make_tuple(parse_ok, result);
}

/*******************************************************************************
 * based_literal
 *
 * Note: The natural way would be to use Spirit.X3 parser primitive, e.g.
 * specialize x3's ureal_policies using a radix template parameter, which
 * compiles so far.
 * Unfortunately, spirit uses a LUT of pow10 - no other radixes are supported
 * at lower level. So the results are wrong.
 * So we have to use our own version. */
numeric_convert::return_type numeric_convert::operator()(ast::based_literal const& literal) const
{
    using boost::locale::format;
    using boost::locale::translate;
    using parser::primitive_parser;

    auto const supported_base = [](unsigned base_) {
        switch (base_) {
            // clang-format off
            case 2:  [[fallthrough]];
            case 8:  [[fallthrough]];
            case 10: [[fallthrough]];
            case 16: return true;
            // clang-format on
            default:
                return false;
        }
    };

    auto const parse_base = [](ast::based_literal const& literal_) {
        return primitive_parse(literal_.base, primitive_parser::dec{});
    };

    auto const parse_integer_part = [](unsigned base, ast::based_literal const& literal_) {
        switch (base) {
            case 2: {
                return primitive_parse(literal_.number.integer_part, primitive_parser::bin{});
            }
            case 8: {
                return primitive_parse(literal_.number.integer_part, primitive_parser::oct{});
            }
            case 10: {
                return primitive_parse(literal_.number.integer_part, primitive_parser::dec{});
            }
            case 16: {
                return primitive_parse(literal_.number.integer_part, primitive_parser::hex{});
            }
            default:
                cxx_unreachable_bug_triggered();
        }
    };

    auto const parse_exponent = [](ast::based_literal const& literal_) {
        return primitive_parse(literal_.number.exponent, primitive_parser::exp{});
    };

    unsigned base{ 0 };
    numeric_convert::value_type result{ 0.0 };
    bool parse_ok{ false };

    /* -------------------------------------------------------------------------
     * base specifier
     */
    std::tie(parse_ok, base) = parse_base(literal);

    cxx_assert(base < 32, "Numeric literals must be expressed in any base from 2 to 16");

    if (!parse_ok) {
        // FixMe: error message not appropriate
        report_error{ os }.unsupported_base(literal.base);
        return std::make_tuple(parse_ok, base);
    }

    if (!supported_base(base)) {
        report_error{ os }.unsupported_base(literal.base);
        return std::make_tuple(false, result);
    }

    /* -------------------------------------------------------------------------
     * based 10 decimal literals are handle by Spirit.X3 supplied parsers
     * directly
     * ------------------------------------------------------------------------*/
    if (base == 10) {

        /* Note, a dumb join of over all numeric literal components doesn't work
         * here since some (empty) number literal components results into an
         * empty iterator_range  where the parser crash with
         * memory access violation at address: 0x00000000
         * Also take care about [boost::range::join for multiple ranges](
         * https://stackoverflow.com/questions/14366576/boostrangejoin-for-multiple-ranges?answertab=active#tab-top)
         */

        /* '.' symbol for assembling a 'to-parse-string' for Spirit.X3 parsers
         * since the dot it's not an AST member by design. */
        static std::string const dot{ "." };

        using kind_specifier = ast::based_literal::kind_specifier;

        switch (literal.number.kind_type) {
            // clang-format off
            case kind_specifier::integer: {
                if(literal.number.exponent.empty()) {
                    std::tie(parse_ok, result) = primitive_parse(
                        literal.number.integer_part, primitive_parser::dec{});
                }
                else {
                    std::tie(parse_ok, result) = primitive_parse(
                        boost::join(
                            literal.number.integer_part,
                            literal.number.exponent
                        ),
                        primitive_parser::dec{});
                }
            }
            break;

            case kind_specifier::real: {
                if(literal.number.exponent.empty()) { // 'integer . fractional'
                    std::tie(parse_ok, result) = primitive_parse(
                        boost::join(
                            boost::join(
                                literal.number.integer_part,
                                dot
                            ),
                            literal.number.fractional_part
                        ),
                        primitive_parser::real{});
                }
                else { // 'integer . fractional exponent'
                    std::tie(parse_ok, result) = primitive_parse(
                        boost::join(
                            boost::join(
                                boost::join(
                                    literal.number.integer_part,
                                    dot
                                ),
                                literal.number.fractional_part
                            ),
                            literal.number.exponent
                        ),
                        primitive_parser::real{});
                }
            }
            break;
            // clang-format on
            default:
                cxx_unreachable_bug_triggered();
        }

        if (!parse_ok) {
            report_error{ os }.overflow(literal);
            return std::make_tuple(parse_ok, result);
        }

        return std::make_tuple(parse_ok, result);
    }

    /* -------------------------------------------------------------------------
     * other based decimal literals
     * -----------------------------------------------------------------------*/

    /* -------------------------------------------------------------------------
     * integer part
     */
    std::tie(parse_ok, result) = parse_integer_part(base, literal);

    if (!parse_ok) {
        report_error{ os }.overflow(literal);
        return std::make_tuple(parse_ok, result);
    }

    /* -------------------------------------------------------------------------
     * fractional part requires special handling since Spirit.X3 doesn't
     * handle bases other than 10 not yet.
     */
    if (!literal.number.fractional_part.empty()) {
        auto const frac_obj = [](unsigned base_) {
            switch (base_) {
                // clang-format off
                case  2:  return detail::frac{ 2};
                case  8:  return detail::frac{ 8};
                case 10:  return detail::frac{10};
                case 16:  return detail::frac{16};
                // clang-format on
                default:
                    cxx_unreachable_bug_triggered();
            }
        };

        auto range_f{ primitive_parser::filter_range(literal.number.fractional_part) };
        auto iter = std::begin(range_f);
        auto const last = std::cend(range_f);
        auto const fractional_part = std::accumulate(iter, last, 0.0, frac_obj(base));

        /* during accumulation using frac_obj a numeric IEEE754 errors may
         * occur */
        if (!std::isnormal(fractional_part)) {
            // clang-format off
            os << format(translate(
                "Numeric error occurred during calculation on based_literal "
                "with fractional part of \'{1}\'."
                ))
                % literal.number.fractional_part
               << '\n';
            // clang-format on
            return std::make_tuple(false, result);
        }

        result += fractional_part;
    }

    /* -------------------------------------------------------------------------
     * exponent
     */
    if (!literal.number.exponent.empty()) {

        detail::signed_integer exponent{ 0 };

        std::tie(parse_ok, exponent) = parse_exponent(literal);

        if (!parse_ok) {
            report_error{ os }.overflow(literal);
            return std::make_tuple(parse_ok, exponent);
        }

        numeric_convert::value_type const pow
            = std::pow(static_cast<double>(base), static_cast<double>(exponent));

        result *= pow;
    }

    return std::make_tuple(true, result);
}

} // namespace ast
} // namespace vhdl
} // namespace eda

/******************************************************************************
 * Code fragments from former converting functions, maybe useful later on.
 * The purpose was to limit the displayed literal length to begin and end of
 * it to shorten the error message in case of range overflow.
 ******************************************************************************

#include <eda/vhdl/util/literal_ellipsis.hpp>

...
// for bit_string_literal

if(ok && iter != cend) {

    static std::array<unsigned, 3> const length {{
            8*sizeof(int32_t), // bin
            4*sizeof(int32_t), // oct
            2*sizeof(int32_t)  // hex
    }};

    BOOST_THROW_EXCEPTION(
        eda::range_error(
            "VHDL Bit String Literal='"
            + literal_ellipsis(node.bit_literal, length[static_cast<unsigned>(node.base)])
            + "' <int32> Range Error")
    );
}


// for deciaml_literal

if (ok && iter != cend) {
    // syntactically ok, but literal probably to long
    BOOST_THROW_EXCEPTION(
        eda::range_error(
            "VHDL Decimal Literal='"
            + literal_ellipsis(node.literal, 15)
            + "' <double> Range Error")
    );
}

 ******************************************************************************/
