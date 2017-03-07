/*
 * x3_quoted_string.cpp
 *
 *  Created on: 04.03.2017
 *      Author: olaf
 */


#include <boost/spirit/home/x3.hpp>

#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/fusion/include/io.hpp>

#include <iostream>
#include <vector>

// c++14 experimental
#include <experimental/string_view>

namespace boost { namespace spirit { namespace x3 { namespace traits {

template <typename It>
void move_to(It b, It e, std::experimental::string_view& v)
{
	// FixMe: storage is contiguous as a concept check for input range
    v = std::experimental::string_view(&*b, std::size_t(std::distance(b,e)));
}

} } } }

namespace ast
{
	using std_string_view = std::experimental::string_view;

    struct foo
    {
        std_string_view string;
    };

    using boost::fusion::operator<<;
}

BOOST_FUSION_ADAPT_STRUCT(ast::foo,
    string
)


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
	struct integer_class;

	typedef x3::rule<basic_graphic_character_class> basic_graphic_character_type;
	typedef x3::rule<graphic_character_class> graphic_character_type;
	typedef x3::rule<integer_class, ast::foo> string_literal_type;

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
		x3::lexeme[ x3::raw[
			'"' >> ( *(graphic_character - '"') ) >> '"'
		] ]
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
	namespace iso8859_1 = boost::spirit::x3::iso8859_1;

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
		ast::foo foo;

		bool r = phrase_parse(iter, end, rule, iso8859_1::space, foo);

		if (r && iter == end) {
			std::cout << "Parsing succeeded, got "
			          << foo.string << '\n';
		} else {
			std::cout << "Parsing failed\n";
		}
    }

    return 0;
}
