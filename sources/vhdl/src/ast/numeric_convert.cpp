/*
 * numeric_convert.cpp
 *
 *  Created on: 26.05.2018
 *      Author: olaf
 */

#include <eda/vhdl/ast/util/numeric_convert.hpp>
#include <eda/vhdl/ast/util/literal_printer.hpp>
#include <eda/support/boost/spirit_x3.hpp>
#include <eda/vhdl/parser/parser_config.hpp>
#include <eda/utils/cxx_bug_fatal.hpp>

#include <numeric>  // accumulate
#include <iterator>
#include <cassert>
#include <iostream>
#include <boost/range/iterator_range.hpp>
#include <boost/iterator/filter_iterator.hpp>


namespace eda { namespace vhdl { namespace ast { namespace parser {


namespace detail {


/* VDL decimal literals does allow exponents on integers, to simplify evaluating
 * a x3 real parser with policies is used. The correct 2nd pass parsing and hence
 * correct converting depends on correct parsing of the VHDL grammar, since the
 * exponent of integer doesn't allow a negative sign. */


template <typename T>
struct integer_policies : x3::ureal_policies<T>
{
    static bool const allow_leading_dot =  false;
    static bool const allow_trailing_dot = false;
    static bool const expect_dot =         false;
};


template <typename T>
struct real_policies : x3::ureal_policies<T>
{
    static bool const allow_leading_dot =  false;
    static bool const allow_trailing_dot = false;
    static bool const expect_dot =         false;
};


using value_type = numeric_convert::value_type;

x3::real_parser<value_type, detail::integer_policies<uint32_t>> integer_base10;
x3::real_parser<value_type, detail::real_policies<value_type>> real_base10;


auto const exponent = x3::rule<struct _, uint32_t>{} =
        x3::omit[
             x3::char_("Ee")
        ]
    >> x3::int32 // signed
    ;

} // namespace detail


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
struct primitive_parser
{
    struct bin  {};
    struct oct  {};
    struct dec  {};
    struct hex  {};
    struct real {};
    struct exp  {};

    /**
     * The type, to which all literals will be converted. */
    typedef double                              attribute_type;

    /**
     * Return the numeric value of the literal
     */
    typedef std::tuple<bool, attribute_type>    return_value;


    template<typename RangeType>
    return_value operator()(RangeType const& range, primitive_parser::bin) const
    {
        uint32_t attribute{};   // exact attribute type for x3 parser

        auto const [parse_ok, full_match] = parse(range, x3::bin, attribute);

        return std::make_tuple(parse_ok && full_match, attribute);
    }


    template<typename RangeType>
    return_value operator()(RangeType const& range, primitive_parser::oct) const
    {
        uint32_t attribute{};   // exact attribute type for x3 parser

        auto const [parse_ok, full_match] = parse(range, x3::oct, attribute);

        return std::make_tuple(parse_ok && full_match, attribute);
    }


    template<typename RangeType>
    return_value operator()(RangeType const& range, primitive_parser::dec) const
    {
        uint32_t attribute{};   // exact attribute type for x3 parser

        auto const [parse_ok, full_match] = parse(range, detail::integer_base10, attribute);

        return std::make_tuple(parse_ok && full_match, attribute);
    }


    template<typename RangeType>
    return_value operator()(RangeType const& range, primitive_parser::hex) const
    {
        uint32_t attribute{};   // exact attribute type for x3 parser

        auto const [parse_ok, full_match] = parse(range, x3::hex, attribute);

        return std::make_tuple(parse_ok && full_match, attribute);
    }


    template<typename RangeType>
    return_value operator()(RangeType const& range, primitive_parser::real) const
    {
        double attribute{};

        auto const [parse_ok, full_match] = parse(range, detail::real_base10, attribute);

        return std::make_tuple(parse_ok && full_match, attribute);
    }


    template<typename RangeType>
    return_value operator()(RangeType const& range, primitive_parser::exp) const
    {
        int32_t attribute{};   // exact attribute type for x3 parser

        auto const [parse_ok, full_match] = parse(range, detail::exponent, attribute);

        return std::make_tuple(parse_ok && full_match, attribute);
    }


    template<typename RangeType, typename ParserType, typename AttributeType>
    std::tuple<bool, bool> parse(RangeType const& range, ParserType const &parser,
                                 AttributeType &attribute) const
    {
        auto range_f{ filter_range(range) };
        auto iter = std::begin(range_f);
        auto const end = std::cend(range_f);

        bool const parse_ok = x3::parse(iter, end, parser, attribute);
        bool const full_match = (iter == end);
#if 0
        std::cout << "inside primitive_parser::parse (" << range << ") -> "
                  << "parse_ok = " << std::boolalpha
                  << ", full_match = " << full_match
                  << '\n';
#endif

        return std::make_tuple(parse_ok, full_match);
    }


    template<typename RangeType>
    static
    auto filter_range(RangeType const& range)
    {
        struct separator_predicate {
            bool operator()(char x) {
                return '_' != x;
            }
        };

        return boost::make_iterator_range(
            boost::make_filter_iterator(separator_predicate{},
                    range.begin(), range.end()),
            boost::make_filter_iterator(separator_predicate{},
                    range.end())
        );
    }
};


} } } } // namespace eda.vhdl.ast.parser


namespace eda { namespace vhdl { namespace ast {


namespace detail {


/* Helper class to calculate fractional parts of binary numbers like bin,
 * oct and hex.  */
struct frac
{
    double const base;
    double pow;

    frac(double base_)
    : base{ base_ }, pow{ base_ }
    { };

    static unsigned digit(char ch)
    {
        /* Spirit.X3 offers utilities for converting chars, but we trust on VHDL
         * parser's 1st pass and can simplify this (hence speed up due not required
         * checks on correct arguments).  */
        switch(ch) {
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

    double operator()(double acc, char ch)
    {
        /* Fixme: The algorithm isn't smart to cover the failure cases like
         * over- and underflow. */
        double digit = frac::digit(ch);
        digit /= pow;
        pow *= base;
        double const result = acc + digit;
        assert(std::isnormal(result) && "Fractional number isn't a number");
        return result;
    }

};

} // namespace detail


auto const primitive_parse{ parser::primitive_parser{} };


numeric_convert::return_type numeric_convert::operator()(ast::bit_string_literal const& literal) const
{
    using parser::primitive_parser;
    using base_specifier = ast::bit_string_literal::base_specifier;

    auto const parse = [](ast::bit_string_literal const& literal)
    {
        switch(literal.base_type) {
            case base_specifier::bin: {
                return primitive_parse(literal.literal, primitive_parser::bin{});
            }
            case base_specifier::oct: {
                return primitive_parse(literal.literal, primitive_parser::oct{});
            }
            case base_specifier::hex: {
                return primitive_parse(literal.literal, primitive_parser::hex{});
            }
            default:
                cxx_unreachable_bug_triggered();
        }
    };

    auto const [parse_ok, result] = parse(literal);

    if(!parse_ok) {
        // assemble literal back since working on AST node
        auto const as_string = [](ast::bit_string_literal const& literal) {
            std::stringstream ss;
            ss <<  "\"" << literal.literal << "\"";
            return ss.str();
        };


        os << "Conversion of VHDL bit string literal \'"
           << literal_printer(literal)
           << "\' failed with numeric overflow (MAX_VALUE = "
           << std::numeric_limits<uint32_t>::max()
           << ")\n";
    }

    return std::make_tuple(parse_ok, result);
}


numeric_convert::return_type numeric_convert::operator()(ast::decimal_literal const& literal) const
{
    using parser::primitive_parser;
    using kind_specifier = ast::decimal_literal::kind_specifier;

    auto const parse = [](ast::decimal_literal const& literal)
    {
        switch(literal.kind_type) {
            case kind_specifier::integer: {
                return primitive_parse(literal.literal, primitive_parser::dec{});
            }
            case kind_specifier::real: {
                return primitive_parse(literal.literal, primitive_parser::real{});
            }
            default:
                cxx_unreachable_bug_triggered();
        }
    };

    auto const [parse_ok, result] = parse(literal);

    return std::make_tuple(parse_ok, result);
}


/* Note: The natural way would be to use Spirit.X3 parser primitive, e.g.
 * specialize x3's ureal_policies using a radix template parameter, which
 * compiles so far.
 * Unfortunately, spirit uses a LUT of pow10 - no other radixes are supported
 * at lower level. So the results are wrong.
 * So we have to use our own version. */
numeric_convert::return_type numeric_convert::operator()(ast::based_literal const& literal) const
{
    using parser::primitive_parser;

    auto const parse_base = [](ast::based_literal const& literal) {
        return primitive_parse(literal.base, primitive_parser::dec{});
    };

    auto const parse_integer_part = [](unsigned base, auto const& literal) {
        switch(base) {
            case 2: {
                return primitive_parse(literal, primitive_parser::bin{});
            }
            case 8: {
                return primitive_parse(literal, primitive_parser::oct{});
            }
            case 10: {
                return primitive_parse(literal, primitive_parser::dec{});
            }
            case 16: {
                return primitive_parse(literal, primitive_parser::hex{});
            }
            default:
                cxx_unreachable_bug_triggered();
        }
    };

    auto const parse_exponent = [](auto const& literal) {
        return primitive_parse(literal, primitive_parser::exp{});
    };

    uint32_t base{ 0 };
    double result { 0.0 };

    bool parse_ok{ false };

    // BASE
    std::tie(parse_ok, base) = parse_base(literal);

    if(!parse_ok) {
        return std::make_tuple(parse_ok, base);
    }

    // INTEGER PART
    std::tie(parse_ok, result) = parse_integer_part(base, literal.number.integer_part);

    if(!parse_ok) {
        return std::make_tuple(parse_ok, result);
    }

    // FRACTIONAL PART
    if(!literal.number.fractional_part.empty()) {
        auto const frac_obj = [](unsigned base) {
            switch(base) {
                case  2:  return detail::frac{ 2};
                case  8:  return detail::frac{ 8};
                case 10:  return detail::frac{10};
                case 16:  return detail::frac{16};
                default:  cxx_unreachable_bug_triggered();
            }
        };

        auto range_f{ primitive_parser::filter_range(literal.number.fractional_part) };
        auto iter = std::begin(range_f);
        auto const last = std::cend(range_f);
        auto const fractional_part = std::accumulate(iter, last, 0.0, frac_obj(base));

        result += fractional_part;
    }

    // EXPONENT
    if(!literal.number.exponent.empty()) {

        int32_t exponent{ 0 };

        std::tie(parse_ok, exponent) = parse_exponent(literal.number.exponent);

        if(!parse_ok) {
            return std::make_tuple(parse_ok, exponent);
        }

        double const pow = std::pow(
            static_cast<double>(base),
            static_cast<double>(exponent)
        );

        result *= pow;
    }

    return std::make_tuple(true, result);
}


} } } // namespace eda.vhdl.ast


/******************************************************************************
 * Code fragments from former converting functions, maybe useful later on.
 * The purpose was to limit the displayed literal length to begin and end of
 * it to shorten the error message in case of range overflow.
 ******************************************************************************

#include <eda/vhdl/utils/literal_ellipsis.hpp>

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
