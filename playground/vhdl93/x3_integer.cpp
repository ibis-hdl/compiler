/*
 * x3_integer.cpp
 *
 *  Created on: 06.03.2017
 *      Author: olaf
 */

#include <iosfwd>
//#define BOOST_SPIRIT_X3_DEBUG

#include <boost/spirit/home/x3.hpp>
#include <iostream>

namespace parser {

    namespace x3 = boost::spirit::x3;
    namespace iso8859_1 = boost::spirit::x3::iso8859_1;

    using iso8859_1::char_;

    struct integer_class;

    typedef x3::rule<integer_class, int> integer_type;

    integer_type const integer { "integer" };

    // Hint: uint_parser<unsigned, 10, 3, 3> uint3_3_p;      //  exactly 3 digits
    auto const integer_def =
#if 1
        x3::omit[
             x3::digit >> *( -char_('_') >> x3::digit )
        ]
#else
        x3::int_
#endif
        ;

    BOOST_SPIRIT_DEFINE(
        integer
    );
}


int main()
{
    namespace x3 = boost::spirit::x3;

    std::vector<std::string> const test_cases {
        "1",
        "42_666_4711"
        };

    typedef std::string::const_iterator iterator_type;

    for(auto str: test_cases) {
        iterator_type iter = str.begin();
        iterator_type const end = str.end();

        int result;
        auto& rule = parser::integer;

        std::cout << "parse " << str << ": ";

        bool r = x3::phrase_parse(iter, end, rule, rule /*, result*/);

        if (r && iter == end) {
            std::cout << "succeeded\n";
        } else {
            std::cout << "failed\n";
        }
    }

    return 0;
}






