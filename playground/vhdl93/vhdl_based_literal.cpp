#include <iostream>
//#define BOOST_SPIRIT_X3_DEBUG

#include <boost/spirit/home/x3.hpp>
#include <boost/optional.hpp>

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
    std::string        scratch_buf;
    static constexpr const char* bin_charset[] = { "01" };
    static constexpr const char* oct_charset[] = { "0-7" };
    static constexpr const char* dec_charset[] = { "0-9" };
    static constexpr const char* hex_charset[] = { "0-9A-Za-z" };

    template<typename RangeT>
    bool parse_separated(RangeT const& input, std::string const& charset)
    {
        auto iter = input.begin(), end = input.end();
        bool ok = x3::parse(iter, end,
                             x3::char_(charset)
                          >> *( -x3::lit('_')
                              >> x3::char_(charset)
                              )
                        , scratch_buf);
        std::cout << "buf = " << scratch_buf << "\n";
        return ok && (iter == end);
    }

    template<typename AttrT>
    bool parse_bin(AttrT& attr)
    {
        auto iter = scratch_buf.begin(), end = scratch_buf.end();

        typedef x3::uint_parser<AttrT, 2 /* Radix */> parser_type;
        parser_type const parser = parser_type();

        bool ok = x3::parse(iter, end, parser, attr);
        return ok && (iter == end);
    }

    template<typename AttrT>
    bool parse_oct(AttrT& attr)
    {
        auto iter = scratch_buf.begin(), end = scratch_buf.end();

        typedef x3::uint_parser<AttrT, 8 /* Radix */> parser_type;
        parser_type const parser = parser_type();

        bool ok = x3::parse(iter, end, parser, attr);
        return ok && (iter == end);
    }

    template<typename AttrT>
    bool parse_dec(AttrT& attr)
    {
        auto iter = scratch_buf.begin(), end = scratch_buf.end();

        typedef x3::uint_parser<AttrT, 10 /* Radix */> parser_type;
        parser_type const parser = parser_type();

        bool ok = x3::parse(iter, end, parser, attr);
        return ok && (iter == end);
    }

    template<typename AttrT>
    bool parse_hex(AttrT& attr)
    {
        auto iter = scratch_buf.begin(), end = scratch_buf.end();

        typedef x3::uint_parser<AttrT, 16 /* Radix */> parser_type;
        parser_type const parser = parser_type();

        bool ok = x3::parse(iter, end, parser, attr);
        return ok && (iter == end);
    }

    unsigned parse_base(ast::based_literal const& literal, std::string const& charset)
    {
        scratch_buf.clear();

        unsigned base{0};
        // base is decimal
        bool ok = parse_separated(literal.base, charset);
        assert(ok);
        ok = parse_dec(base);
        assert(ok);
        return base;
    }

    unsigned parse_integer(ast::based_literal const& literal, std::string const& charset)
    {
        scratch_buf.clear();

        bool ok = parse_separated(literal.integer_part, charset);
        assert(ok);
        std::cout << "integer(str) = " << scratch_buf << "\n";
        return ok;
    }

    bool extract(ast::based_literal const& literal)
    {
        unsigned base = parse_base(literal, *dec_charset);

        bool ok;
        unsigned int_part{ 0 };

        switch(base) {
        case 2:
            ok = parse_integer(literal, std::string(*bin_charset));
            ok = parse_bin(int_part);
            break;
        case 8:
            ok = parse_integer(literal, std::string(*oct_charset));
            ok = parse_oct(int_part);
            break;
        case 10:
            ok = parse_integer(literal, std::string(*dec_charset));
            ok = parse_dec(int_part);
            break;
        case 16:
            ok = parse_integer(literal, std::string(*hex_charset));
            ok = parse_hex(int_part);
            break;
        default:
            std::cerr << "only bases of 2, 8, 10 and 16 are supported.";
        }

        std::cout << "int = " << int_part << "\n";

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


