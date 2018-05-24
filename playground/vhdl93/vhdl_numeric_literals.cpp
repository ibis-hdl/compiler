/*
 * vhdl_numeric_literals.cpp
 *
 *  Created on: 21.05.2018
 *      Author: olaf
 */

#include <iostream>
#include <string>
#include <algorithm>
#include <numeric>  // accumulate
#include <iterator>
#include <cassert>
#include <boost/range/iterator_range.hpp>
#include <boost/iterator/filter_iterator.hpp>

//#define BOOST_SPIRIT_X3_DEBUG
#include <boost/spirit/home/x3.hpp>
#include <boost/fusion/include/adapt_struct.hpp>


namespace x3 = boost::spirit::x3;


namespace ast {


struct bit_string_literal {
    enum base_specifier { bin, oct, hex };

    std::string     literal;
    base_specifier  base;
};

struct decimal_literal
{
    enum class kind_specifier { integer, real };

    std::string     literal;
    kind_specifier  kind;
};

struct based_literal
{
    /*
     * The tagged type is elementary on elaboration time, since after converting
     * informations about the integer/real string are lost, see e.g.
     * [vhdl error: integer literal cannot have negative exponent](
     * https://stackoverflow.com/questions/22113223/vhdl-error-integer-literal-cannot-have-negative-exponent)
     */
    enum class kind_specifier { integer, real };

    struct number {
        std::string     integer_part;
        std::string     fractional_part;
        std::string     exponent;
        kind_specifier  kind;
    };

    std::string         base;
    number              literal;
};


std::ostream& operator<<(std::ostream& os, bit_string_literal::base_specifier base)
{
    using base_specifier = ast::bit_string_literal::base_specifier;

    switch(base) {
        case base_specifier::bin: { os << "bin"; break; }
        case base_specifier::oct: { os << "oct"; break; }
        case base_specifier::hex: { os << "hex"; break; }
        default:                        abort();
    }
    return os;
}

std::ostream& operator<<(std::ostream& os, decimal_literal::kind_specifier kind)
{
    using kind_specifier = ast::decimal_literal::kind_specifier;

    switch(kind) {
        case kind_specifier::integer: { os << "integer"; break; }
        case kind_specifier::real:    { os << "real"; break; }
        default:                        abort();
    }
    return os;
}

std::ostream& operator<<(std::ostream& os, based_literal::kind_specifier kind)
{
    using kind_specifier = ast::based_literal::kind_specifier;

    switch(kind) {
        case kind_specifier::integer: { os << "integer"; break; }
        case kind_specifier::real:    { os << "real"; break; }
        default:                        abort();
    }
    return os;
}



} // namespace ast


BOOST_FUSION_ADAPT_STRUCT(ast::bit_string_literal,
    literal, base
)

BOOST_FUSION_ADAPT_STRUCT(ast::decimal_literal,
    literal, kind
)

BOOST_FUSION_ADAPT_STRUCT(ast::based_literal::number,
    integer_part, fractional_part, exponent, kind
)

BOOST_FUSION_ADAPT_STRUCT(ast::based_literal,
    base, literal
)


namespace parser {


using x3::char_;
using x3::lit;

template<typename T>
auto as = [](auto p) { return x3::rule<struct _, T>{} = x3::as_parser(p); };

auto const integer = x3::rule<struct _, std::string> { "integer" } =
    char_("0-9") >> *( -lit("_") >> char_("0-9") )
    ;

auto const exponent = x3::rule<struct _, std::string> { "exponent" } =
    char_("Ee") >> -char_("-+") >> integer
    ;

/* Note, specify valid chars for each base in real case. The BNF doesn't specify
 * explicit the valid bit values on given base. */
auto const bit_value = x3::rule<struct _, std::string> { "bit_value" } =
    char_("0-9a-fA-F") >> *( -lit('_') >> char_("0-9a-fA-F") )
    ;

auto const bit_string_literal = x3::rule<struct _, ast::bit_string_literal> { "bit_string_literal" } =
      (x3::omit[char_("Bb")] >> lit('"') >> bit_value >> lit('"') >> x3::attr(ast::bit_string_literal::base_specifier::bin))
    | (x3::omit[char_("Oo")] >> lit('"') >> bit_value >> lit('"') >> x3::attr(ast::bit_string_literal::base_specifier::oct))
    | (x3::omit[char_("Xx")] >> lit('"') >> bit_value >> lit('"') >> x3::attr(ast::bit_string_literal::base_specifier::hex))
    ;

auto const based_integer = x3::rule<struct _, std::string> { "based_integer" } =
     char_("0-9a-fA-F") >> *( -lit('_') >> char_("0-9a-fA-F") )
    ;

auto const decimal_literal_int = x3::rule<struct _, ast::decimal_literal> { "decimal_literal<int>" } =
       as<std::string>(integer >> -(char_("Ee") >> integer))
    >> x3::attr(ast::decimal_literal::kind_specifier::integer)
    ;

auto const decimal_literal_real = x3::rule<struct _, ast::decimal_literal> { "decimal_literal<real>" } =
       as<std::string>(integer >> char_('.') >> integer >> -exponent)
    >> x3::attr(ast::decimal_literal::kind_specifier::real)
    ;

auto const decimal_literal = x3::rule<struct _, ast::decimal_literal>{ "decimal_literal" } =
      decimal_literal_real
    | decimal_literal_int
    ;

auto const based_literal_int = x3::rule<struct _, ast::based_literal::number>{ "based_literal<int>" } =
       based_integer >> x3::attr(std::string{/* empty fractional part */})
    >> '#'
    >> -exponent
    >> x3::attr(ast::based_literal::kind_specifier::integer)
    ;

auto const based_literal_real = x3::rule<struct _, ast::based_literal::number>{ "based_literal<real>" } =
       based_integer >> lit('.') >> based_integer
    >> '#'
    >> -exponent
    >> x3::attr(ast::based_literal::kind_specifier::real)
    ;

auto const based_literal = x3::rule<struct _, ast::based_literal>{ "based_literal" } =
       integer  // base
    >> '#'
    >> (based_literal_real | based_literal_int)
    ;

} // namespace parser


namespace detail {


template <typename T>
struct integer_policies : x3::ureal_policies<T>
{
    static bool const allow_leading_dot = false;
    static bool const allow_trailing_dot = false;
    static bool const expect_dot = false;
};

template <typename T>
struct real_policies : x3::ureal_policies<T>
{
    static bool const allow_leading_dot = false;
    static bool const allow_trailing_dot = false;
    static bool const expect_dot = false;
};

/* VDL decimal literals does allow exponents on integers, to simplify evaluating
 * a x3 real parser with policies is used. The correct 2nd pass parsing and hence
 * converting depends on correct parsing of the VHDL grammar, since the exponent
 * of integer doesn't allow any sign. The rule used here consider this. */
x3::real_parser<double, detail::integer_policies<uint32_t>> integer_base10;

x3::real_parser<double, detail::real_policies<double>> real_base10;

auto const exponent = x3::rule<struct _, uint32_t>{} =
        x3::omit[
             (x3::lit('e') | 'E')
        ]
    >> x3::int32
    ;


} // namespace detail


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
    /*
     * We trust in the correct VHDL grammar rules which feeds this numeric
     * literal_parser. This allows to use 'sloppy' rules to convert from
     * strings to numeric values.
     *
     * Treat all of x3's attribute type as double for simplification, otherwise
     * one has to handle with different return types using C++ lambdas.
     */
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

        bool const parse_ok = parse(range, detail::integer_base10, attribute);

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
               AttributeType &attribute) const
    {
        auto range_f{ filter_range(range) };
        auto iter = std::begin(range_f);
        auto const last = std::cend(range_f);

        bool const parse_ok = x3::parse(iter, last, parser, attribute);
#if 0
        std::cout << "inside literal_parser::parse (" << range << ") -> "
                  << std::boolalpha << (parse_ok && (iter == last))
                  << '\n';
#endif
        return parse_ok && (iter == last);
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

    typedef std::tuple<bool, double>            return_type;
    literal_parser                              literal_parse;


    return_type operator()(ast::bit_string_literal const& literal) const
    {
        using base_specifier = ast::bit_string_literal::base_specifier;

        auto const parse = [this](ast::bit_string_literal const& literal)
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


    /* Note: The natural way would be to use Spirit.X3 arser primitive, e.g.
     * specialize x3's ureal_policies using a radix template parameter, which
     * compiles so far.
     * Unfortunately, spirit uses a LUT of pow10 - no other radixes are supported
     * at lower level. So the results are wrong.
     * So we have to use our own version. */
    return_type operator()(ast::based_literal const& literal) const
    {
        auto const parse_base = [this](ast::based_literal const& literal) {
            return literal_parse(literal.base, tag::dec{});
        };

        auto const parse_integer_part = [this](unsigned base, auto const& literal) {
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

        auto const parse_fractional_part = [this](unsigned base, auto const& literal) {
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

        auto const parse_exponent = [this](unsigned base, auto const& literal) {
            return literal_parse(literal, tag::exp{});
        };

        uint32_t base{ 0 };
        double result { 0.0 };

        bool parse_ok{ false };

        // BASE
        std::tie(parse_ok, base) = parse_base(literal);
        std::cout << "  base: " << base << " (" << std::boolalpha << parse_ok << ")\n";

        if(!parse_ok) {
            return std::make_tuple(parse_ok, base);
        }

        // INTEGER PART
        std::tie(parse_ok, result) = parse_integer_part(base, literal.literal.integer_part);
        std::cout << "  integer_part: " << result << " (" << std::boolalpha << parse_ok << ")\n";

        if(!parse_ok) {
            return std::make_tuple(parse_ok, result);
        }

        // FRACTIONAL PART
        if(!literal.literal.fractional_part.empty()) {
#if 0
            uint32_t fractional_part{ 0 };

            std::tie(parse_ok, fractional_part) = parse_fractional_part(base, literal.literal.fractional_part);

            if(!parse_ok) {
                std::cout << "\n";
                return std::make_tuple(parse_ok, fractional_part);
            }
#endif
            auto const frac_obj = [this](unsigned base) {
                switch(base) {
                    case  2:  return frac{ 2};
                    case  8:  return frac{ 8};
                    case 10:  return frac{10};
                    case 16:  return frac{16};
                    default:  abort();
                }
            };

            auto iter = std::begin(literal.literal.fractional_part);
            auto const last = std::cend(literal.literal.fractional_part);
            auto const f = std::accumulate(iter, last, 0.0, frac_obj(base));

            std::cout << "  fractional_part: " << f << "\n";
            result += f;
        }

        // EXPONENT
        if(!literal.literal.exponent.empty()) {

            int32_t exponent{ 0 };

            std::tie(parse_ok, exponent) = parse_exponent(base, literal.literal.exponent);

            std::cout << "  exponent: " << exponent << " (" << std::boolalpha << parse_ok << ")";

            if(!parse_ok) {
                std::cout << '\n';
                return std::make_tuple(parse_ok, exponent);
            }

            double const pow = std::pow(
                static_cast<double>(base),
                static_cast<double>(exponent)
            );
            std::cout << "  exponent: " << pow << '\n';
            result *= pow;
        }

        // ...

        return std::make_tuple(true, result);
    }

};



int main()
{
    literal_convert convert{};

    std::cout << "\n--- bit_string_literal ---\n";
    for(std::string const s : {
        R"(B"0")",
        R"(B"1")",
        R"(B"100_00")",
        R"(O"123_456")",
        R"(X"AFFE")",
        R"(X"00_EBBE_0")",
    }) {
        ast::bit_string_literal bit_string_literal{};
        auto iter = std::begin(s);
        auto const last = std::cend(s);
        auto const parse_ok = x3::parse(iter, last,
                parser::bit_string_literal, bit_string_literal);

        if(iter != last) {
            std::cout << "ERROR: VHDL parsing of '" << s << "' failed, rest = "
                      << std::distance(iter, last)
                      << "-> no conversion!\n";
            continue;
        }

        auto const [ok, result] = convert(bit_string_literal);

        std::cout.precision(std::numeric_limits<double>::max_digits10);
        std::cout << s << " -> " << result << " "
                  << bit_string_literal.base
                  << " (" << std::boolalpha << parse_ok << ", " << ok
                  << ")\n";
    }


    std::cout << "\n--- decimal_literal ---\n";
    for(std::string const s : {
        "0", "1",
        "100",
        "1_000_000",
        //"1_000e3",        // integer
        "1.0e6",            // real
        "1_023.1_023e-4",
        // failure test cases
        "1_000e-3",         // integer

    }) {
        ast::decimal_literal decimal_literal{};
        auto iter = std::begin(s);
        auto const last = std::cend(s);
        auto const parse_ok = x3::parse(iter, last,
                parser::decimal_literal, decimal_literal);

        if(iter != last) {
            std::cout << "ERROR: VHDL parsing of '" << s << "' failed, rest = "
                      << std::distance(iter, last)
                      << "-> no conversion!\n";
            continue;
        }

        auto const [ok, result] = convert(decimal_literal);

        std::cout.precision(std::numeric_limits<double>::max_digits10);
        std::cout << s << " -> " << result << " "
                  << decimal_literal.kind
                  << " (" << std::boolalpha << parse_ok << ", " << ok
                  << ")\n";
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
    std::cout << "\n--- based_literal ---\n";
    for(std::string const s : {
        // LRM examples
        "2#1111_1111#",             // 16
        "16#FF#",                   // 16
        "016#0FF#",                 // 16
        "16#E#E1",                  // 224
        "2#1110_0000#",             // 224
        "16#F.FF#E+2",              // 4095.0
        "2#1.1111_1111_111#E11",    // 4095.0
        // border cases
        "2#1.0#",                   // 1.0
        "10#42.0#",
        "10#42.000_1#",
        // other
        "16#FF.FF#E-2",
    }) {

        ast::based_literal based_literal{};
        auto iter = std::begin(s);
        auto const last = std::cend(s);
        auto const parse_ok = x3::parse(iter, last,
                parser::based_literal, based_literal);

        if(iter != last) {
            std::cout << "ERROR: VHDL parsing of '" << s << "' failed, rest = "
                      << std::distance(iter, last)
                      << "-> no conversion!\n";
            continue;
        }
#if 0
        std::cout << "\nCONVERT/PARSE "
                  << based_literal.base << "#" << based_literal.literal.integer_part
                  << (!based_literal.literal.fractional_part.empty() ? "." + based_literal.literal.fractional_part : "")
                  << (!based_literal.literal.exponent.empty()     ? "#" + based_literal.literal.exponent : "")
                  << "\n"
                  ;
#endif
        auto const [ok, result] = convert(based_literal);

        std::cout.precision(std::numeric_limits<double>::max_digits10);
        std::cout << s << " -> " << result << " "
                  << based_literal.literal.kind
                  << " (" << std::boolalpha << parse_ok << ", " << ok
                  << ")\n\n";
    }

}

#if 0
/*
 * Concept of calculating fractional part
 */
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
