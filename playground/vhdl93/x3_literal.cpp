/*
 * x3_literal.cpp
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
   using x3::char_;
   using x3::lit;

   auto const integer = x3::rule<struct _, std::string> { "integer" } =
        char_("0-9") >> *char_("0-9")
        ;

   auto const based_literal = x3::rule<struct _, std::string> { "based_literal" } =
       lexeme [
           integer >> char_('#') >> integer >> -(char_('.') >> integer) >> char_('#') >> -integer
       ]
       ;

   auto const decimal_literal = x3::rule<struct _, std::string> { "decimal_literal" } =
       lexeme [
           integer >> -(char_('.') >> integer) >> -(char_("eE") >> integer)
       ]
       ;

   auto const abstract_literal = x3::rule<struct _, std::string> { "abstract_literal" } =
         based_literal
       | decimal_literal
       ;

   auto const basic_identifier = x3::rule<struct _, std::string> { "basic_identifier" } =
          char_("A-Za-z")
       >> ~char_('"') // reject bit_string_literal
       >> *( -char_("_") >> char_("A-Za-z0-9") )
       ;

   auto const extended_identifier = x3::rule<struct _, std::string> { "extended_identifier" } =
       '\\' >> char_("A-Za-z0-9") >> *char_("A-Za-z0-9_") >> '\\'
       ;

   auto const identifier = x3::rule<struct _, std::string> { "identifier" } =
       basic_identifier | extended_identifier
       ;

   auto const character_literal = x3::rule<struct _, std::string> { "character_literal" } =
       lit("\'") >> ( char_ - char_("\'") ) >> lit("\'")
       ;

   auto const enumeration_literal = x3::rule<struct _, std::string> { "enumeration_literal" } =
         identifier
       | character_literal
       ;

   auto const physical_literal = x3::rule<struct _, std::string> { "physical_literal" } =
       -abstract_literal >> +char_("A-Za-z")
       ;

   auto const numeric_literal = x3::rule<struct _, std::string> { "numeric_literal" } =
         physical_literal
       | abstract_literal
       ;

   auto const string_literal = x3::rule<struct _, std::string> { "string_literal" } =
       lexeme [
           '"' >> *(char_ - '"') >> '"'
       ]
       ;

   auto const bit_string_literal = x3::rule<struct _, std::string> { "bit_string_literal" } =
       lexeme[
           char_("HBO") >> lit('"') >> +char_("0-9a-fA-F") >> lit('"')
       ]
       ;

   auto const literal = x3::rule<struct _, std::string> { "literal" } =
    enumeration_literal
       | string_literal
       | bit_string_literal
       | numeric_literal
       | "NULL"
       ;

}


int main()
{
   namespace x3 = boost::spirit::x3;

   typedef std::string::const_iterator iterator_type;

   std::vector<std::string> const test_cases {
       // enumeration_literal/identifier/basic_identifier
       "Bar",
       "X",
       "X2",
       // enumeration_literal/identifier/extended_identifier
       "\\Foo\\",
       // enumeration_literal/character_literal
       "'A'",
       // string_literal
       "\"FooBar\"",
       // bit_string_literal
       "B\"1111\"",
       // numeric_literal/physical_literal
       "42 fs",
       // numeric_literal/physical_literal
       // ATTENTION: This is a special case for 'literal' since it can't be
       //       distinct from basic_identifier without context !!
       //"ps",
       // numeric_literal/abstract_literal/based_literal
       "8#42#",
       "16#42#4",
       // numeric_literal/abstract_literal/decimal_literal
       "42",
       "42e6",
       // NULL
       "NULL"
       };

   for(auto str: test_cases) {
     iterator_type iter = str.begin();
     iterator_type const end = str.end();

     auto& rule = parser::literal;
     std::string attr;

     std::cout << "parse `" << str << "`:\n";

     bool r = x3::phrase_parse(iter, end, rule, x3::space, attr);

     if (r && iter == end) {
       std::cout << "SUCCEEDED: '" << attr << "'\n\n";
     } else {
       std::cout << "*** FAILED ***\n";
     }
     std::cout << "-----------------------------------------------------------\n";
   }

   return 0;
}

