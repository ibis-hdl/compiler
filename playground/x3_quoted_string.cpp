/*
 * x3_quoted_string.cpp
 *
 *  Created on: 04.03.2017
 *      Author: olaf
 */


#include <boost/spirit/home/x3.hpp>
#include <iostream>

namespace parser {

	namespace x3 = boost::spirit::x3;

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
		  x3::upper
		| x3::digit
		| x3::punct // special_character
		| x3::space
		;

	auto const graphic_character_def =
		  basic_graphic_character
		| x3::lower
		| x3::graph // other_special_character
		;

	auto const string_literal_def =
		x3::lexeme[
			'"' >> ( +(graphic_character - '"') ) >> '"'
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

	std::string const input { "\" aa\"" };

    typedef std::string::const_iterator iterator_type;

    iterator_type iter = input.begin();
    iterator_type const end = input.end();

    auto& rule = parser::string_literal;

    bool r = phrase_parse(iter, end, rule, x3::space);

    if (r && iter == end) {
    	std::cout << "Parsing succeeded\n";
    } else {
    	std::cout << "Parsing failed\n";
    }

    return 0;
}

