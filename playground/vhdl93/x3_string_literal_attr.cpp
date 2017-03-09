/*
 * x3_string_literal.cpp
 *
 *  Created on: 04.03.2017
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

	using iso8859_1::char_;

	struct basic_graphic_character_class;
	struct graphic_character_class;
	struct integer_class;

	typedef x3::rule<basic_graphic_character_class, char> basic_graphic_character_type;
	typedef x3::rule<graphic_character_class, char> graphic_character_type;
	typedef x3::rule<integer_class, std::string> string_literal_type;

	basic_graphic_character_type const basic_graphic_character { "basic_graphic_character" };
	graphic_character_type const graphic_character { "graphic_character" };
	string_literal_type const string_literal { "string_literal" };

	// helper
	struct upper_case_letter_class;
	struct digit_class;
	struct special_character_class;
	struct space_character_class;
	struct format_effector_class;
	struct end_of_line_class;
	struct lower_case_letter_class;
	struct other_special_character_class;

	typedef x3::rule<upper_case_letter_class, char> upper_case_letter_type;
	typedef x3::rule<digit_class, char> digit_type;
	typedef x3::rule<special_character_class, char> special_character_type;
	typedef x3::rule<space_character_class, char> space_character_type;
	typedef x3::rule<format_effector_class> format_effector_type;
	typedef x3::rule<end_of_line_class> end_of_line_type;
	typedef x3::rule<lower_case_letter_class, char> lower_case_letter_type;
	typedef x3::rule<other_special_character_class, char> other_special_character_type;

	upper_case_letter_type const upper_case_letter { "upper_case_letter" };
	digit_type const digit { "digit" };
	special_character_type const special_character { "special_character" };
	space_character_type const space_character { "space_character" };
	format_effector_type const format_effector { "format_effector" };
	end_of_line_type const end_of_line { "end_of_line" };
	lower_case_letter_type const lower_case_letter { "lower_case_letter" };
	other_special_character_type const other_special_character { "other_special_character" };

	auto const upper_case_letter_def = char_("ABCDEFGHIJKLMNOPQRSTUVWXYZÀÁÂÃÄÅÆÇÈÉÊËÌÍÎÏÐÑÒÓÔÕÖØÙÚÛÜÝÞ");
	auto const lower_case_letter_def = char_("abcdefghijklmnopqrstuvwxyzßàáâãäåæçèéêëìíîïðñòóôõöøùúûüýþÿ");
	auto const digit_def = char_("0-9");
	auto const special_character_def = char_("\"#&'()*+,-./:;<=>[]_|");
	auto const other_special_character_def = char_("!$%?@\\^`{}~¡¢£¤¥¦§¨©ª«¬­®¯°±²³´µ¶·¸¹º»¼½¾¿×÷");

	auto const space_character_def = iso8859_1::space;
	auto const format_effector_def = char_("\t\n\v\r\f");
	auto const end_of_line_def = x3::eol;

	BOOST_SPIRIT_DEFINE(
		upper_case_letter,
		digit,
		special_character,
		space_character,
		format_effector,
		end_of_line,
		lower_case_letter,
		other_special_character
	)

	auto const basic_graphic_character_def =
		  upper_case_letter
		| digit
		| special_character
		| space_character
		;

	auto const graphic_character_def =
		  basic_graphic_character
		| lower_case_letter
		| other_special_character
		;

	/* From Lexer (Thomas Dettmer) VHDL Archive:
	 *
	 * (\"({graphic_character}|(\"\")|\%)*\")|(\%({graphic_character}|(\%\%)|\")*\%) {
	 *		ECHO; return ( t_StringLit );
	 *
	 *   ( " ( {graphic_character}
     *       | ("")
     *       | %
     *       )*
     *     "
     *   )
     * | ( % ( {graphic_character}
     *       | (%%)
     *       | "
     *       )*
     *     %
     *   )
	 *
	 * Note, other_special_character doesn't contain '%' !
	 */
    // string_literal ::=  " { graphic_character } "
	auto const string_literal_def =
        x3::lexeme[
            (      '"'
                >> *( (graphic_character - '"')
                    | x3::no_skip[char_('"') >> char_('"')]
                    )
                >> '"'
            )
            |
            (      '%' // LRM Chapter 13.10
                >> *( (graphic_character - '%')
                    | x3::no_skip[char_('%') >> char_('%')]
                    )
                >> '%'
            )
        ]
		;

	BOOST_SPIRIT_DEFINE(
		basic_graphic_character,
		graphic_character,
		string_literal
	)
}

int main()
{
	namespace x3 = boost::spirit::x3;

	std::vector<std::string> const test_cases {
		"\"Both S and Q equal to 1\"",
		"\"Characters such as $, %, and } are allowed in string literals.\"",
		"\"& ' ( ) * + , - . / : ; < = > | [ ]\"",
		"\"Quotation: \"\"REPORT...\"\" is also allowed\"",
		"%see \"LRM 13.10\", it's legal VHDL%",
		"%Quotation: %%REPORT...%% is also allowed%",
		// has to fail
		"\"Both S and Q equal to 1",
		};

    typedef std::string::const_iterator iterator_type;

    for(auto str: test_cases) {
		iterator_type iter = str.begin();
		iterator_type const end = str.end();

		//auto& rule = parser::graphic_character;
		auto& rule = parser::string_literal;
        std::string s;
        
		std::cout << "parse [" << str << "]: ";

		bool r = phrase_parse(iter, end, rule, x3::space, s);

		if (r && iter == end) {
			std::cout << "Parsing succeeded: " << s << "\n";
		} else {
			std::cout << "*** Parsing failed ***\n";
		}
    }

    return 0;
}
