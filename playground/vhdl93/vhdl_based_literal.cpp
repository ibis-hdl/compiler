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
        std::string                 exponent;
    };
}

namespace x3 = boost::spirit::x3;



struct foo
{
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

        using x3::extension::pow10;

        unsigned const exp_n = scratch_buf.length();
        double const exp = pow10<unsigned>(exp_n);
        frac_part /= exp;

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

        switch(base_) {
        case 2: {
            static constexpr unsigned radix{2};

            ok = extract_integer<radix>(literal, int_part);
            if(!ok) return false;

            ok = extract_fractional<radix>(literal, frac_part);
            if(!ok) return false;

            break;
        }
        case 8: {
            static constexpr unsigned radix{8};

            ok = extract_integer<radix>(literal, int_part);
            if(!ok) return false;

            ok = extract_fractional<radix>(literal, frac_part);
            if(!ok) return false;

            break;
        }
        case 10: {
            static constexpr unsigned radix{10};

            ok = extract_integer<radix>(literal, int_part);
            if(!ok) return false;

            ok = extract_fractional<radix>(literal, frac_part);
            if(!ok) return false;

            break;
        }
        case 16: {
            static constexpr unsigned radix{16};

            ok = extract_integer<radix>(literal, int_part);
            if(!ok) return false;

            ok = extract_fractional<radix>(literal, frac_part);
            if(!ok) return false;

            break;
        }
        default:
            std::cerr << "only bases of 2, 8, 10 and 16 are supported.";
            return false;
        }

        std::cout << "input: " << literal.integer_part;
        if(literal.fractional_part) {
            std::cout << "." << literal.fractional_part.value() << "\n";
        }
        std::cout << "base = " << base_
                  << ", int = " << int_part
                  << ", frac = " << frac_part
                  << " => " << std::fixed << (int_part + frac_part)
                  << "\n";

        return true;
    }
};

int main()
{
    ast::based_literal literal{ "010", "1_009", boost::optional<std::string>("012"), "e-12" };

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


