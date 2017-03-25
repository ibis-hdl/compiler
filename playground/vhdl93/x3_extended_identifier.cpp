/*
 * x3_extended_identifier.cpp
 *
 *  Created on: 25.03.2017
 *      Author: olaf
 */


#include <iostream>
#define BOOST_SPIRIT_X3_DEBUG_OUT std::cout
#define BOOST_SPIRIT_X3_DEBUG

#include <boost/spirit/home/x3.hpp>


namespace parser {

   namespace x3 = boost::spirit::x3;
   using x3::lexeme;
   using x3::int_;
   using x3::char_;
   using x3::lit;

   auto const basic_identifier = x3::rule<struct _, std::string> { "basic_identifier" } =
		char_("A-Za-z") >> *( -lit("_") >> +char_("A-Za-z0-9") )
		;

   auto const extended_identifier = x3::rule<struct _, std::string> { "extended_identifier" } =
		lexeme [
			   '\\'
			>> ( ( char_ >> *( char_ - char_('\\') ) )
			   | ( char_('\\') >> char_('\\'))
			   )
			>> '\\'
		]
		;

   auto const identifier = x3::rule<struct _, std::string> { "identifier" } =
   		basic_identifier | extended_identifier
   		;
}

int main()
{
   namespace x3 = boost::spirit::x3;

   typedef std::string::const_iterator iterator_type;

   std::vector<std::string> const test_cases {
	   "\\Bus\\",
	   "\\Foo\\\\oh\\",
	   //"VHDL"
	   };

   for(auto str: test_cases) {
	 iterator_type iter = str.begin();
	 iterator_type const end = str.end();

	 auto& rule = parser::extended_identifier;
	 std::string attr;

	 std::cout << "parse `" << str << "`:\n";

	 bool r = x3::phrase_parse(iter, end, rule, x3::space, attr);

	 if (r && iter == end) {
	   std::cout << "succeeded: \"" << attr << "\"\n";
	   std::cout << '\n';
	 } else {
	   std::cout << "*** failed ***\n";
	 }
   }

   return 0;
}



