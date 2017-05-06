#include <iostream>
//#define BOOST_SPIRIT_X3_DEBUG

#include <boost/spirit/home/x3.hpp>
#include <boost/spirit/home/x3/numeric/real_policies.hpp>
#include <boost/optional.hpp>

#include <algorithm> //copy_if
#include <iomanip>


namespace ast {
    struct based_literal {
        std::string                 base;
        std::string                 integer_part;
        boost::optional<std::string> fractional_part;
        boost::optional<std::string> exponent_part;
    };
}

namespace x3 = boost::spirit::x3;


namespace detail {

    template<unsigned Radix>
    double exponent(unsigned n)
    {
        double exp{ 1 };
        for(unsigned i = 0; i != n; ++i) {
            exp *= Radix;
        }
        return exp;
    }
}

struct foo
{
    /*
     * Parsing separated numeric literals aren't directly support by spirit.x3.
     * On character level a string(_view) is created, on lexeme level a vector
     * of integers are created which doesn't simplify the process since several
     * separators are allowed. Hence this approach uses a scratch buffer string
     * to prune the separators.
     * Useful may be a string which works on stack using a buffer or heap for
     * larger strings, e.g. see
     * https://stackoverflow.com/questions/39896348/does-a-stdstring-always-require-heap-memory/39896438
     */
    template<typename RangeT>
    void strip_separator(RangeT const& input, std::string& stripped)
    {
        std::copy_if(input.begin(), input.end(),
            std::back_inserter(stripped), [](auto c) {
                return c != '_';
        });
    }

    template<typename AttrT, unsigned Radix>
    bool parse_numeric_attr(std::string const& input, AttrT& attr)
    {
        auto iter = input.begin(), end = input.end();

        typedef x3::uint_parser<AttrT, Radix> parser_type;
        parser_type const parser = parser_type{};

        bool ok = x3::parse(iter, end, parser, attr);
        return ok && (iter == end);
    }

    unsigned extract_base(ast::based_literal const& literal, std::string& buffer)
    {
        unsigned base_{0};

        strip_separator(literal.base, buffer);

        auto iter = buffer.begin(), end = buffer.end();
        bool ok = x3::parse(iter, end, x3::uint_, base_);
        assert(ok && "parse <based_literal.base> failed!");

        return base_;
    }

    template<unsigned Radix>
    bool extract_integer(ast::based_literal const& literal, unsigned& int_part)
    {
        std::string scratch_buf;
        strip_separator(literal.integer_part, scratch_buf);

        bool ok = parse_numeric_attr<unsigned, Radix>(scratch_buf, int_part);
        if(!ok) {
            std::cout << "parsing with base of " << Radix << " failed for integer part\n";
        }

        return ok;
    }

    template<unsigned Radix>
    bool extract_fractional(ast::based_literal const& literal, double& frac_part)
    {
        std::string scratch_buf;
        if(!literal.fractional_part) {
            std::cout << "there is no fractional part\n";
            frac_part = 0;
            return true;
        }

        strip_separator(literal.fractional_part.get(), scratch_buf);

        bool ok = parse_numeric_attr<double, Radix>(scratch_buf, frac_part);
        if(!ok) {
            std::cout << "parsing with base of " << Radix << " failed for fractional part\n";
        }

        unsigned const exp_n = scratch_buf.length();
        frac_part /= detail::exponent<Radix>(exp_n);

        return ok;
    }

    template<unsigned Radix>
    bool extract_exponent(ast::based_literal const& literal, double& exponent_part)
    {
        exponent_part = 1;

        if(!literal.exponent_part) {
            std::cout << "there is no exponent part\n";
            return true;
        }

        std::string const& part = literal.exponent_part.get();
        assert((part[0] == 'E' || part[0] == 'e') && "Parser internal Error! No exponent found!");

        bool pos_sign = true;
        unsigned first = 0;
        switch(part[1]) {
        case '-':
            pos_sign = false;
            first = 2;
            break;
        case '+':
            first = 2;
            break;
        default:
            first = 1;
        }
        std::cout << "pure exp = " <<  Radix << "^" << (pos_sign ? '+' : '-')
                  << part.substr(first, std::string::npos) << "\n";

        std::string scratch_buf;

        strip_separator(part.substr(first, std::string::npos), scratch_buf); // string_view candidate

        unsigned exp_n{ 0 };
        bool ok = parse_numeric_attr<unsigned, 10>(scratch_buf, exp_n);
        if(!ok) {
            std::cout << "parsing with base of " << Radix << " failed for exponent part\n";
        }

        std::cout << "=> exp = " << Radix << "^" << exp_n << "\n";
        if(pos_sign) {
            exponent_part *= detail::exponent<Radix>(exp_n);
        }
        else {
            exponent_part /= detail::exponent<Radix>(exp_n);
        }

        return ok;
    }

    bool extract(ast::based_literal const& literal)
    {
        std::string       scratch_buf;

        unsigned base_ = extract_base(literal, scratch_buf);

        scratch_buf.clear(); // reuse buffer

        bool ok;
        unsigned int_part{ 0 };
        double frac_part{ 0 };
        double exp_part{ 0 };

        switch(base_) {
        case 2: {
            static constexpr unsigned radix{2};

            ok = extract_integer<radix>(literal, int_part);
            if(!ok) return false;

            ok = extract_fractional<radix>(literal, frac_part);
            if(!ok) return false;

            ok = extract_exponent<radix>(literal, exp_part);
            if(!ok) return false;

            break;
        }
        case 8: {
            static constexpr unsigned radix{8};

            ok = extract_integer<radix>(literal, int_part);
            if(!ok) return false;

            ok = extract_fractional<radix>(literal, frac_part);
            if(!ok) return false;

            ok = extract_exponent<radix>(literal, exp_part);
            if(!ok) return false;

            break;
        }
        case 10: {
            static constexpr unsigned radix{10};

            ok = extract_integer<radix>(literal, int_part);
            if(!ok) return false;

            ok = extract_fractional<radix>(literal, frac_part);
            if(!ok) return false;

            ok = extract_exponent<radix>(literal, exp_part);
            if(!ok) return false;

            break;
        }
        case 16: {
            static constexpr unsigned radix{16};

            ok = extract_integer<radix>(literal, int_part);
            if(!ok) return false;

            ok = extract_fractional<radix>(literal, frac_part);
            if(!ok) return false;

            ok = extract_exponent<radix>(literal, exp_part);
            if(!ok) return false;

            break;
        }
        default:
            std::cerr << "only bases of 2, 8, 10 and 16 are supported.";
            return false;
        }

        std::cout << "input: " << literal.integer_part;
        if(literal.fractional_part) {
            std::cout << "." << literal.fractional_part.value();
        }
        if(literal.exponent_part) {
            std::cout << literal.exponent_part.value();
        }
        std::cout << "\n";
        std::cout << "base = " << base_
                  << ", int = " << int_part
                  << ", frac = " << frac_part
                  << ", exp = " << exp_part
                  << " => " << std::fixed << (int_part + frac_part)*exp_part
                  << "\n";

        return true;
    }
};

int main()
{
#if 0
    // 4096.0
    ast::based_literal literal{ "016", "F",
                                boost::optional<std::string>("FF"),
                                boost::optional<std::string>("e+2") };
#else
    // 4096.0
    ast::based_literal literal{ "2", "1",
                                boost::optional<std::string>("1111_1111_111"),
                                boost::optional<std::string>("e11") };
#endif

    foo f;
    f.extract(literal);

    return 0;
}

#if 0
    /* doesn't work for fractional, only pow10 is used nevertheless the radix
     * by x3 */

namespace parser {

    template<typename T, unsigned Radix>
    struct numeric_policies : x3::ureal_policies<T>
    {
        static bool const allow_leading_dot = true;
        static bool const allow_trailing_dot = false;
        static bool const expect_dot = false;

        template <typename Iterator>
        static bool
        parse_sign(Iterator& /*first*/, Iterator const& /*last*/)
        {
            return false;
        }

        template <typename Iterator, typename Attribute>
        static bool
        parse_n(Iterator& first, Iterator const& last, Attribute& attr_)
        {
            return x3::extract_uint<T, Radix, 1, -1>::call(first, last, attr_);
        }

        template <typename Iterator, typename Attribute>
        static bool
        parse_frac_n(Iterator& first, Iterator const& last, Attribute& attr_)
        {
            return x3::extract_uint<T, Radix, 1, -1, true>::call(first, last, attr_);
        }

        template <typename Iterator>
        static bool
        parse_exp_n(Iterator& first, Iterator const& last, int& attr_)
        {
            return x3::extract_int<int, Radix, 1, -1>::call(first, last, attr_);
        }

        template <typename Iterator, typename Attribute>
        static bool
        parse_nan(Iterator& /*first*/, Iterator const& /*last*/, Attribute& /* attr_ */)
        {
            return false;
        }

        template <typename Iterator, typename Attribute>
        static bool
        parse_inf(Iterator& /*first*/, Iterator const& /*last*/, Attribute& /* attr_ */)
        {
            return false;
        }
    };



    template <typename T, unsigned Radix, typename RealPolicies = numeric_policies<T, Radix> >
    struct numeric_parser : x3::parser<numeric_parser<T, Radix, RealPolicies> >
    {
        typedef T attribute_type;
        static bool const has_attribute = true;

        numeric_parser() : policies() {}

        numeric_parser(RealPolicies const& policies) : policies(policies) {}

        template <typename Iterator, typename Context>
        bool parse(Iterator& first, Iterator const& last
          , Context& context, x3::unused_type, T& attr_) const
        {
            x3::skip_over(first, last, context);
            return x3::extract_real<T, RealPolicies>::parse(first, last, attr_, policies);
        }

        template <typename Iterator, typename Context, typename Attribute>
        bool parse(Iterator& first, Iterator const& last
          , Context& context, x3::unused_type, Attribute& attr_param) const
        {
            // this case is called when Attribute is not T
            T attr_;
            if (parse(first, last, context, x3::unused, attr_))
            {
                x3::traits::move_to(attr_, attr_param);
                return true;
            }
            return false;
        }

        RealPolicies policies;
    };

    typedef numeric_parser<double,  2> numeric_bin_type;
    typedef numeric_parser<double,  8> numeric_oct_type;
    typedef numeric_parser<double, 10> numeric_dec_type;
    typedef numeric_parser<double, 16> numeric_hex_type;

    numeric_bin_type const numeric_bin{};
    numeric_oct_type const numeric_oct{};
    numeric_dec_type const numeric_dec{};
    numeric_hex_type const numeric_hex{};

} // parser

void test()
{
    std::string input{"1000"};
    double x;
    {
        auto iter = input.begin(), end = input.end();
        bool ok = x3::parse(iter, end, parser::numeric_bin, x);
        std::cout << std::boolalpha << ok << " -> " << x << "\n";
    }
    {
        auto iter = input.begin(), end = input.end();
        bool ok = x3::parse(iter, end, parser::numeric_oct, x);
        std::cout << std::boolalpha << ok << " -> " << x << "\n";
    }
    {
        auto iter = input.begin(), end = input.end();
        bool ok = x3::parse(iter, end, parser::numeric_dec, x);
        std::cout << std::boolalpha << ok << " -> " << x << "\n";
    }
    {
        auto iter = input.begin(), end = input.end();
        bool ok = x3::parse(iter, end, parser::numeric_hex, x);
        std::cout << std::boolalpha << ok << " -> " << x << "\n";
    }
}
#endif


