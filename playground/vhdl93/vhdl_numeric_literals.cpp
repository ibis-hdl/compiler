/*
 * vhdl_numeric_literals.cpp
 *
 *  Created on: 21.05.2018
 *      Author: olaf
 */

#include <iostream>
#include <string>
#include <algorithm>
#include <iterator>
#include <boost/range/iterator_range.hpp>
#include <boost/iterator/filter_iterator.hpp>

//#define BOOST_SPIRIT_X3_DEBUG
#include <boost/spirit/home/x3.hpp>



namespace x3 = boost::spirit::x3;


namespace ast {
    struct literal {
        enum base_specifier { bin, oct, hex };

        base_specifier  base;
        std::string     literal;
    };

    struct decimal_literal
    {
        enum class kind_specifier { integer, real };

        std::string     literal;
        kind_specifier  kind;
    };

    struct based_literal
    {
        // FixMe in Grammar - see why here: https://stackoverflow.com/questions/22113223/vhdl-error-integer-literal-cannot-have-negative-exponent
        enum class kind_specifier { integer, real };

        std::string     base;
        std::string     integer_part;
        std::string     fractional_part;
        std::string     exponent;
        kind_specifier  kind;
    };

}

namespace detail {

    template <typename T>
    struct integer_policies : x3::ureal_policies<T>
    {
        static bool const allow_leading_dot = false;
        static bool const allow_trailing_dot = false;
        static bool const expect_dot = false;
        // ...
    };

    x3::real_parser<double, detail::integer_policies<double>> real;

    auto const exponent = x3::rule<struct _, int32_t>{} =
            x3::omit[
                 (x3::lit('e') | 'E')
            ]
        >> x3::int32
        ;
}

namespace tag {
    struct bin  {};
    struct oct  {};
    struct dec  {};
    struct hex  {};
    struct real {};
    struct exp  {};
}

struct literal_parser
{
    /* treat all as double, otherwise one has to handle with different return types
     * using C++ lambdas. */
    typedef std::tuple<bool, double>            return_value;

    template<typename RangeType>
    return_value operator()(RangeType const& range, tag::bin) const
    {
        uint32_t attribute{};

        bool const parse_ok = parse(range, x3::bin, attribute);

        return std::make_tuple(parse_ok, attribute);
    }

    template<typename RangeType>
    return_value operator()(RangeType const& range, tag::oct) const
    {
        uint32_t attribute{};

        bool const parse_ok = parse(range, x3::oct, attribute);

        return std::make_tuple(parse_ok, attribute);
    }

    template<typename RangeType>
    return_value operator()(RangeType const& range, tag::dec) const
    {
        uint32_t attribute{};

        bool const parse_ok = parse(range, x3::uint32, attribute);

        return std::make_tuple(parse_ok, attribute);
    }

    template<typename RangeType>
    return_value operator()(RangeType const& range, tag::hex) const
    {
        uint32_t attribute{};

        bool const parse_ok = parse(range, x3::hex, attribute);

        return std::make_tuple(parse_ok, attribute);
    }

    template<typename RangeType>
    return_value operator()(RangeType const& range, tag::real) const
    {
        double attribute{};

        bool const parse_ok = parse(range, x3::double_, attribute);

        return std::make_tuple(parse_ok, attribute);
    }

    template<typename RangeType>
    return_value operator()(RangeType const& range, tag::exp) const
    {
        int32_t attribute{};

        bool const parse_ok = parse(range, detail::exponent, attribute);

        return std::make_tuple(parse_ok, attribute);
    }

    template<typename RangeType, typename AttributeType, typename ParserType>
    bool parse(RangeType const& range, ParserType const &parser,
               AttributeType &attribute,  bool full_match = true) const
    {
        auto range_f{ filter_range(range) };
        auto iter = std::begin(range_f);
        auto const last = std::cend(range_f);

        bool const parse_ok = x3::parse(iter, last, parser, attribute);

        return parse_ok && (!full_match || (iter == last));
    }

    template<typename RangeType>
    auto filter_range(RangeType const& range) const
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


struct literal_convert
{
    typedef std::tuple<bool, double>            return_type;
    literal_parser                              literal_parse;

    return_type operator()(ast::literal const& literal) const
    {
        using base_specifier = ast::literal::base_specifier;

        auto const parse = [this](ast::literal const& literal)
        {
            switch(literal.base) {
                case base_specifier::bin: {
                    return literal_parse(literal.literal, tag::bin{});
                }
                case base_specifier::oct: {
                    return literal_parse(literal.literal, tag::oct{});
                }
                case base_specifier::hex: {
                    return literal_parse(literal.literal, tag::hex{});
                }
                default:
                    abort();
            }
        };

        auto const [parse_ok, result] = parse(literal);

        // ...

        return std::make_tuple(parse_ok, result);
    }


    return_type operator()(ast::decimal_literal const& literal) const
    {
        using kind_specifier = ast::decimal_literal::kind_specifier;

        auto const parse = [this](ast::decimal_literal const& literal)
        {
            switch(literal.kind) {
                case kind_specifier::integer: {
                    return literal_parse(literal.literal, tag::dec{});
                }
                case kind_specifier::real: {
                    return literal_parse(literal.literal, tag::real{});
                }
                default:
                    abort();
            }
        };

        auto const [parse_ok, result] = parse(literal);

        // ...

        return std::make_tuple(parse_ok, result);
    }


    return_type operator()(ast::based_literal const& literal) const
    {
        auto const parse_base = [this](ast::based_literal const& literal) {
            return literal_parse(literal.base, tag::dec{});
        };

        auto const parse_integer = [this](unsigned base, auto const& literal) {
            switch(base) {
                case 2: {
                    return literal_parse(literal, tag::bin{});
                }
                case 8: {
                    return literal_parse(literal, tag::oct{});
                }
                case 10: {
                    return literal_parse(literal, tag::dec{});
                }
                case 16: {
                    return literal_parse(literal, tag::hex{});
                }
                default:
                    abort();
            }
        };

        auto const parse_exponent = [this](ast::based_literal const& literal) {
            return literal_parse(literal.exponent, tag::exp{});
        };

        bool parse_ok{ false };
        uint32_t base{ 0 };
        uint32_t integer_part{ 0 };
        uint32_t fractional_part{ 0 };
        int32_t  exponent{ 0 };
        double result { 0.0 };

        // --- BASE
        std::tie(parse_ok, base) = parse_base(literal);
        std::cout << "base: " << base << " (" << std::boolalpha << parse_ok << ")\n";

        if(!parse_ok) {
            return std::make_tuple(parse_ok, base);
        }

        // INTEGER PART
        std::tie(parse_ok, integer_part) = parse_integer(base, literal.integer_part);
        std::cout << "integer_part: " << integer_part << " (" << std::boolalpha << parse_ok << ")\n";

        if(!parse_ok) {
            return std::make_tuple(parse_ok, integer_part);
        }

        result = static_cast<double>(integer_part);

        // FRACTIONAL PART
        if(!literal.fractional_part.empty()) {

            /* FixMe: Doesn't work that way, see e.g. at https://planetcalc.com/862/
             *        or on end on notes at the test case */

            std::tie(parse_ok, fractional_part) = parse_integer(base, literal.fractional_part);
            std::cout << "fractional_part: 1/" << fractional_part << " (" << std::boolalpha << parse_ok << ")";

            if(!parse_ok) {
                std::cout << "\n";
                return std::make_tuple(parse_ok, fractional_part);
            }

            double foo = 1.0 / static_cast<double>(fractional_part);
            std::cout << " -> " << foo << "\n";
            result += foo;
        }

        // EXPONENT
        if(!literal.exponent.empty()) {

            std::tie(parse_ok, exponent) = parse_exponent(literal);

            std::cout << "exponent: " << exponent << " (" << std::boolalpha << parse_ok << ")";

            if(!parse_ok) {
                std::cout << '\n';
                return std::make_tuple(parse_ok, exponent);
            }

            double pow = std::pow(
                static_cast<double>(base),
                static_cast<double>(exponent)
            );
            std::cout << " -> " << pow << '\n';
            result *= pow;
        }

        // ...
        std::cout << "RESULT = " << result << "\n";

        return std::make_tuple(true, result);
    }

};



int main()
{
    literal_convert convert{};

    std::cout << "--- literal ---\n";
    for(ast::literal const lit : {
        ast::literal{ast::literal::base_specifier::bin, "0"},
        ast::literal{ast::literal::base_specifier::bin, "1"},
        ast::literal{ast::literal::base_specifier::bin, "1_000"},
        ast::literal{ast::literal::base_specifier::bin, "0_001"},
    }) {
       auto const [ok, result] = convert(lit);

       std::cout << lit.literal << " -> " << result << '\n';
    }


    std::cout << "--- decimal_literal ---\n";
    for(ast::decimal_literal const lit : {
        ast::decimal_literal{"100", ast::decimal_literal::kind_specifier::integer},
        ast::decimal_literal{"1e6", ast::decimal_literal::kind_specifier::integer}, // !!!!! FixMe in Grammar
        ast::decimal_literal{"1.0e6", ast::decimal_literal::kind_specifier::real},
    }) {
        auto const [ok, result] = convert(lit);

        std::cout << lit.literal << " -> " << result << '\n';
    }


   /* Examples from
    * - VHDL Coding Styles and Methodologies
    * - IEEE_VHDL_1076-1993: Chapter 13.4.2 Based literals
    *
    *   2#1111_1111#            = 16 (integer literal)
    *   16#FF#                  = 16 (integer literal)
    *   16#E#E1                 = 224  (integer literal)
    *   2#1110_0000#            = 224  (integer literal)
    *   16#F.FF#E+2             = 4095.0 (real literal)
    *   2#1.1111_1111_111#E11   = 4095.0 (real literal)
    *
    * Algorithm (in Octave/Matlab):
    * base = 16
    * result = ( ...
    *    hex2dec('F')*base^0  ...
    * + ( ...
    *      hex2dec('F')/base^1 ...
    *    + hex2dec('F')/base^2 ...
    *    ) ...
    * ) * base^2
    *
    */
    std::cout << "--- based_literal ---\n";
    for(ast::based_literal const lit : {
//       ast::based_literal{"2", "111"},
//       ast::based_literal{"10", "42"},
//       ast::based_literal{"10", "42" , "8"},
//       ast::based_literal{"10", "42", "32", "e3"},
        // VHDL Coding Styles and Methodologies
        ast::based_literal{ "2", "1111_1111"},
        ast::based_literal{"16", "FF"},
        ast::based_literal{"016", "0FF"},
        ast::based_literal{"16", "E", std::string{}, "E+1"},
        ast::based_literal{ "2", "1110_0000"},
        ast::based_literal{"16", "F", "FF", "E+2"},
        ast::based_literal{ "2", "1", "1111_1111_111", "E11"},
    }) {

        std::cout << '\n';

        std::cout << "\nPARSE "
                  << lit.base << "#" << lit.integer_part
                  << (!lit.fractional_part.empty() ? "." + lit.fractional_part : "")
                  << (!lit.exponent.empty()     ? "#" + lit.exponent : "")
                  << "\n"
                  ;
        auto const [ok, result] = convert(lit);
    }
}

#if 0
#include <vector>
#include <string>
#include <iostream>
//#include <algorithm>
#include <numeric>
#include <limits>
#include <cmath>
#include <cassert>

template<unsigned Radix>
struct frac
{
    double pow;

    frac() : pow{Radix} {};

    static unsigned digit(auto ch)
    {
        // We trust Spirit.X3 on correct ASCII range and codes
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
            default:    abort();
        }
    };

    double operator()(double acc, char ch)
    {
        /* Fixme: The algorithm isn't smart to cover the failure cases. */
        double digit = frac<Radix>::digit(ch);
        digit /= pow;
        pow *= Radix;
        double const result = acc + digit;
        assert(std::isnormal(result) && "Fractional number isn't a number");
        return result;
    }

};

int main() {

    //std::vector<int> v{1,2,3,4,5};
    std::vector<char> v{'F','F'};

    auto const f = std::accumulate(v.begin(), v.end(), 0.0, frac<16>{});

    std::cout.precision(std::numeric_limits<double>::max_digits10);
    std::cout << "Result = " << (15 + f)*16*16 << "\n";
}
#endif

#if 0 // join ranges
#include <vector>
#include <deque>
#include <string>
#include <iostream>
#include <algorithm>
#include <boost/range/join.hpp>

int main() {
    // Iterated-over containers can be different types, as long as the
    // value types are the same (string, in this case).
    std::vector<std::string> vec1 = { "one", "two", "three" };
    std::deque<std::string> deq2 = { "four", "five", "six" };
    std::vector<std::string> vec3 = { "seven", "eight", "nine" };

    auto range1_2 = boost::join(vec1, deq2);
    auto range12_3 = boost::join(range1_2, vec3);

    for(auto s: range12_3) {
        std::cout << s << ' ';
    }
    std::cout << "\n";

    std::copy(range12_3.begin(), range12_3.end(),
              std::ostream_iterator<std::string>(std::cout, " "));

    std::cout << std::endl;

    return 0;
}
#endif
