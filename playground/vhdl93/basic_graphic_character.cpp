/*
 * basic_graphic_character.cpp
 *
 *  Created on: 05.03.2017
 *      Author: olaf
 */

#include <iosfwd>
//#define BOOST_SPIRIT_X3_DEBUG

#include <boost/spirit/home/x3.hpp>
#include <iostream>
#include <vector>

/*
 * http://rti.etf.bg.ac.rs/rti/ri5rvl/tutorial/TUTORIAL/IEEE/HTML/1076_13.HTM#13.6
 */
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

	typedef x3::rule<basic_graphic_character_class> basic_graphic_character_type;

	basic_graphic_character_type const basic_graphic_character { "basic_graphic_character" };

	auto const basic_graphic_character_def =
		  upper
		| digit
		| punct // special_character
		| space
		;


	BOOST_SPIRIT_DEFINE(
		basic_graphic_character
	);
}

int main()
{
	namespace x3 = boost::spirit::x3;

	// 13.1 Character set
	std::vector<std::string> const test_cases {
		// Uppercase letters
		"A B C D E F G H I J K L M N O P Q R S T U V W X Y Z А Б В Ã Д Е Ж З И Й К Л М Н О П С Т У Ô Õ Ц Ø Щ Ъ Ы Ь Ý Þ",
		" ",
		" ",
		};

    typedef std::string::const_iterator iterator_type;

    for(auto str: test_cases) {
		iterator_type iter = str.begin();
		iterator_type const end = str.end();

		auto& rule = parser::string_literal;

                std::cout << "parse \"" << str << "\"\n";

		bool r = phrase_parse(iter, end, rule, x3::space);

		if (r && iter == end) {
			std::cout << "Parsing succeeded\n";
		} else {
			std::cout << "Parsing failed\n";
		}
    }

    return 0;
}



