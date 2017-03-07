/*
 * qi_snippets.cpp
 *
 *  Created on: 06.03.2017
 *      Author: olaf
 */

/*
 * Why does this Boost.Spirit x3 rule parse correctly with angle brackets, but incorrectly with quotes?
 *
 * From SeHe:
 * https://stackoverflow.com/questions/39056992/why-does-this-boost-spirit-x3-rule-parse-correctly-with-angle-brackets-but-inco
 */

#include <boost/spirit/home/x3.hpp>
#include <iostream>
#include <cassert>

template <typename Prefix, typename Postfix>
static auto quoted_(Prefix const& prefix, Postfix const& postfix) {
    using namespace boost::spirit::x3;
    return rule<struct _, std::string, true> {} = lexeme [
        omit[prefix] >> *(char_ - postfix) >> omit[postfix]
    ];
}

template <typename Prefix>
static auto quoted_(Prefix const& prefix) { return quoted_(prefix, prefix); }

int main() {
    using boost::spirit::x3::space;

    auto header_name_brackets = quoted_('<', '>');
    auto header_name_quotes   = quoted_('"');

    {
        auto s = std::string{"<my/file.hpp>"};
        std::string parsed;
        assert(phrase_parse(s.begin(), s.end(), header_name_brackets, space, parsed));
    }

    {
        auto s = std::string{"\"my/file.hpp\""};
        std::string parsed;
        assert(phrase_parse(s.begin(), s.end(), header_name_quotes, space, parsed));
    }

    std::cout << "Bye\n";
}

/*
 * Parse int or double using boost spirit (longest_d)
 *
 * from SeHe:
 * https://stackoverflow.com/questions/13261502/parse-int-or-double-using-boost-spirit-longest-d
 */

#include <boost/spirit/include/qi.hpp>

using namespace boost::spirit::qi;

using A  = boost::variant<int, double>;
static real_parser<double, strict_real_policies<double>> const strict_double;

A parse(std::string const& s)
{
    typedef std::string::const_iterator It;
    It f(begin(s)), l(end(s));
    static rule<It, A()> const p = strict_double | int_;

    A a;
    assert(parse(f,l,p,a));

    return a;
}

int main()
{
    assert(0 == parse("42").which());
    assert(0 == parse("-42").which());
    assert(0 == parse("+42").which());

    assert(1 == parse("42.").which());
    assert(1 == parse("0.").which());
    assert(1 == parse(".0").which());
    assert(1 == parse("0.0").which());
    assert(1 == parse("1e1").which());
    assert(1 == parse("1e+1").which());
    assert(1 == parse("1e-1").which());
    assert(1 == parse("-1e1").which());
    assert(1 == parse("-1e+1").which());
    assert(1 == parse("-1e-1").which());
}


