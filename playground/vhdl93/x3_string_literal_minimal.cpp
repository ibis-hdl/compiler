/*
 * x3_string_literal_minimal.cpp
 *
 *  Created on: 04.03.2017
 *      Author: olaf
 */

#include <iostream>
#include <vector>

#define BOOST_SPIRIT_X3_DEBUG


#include <boost/spirit/home/x3.hpp>

namespace parser {

	namespace x3 = boost::spirit::x3;
	namespace iso8859_1 = boost::spirit::x3::iso8859_1;

	using iso8859_1::char_;

	struct string_literal_class;

	typedef x3::rule<string_literal_class> string_literal_type;

	string_literal_type const string_literal { "string_literal" };

	auto const string_literal_def =
		x3::lexeme[
			(      '"'
				>> *(  (char_ - '"')
                    | "\"\""
				    )
				>> '"'
			)
		]
		;

	BOOST_SPIRIT_DEFINE(
		string_literal
	);
}


int main()
{
	namespace x3 = boost::spirit::x3;

	std::vector<std::string> const test_cases {
        "\" \"\" cc \"\" \"",		// with ""inner escaped"" quotes
	    "\" \"\"Characters such as $, %, and } are allowed in string literals.\"\" \""
		};

    typedef std::string::const_iterator iterator_type;

    for(auto str: test_cases) {
		iterator_type iter = str.begin();
		iterator_type const end = str.end();

		auto& rule = parser::string_literal;

        std::cout << "parse " << str << ": ";

		bool r = phrase_parse(iter, end, rule, x3::space);

		if (r && iter == end) {
			std::cout << "succeeded\n";
		} else {
			std::cout << "failed\n";
		}
    }

    return 0;
}



