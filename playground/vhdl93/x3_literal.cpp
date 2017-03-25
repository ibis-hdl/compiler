/*
 * x3_literal.cpp
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

   auto const based_literal = x3::rule<struct _> { "based_literal" } =
       lexeme [
              int_ >> '#' >> int_ >> -(lit('.') >> int_) >> '#' >> -int_
       ]
       ;

   auto const decimal_literal = x3::rule<struct _> { "decimal_literal" } =
       lexeme [
              int_ >> -(lit('.') >> int_) >> '#' >> -int_
       ]
       ;

   auto const abstract_literal = x3::rule<struct _> { "abstract_literal" } =
		  based_literal
		| decimal_literal
		;

   auto const basic_identifier = x3::rule<struct _> { "basic_identifier" } =
		char_("A-Za-z") >> *( -lit("_") >> +char_("A-Za-z0-9") )
		;

   auto const extended_identifier = x3::rule<struct _> { "extended_identifier" } =
		'\\' >> char_("A-Za-z0-9") >> *char_("A-Za-z0-9_") >> '\\'
		;

   auto const identifier = x3::rule<struct _> { "identifier" } =
   		basic_identifier | extended_identifier
   		;

   auto const character_literal = x3::rule<struct _> { "character_literal" } =
		lit("\'") >> ( char_ - char_("\'") ) >> lit("\'")
        ;

   auto const enumeration_literal = x3::rule<struct _> { "enumeration_literal" } =
         identifier
       | character_literal
       ;

   auto const physical_literal = x3::rule<struct _> { "physical_literal" } =
       -abstract_literal >> +char_("A-Za-z")
       ;

   auto const numeric_literal = x3::rule<struct _> { "numeric_literal" } =
         physical_literal
       | abstract_literal
       ;

   auto const string_literal = x3::rule<struct _> { "string_literal" } =
	   lexeme [
			'"' >> (char_ - '"') >> '"'
	   ]
	   ;

   auto const bit_string_literal = x3::rule<struct _> { "bit_string_literal" } =
		lexeme[
			  char_("HBO") >> lit("\"") >> +char_("0-9a-fA-F") >> lit('"')
		]
		;

   auto const literal = x3::rule<struct _> { "literal" } =
         numeric_literal
       | enumeration_literal
       | string_literal
       | bit_string_literal
       | "NULL"
       ;

}


int main()
{
   namespace x3 = boost::spirit::x3;

   typedef std::string::const_iterator iterator_type;

   std::vector<std::string> const test_cases {
	   //"foobar"
	   //"B\"1111_1111_1111\""
	   "'A'"
	   };

   for(auto str: test_cases) {
	 iterator_type iter = str.begin();
	 iterator_type const end = str.end();

	 auto& rule = parser::character_literal;

	 std::cout << "parse `" << str << "`:\n";

	 bool r = x3::phrase_parse(iter, end, rule, x3::space);

	 if (r && iter == end) {
	   std::cout << "succeeded\n";
	   std::cout << '\n';
	 } else {
	   std::cout << "*** failed ***\n";
	 }
   }

   return 0;
}

