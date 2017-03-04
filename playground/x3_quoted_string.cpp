/*
 * x3_quoted_string.cpp
 *
 *  Created on: 04.03.2017
 *      Author: olaf
 */


#include <boost/spirit/home/x3.hpp>
#include <iostream>
#include <vector>

namespace parser {

	namespace x3 = boost::spirit::x3;
	namespace iso8859_1 = boost::spirit::x3::iso8859_1;

	using iso8859_1::upper;
	using iso8859_1::lower;
	using iso8859_1::digit;
	using iso8859_1::punct;
	using iso8859_1::space;
	using iso8859_1::graph;

	struct basic_graphic_character_class;
	struct graphic_character_class;
	struct string_literal_class;

	typedef x3::rule<basic_graphic_character_class> basic_graphic_character_type;
	typedef x3::rule<graphic_character_class> graphic_character_type;
	typedef x3::rule<string_literal_class> string_literal_type;

	basic_graphic_character_type const basic_graphic_character { "basic_graphic_character" };
	graphic_character_type const graphic_character { "graphic_character" };
	string_literal_type const string_literal { "string_literal" };

	auto const basic_graphic_character_def =
		  upper
		| digit
		| punct // special_character
		| space
		;

	auto const graphic_character_def =
		  basic_graphic_character
		| lower
		| graph // other_special_character
		;

	auto const string_literal_def =
		x3::lexeme[
			'"' >> ( *(graphic_character - '"') ) >> '"'
		]
		;

	BOOST_SPIRIT_DEFINE(
		basic_graphic_character,
		graphic_character,
		string_literal
	);
}

int main()
{
	namespace x3 = boost::spirit::x3;

	std::vector<std::string> const test_cases {
		"\" aa\"",
		"\"aa \"",
		"\" aa \"",
		"\".\"",
		"\" \"",
		"\"ä\"",
		"\"\""
		};

    typedef std::string::const_iterator iterator_type;

    for(auto str: test_cases) {
		iterator_type iter = str.begin();
		iterator_type const end = str.end();

		auto& rule = parser::string_literal;

		bool r = phrase_parse(iter, end, rule, x3::space);

		if (r && iter == end) {
			std::cout << "Parsing succeeded\n";
		} else {
			std::cout << "Parsing failed\n";
		}
    }

    return 0;
}

/*
LANG=en g++ -std=c++14 ../IBIS_SOURCE/playground/x3_quoted_string.cpp -o x3_quoted_string && ./x3_quoted_string
Parsing succeeded
Parsing succeeded
Parsing succeeded
Parsing succeeded
Parsing succeeded
Parsing succeeded
Parsing failed
 */
