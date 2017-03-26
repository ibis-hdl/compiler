/*
 * x3_extended_identifier.cpp
 *
 *  Created on: 25.03.2017
 *      Author: olaf
 */


#include <iostream>
#define BOOST_SPIRIT_X3_DEBUG_OUT std::cout
//#define BOOST_SPIRIT_X3_DEBUG

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

   auto const extended_identifier_chars = x3::rule<struct _, std::string> { "extended_identifier (chars)" } =
        +( char_ - char_('\\') )
        ;

   auto const extended_identifier_atom = x3::rule<struct _, std::string> { "extended_identifier (atom)" } =
		lexeme [
			   char_('\\')
			>> extended_identifier_chars
			>> char_('\\')
		]
		;

   auto const extended_identifier = x3::rule<struct _, std::string> { "extended_identifier" } =
		lexeme [
			    extended_identifier_atom
			>> *(extended_identifier_atom % (char_('\\') >> char_('\\')))
		]
		;

   auto const identifier = x3::rule<struct _, std::string> { "identifier" } =
   		basic_identifier | extended_identifier
   		;
}


int main()
{
   namespace x3 = boost::spirit::x3;

   for(std::string const str: {
	   "\\BoBus\\",				// expected '\Bus\'
	   "\\Foo\\\\oh\\", 		// expected '\Foo\\oh\'
	   "\\Foo\\\\Bar\\\\Baz\\", // expected '\Foo\\Bar\\Baz\'
	   "VHDL"
    })
    {
	 auto iter = str.begin(), end = str.end();

	 std::string attr;

	 std::cout << "parse `" << str << "`:\n";

	 bool r = x3::phrase_parse(iter, end, parser::identifier, x3::space, attr);

	 if (r && iter == end) {
	   std::cout << "succeeded: \'" << attr << "\'\n";
	   std::cout << '\n';
	 } else {
	   std::cout << "*** failed ***\n";
	 }
   }

   return 0;
}

