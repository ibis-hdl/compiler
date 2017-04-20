/*
 * string_literal_view.cpp
 *
 *  Created on: 14.04.2017
 *      Author: olaf
 */

#include <iostream>
#include <vector>


#include <experimental/string_view>

namespace boost { namespace spirit { namespace x3 { namespace traits {

template <typename It>
void move_to(It b, It e, std::experimental::string_view& v)
{
    // Note requires storage to be contiguous
    v = std::experimental::string_view(&*b, e - b);
}

} } } }


//#define BOOST_SPIRIT_X3_DEBUG
#include <boost/spirit/home/x3.hpp>

#if 1
// XXX basic_string_view<char>« has no member named »insert« XXX
typedef std::experimental::string_view  attribute_type;
#else
typedef std::string                     attribute_type;
#endif

namespace parser {

    namespace x3 = boost::spirit::x3;
    namespace iso8859_1 = boost::spirit::x3::iso8859_1;

    using iso8859_1::char_;

    auto const string_literal = x3::rule<struct _, attribute_type> { "string_literal" } =
        x3::lexeme[
            (      '"'
                >> x3::raw[
                    *(  (char_ - '"')
                     | "\"\""
                     )
                ]
                >> '"'
            )
        ]
        ;
}


int main()
{
    namespace x3 = boost::spirit::x3;

    std::vector<std::string> const test_cases {
        R"("FooBar")",
        R"("FooBar"  )",
        R"(    "FooBar"  )",
        R"(" "" FooBarBaz "" ")"       // with ""inner escaped"" quotes
        };

    /* expected output:
     * parse '"FooBar"': succeeded: 'FooBar'
     * parse '"FooBar"  ': succeeded: 'FooBar'
     * parse '    "FooBar"  ': succeeded: 'FooBar'
     * parse '" "" FooBarBaz "" "': succeeded: ' "" FooBarBaz "" '
     */

    typedef std::string::const_iterator iterator_type;

    for(auto str: test_cases) {
        iterator_type iter = str.begin();
        iterator_type const end = str.end();

        attribute_type attr;

        auto& rule = parser::string_literal;

        std::cout << "parse '" << str << "': ";

        bool r = phrase_parse(iter, end, *x3::space >> rule, x3::space, attr);

        if (r && iter == end) {
            std::cout << "succeeded: '" << attr << "'\n";
        } else {
            std::cout << "*** failed ***\n";
        }
    }

    return 0;
}






