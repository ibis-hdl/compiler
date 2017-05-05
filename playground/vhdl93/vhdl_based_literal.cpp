#include <iostream>
//#define BOOST_SPIRIT_X3_DEBUG

#include <boost/spirit/home/x3.hpp>
#include <boost/optional.hpp>

#include <algorithm> //copy_if


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
    static constexpr const char* binary_charset[] = { "01" };
    static constexpr const char* octal_charset[] = { "0-7" };
    static constexpr const char* decimal_charset[] = { "0-9" };
    static constexpr const char* hexadecimal_charset[] = { "0-9A-Za-z" };

    template<typename RangeT>
    bool strip_separator(RangeT const& input, std::string const& charset, std::string& stripped)
    {
        std::copy_if(input.begin(), input.end(),
            std::back_inserter(stripped),
            [](auto c) {
                return c != '_';
        });
    }

    template<typename AttrT, unsigned Radix>
    bool parse_numeric_attr(std::string const& input, AttrT& attr)
    {
        auto iter = input.begin(), end = input.end();

        typedef x3::uint_parser<AttrT, Radix> parser_type;
        parser_type const parser = parser_type();

        bool ok = x3::parse(iter, end, parser, attr);
        return ok && (iter == end);
    }

    unsigned base(ast::based_literal const& literal, std::string const& charset, std::string& buffer)
    {
        unsigned base_{0};

        bool ok = strip_separator(literal.base, charset, buffer);
        assert(ok);

        ok = parse_numeric_attr<unsigned, 10>(buffer, base_);
        assert(ok);

        return base_;
    }

    unsigned integer(ast::based_literal const& literal, std::string const& charset, std::string& buffer)
    {
        bool ok = strip_separator(literal.integer_part, charset, buffer);
        assert(ok);

        return ok;
    }

    bool extract(ast::based_literal const& literal)
    {
        std::string       scratch_buf;
        std::string const dec_charset{ *decimal_charset };

        unsigned base_ = base(literal, dec_charset, scratch_buf);

        scratch_buf.clear(); // reuse buffer

        bool ok;
        unsigned int_part{ 0 };

        switch(base_) {
        case 2: {
            std::string const charset{ *binary_charset };
            ok = integer(literal, charset, scratch_buf);
            ok = parse_numeric_attr<unsigned,  2>(scratch_buf, int_part);
            break;
        }
        case 8: {
            std::string const charset{ *octal_charset };
            ok = integer(literal, charset, scratch_buf);
            ok = parse_numeric_attr<unsigned,  8>(scratch_buf, int_part);
            break;
        }
        case 10: {
            ok = integer(literal, dec_charset, scratch_buf);
            ok = parse_numeric_attr<unsigned, 10>(scratch_buf, int_part);
            break;
        }
        case 16: {
            std::string const charset{ *hexadecimal_charset };
            ok = integer(literal, charset, scratch_buf);
            ok = parse_numeric_attr<unsigned, 16>(scratch_buf, int_part);
            break;
        }
        default:
            std::cerr << "only bases of 2, 8, 10 and 16 are supported.";
        }

        std::cout << "base = " << base_ << ", int = " << int_part << "\n";

        return ok;
    }
};

int main()
{
    ast::based_literal literal{ "016", "1_000", boost::optional<std::string>("012"), "e-12" };

    foo f;
    f.extract(literal);
    return 0;
}


