#if 0 // problem rule separated for NG
#include <iostream>
//#define BOOST_SPIRIT_X3_DEBUG

#include <boost/spirit/home/x3.hpp>

int main()
{
   namespace x3 = boost::spirit::x3;
   using x3::char_;

   auto const integer =  x3::rule<struct _, std::string>{} =
       x3::lexeme[ +char_("0-9") >> *(char_("0-9") | "_") ]; // XXX This inserts a 0x00 for '_'

   for(std::string const str: {
           "4711", "123_456"
   }) {
     auto iter = str.begin(), end = str.end();

     std::string attr;
     bool r = x3::phrase_parse(iter, end, integer, x3::space, attr);

     std::cout << "parse '" << str << "': ";
     if (r && iter == end) {
       std::cout << "succeeded: '" << attr << "'\n";
       if(attr.find('\0') != std::string::npos) {
           std::cout << "found '\\0'\n";
       }
     } else {
       std::cout << "*** failed ***\n";
     }
   }

   return 0;
}
#endif

#include <iostream>
//#define BOOST_SPIRIT_X3_DEBUG

#include <boost/spirit/home/x3.hpp>
#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/fusion/include/io.hpp>

namespace parser {

   namespace x3 = boost::spirit::x3;

   using x3::char_;

   template<typename T>
   auto as_rule = [](auto p) { return x3::rule<struct _, T>{} = x3::as_parser(p); };

   auto const integer = as_rule<std::string>(
       //x3::lexeme[ +char_("0-9") >> *(char_("0-9") | "_") ]); // XXX This inserts a 0x00 for '_'
       x3::lexeme[ +char_("0-9") >> *(-x3::lit("_") >> char_("0-9")) ]; // solution
   auto const exponent = as_rule<std::string>(
       x3::lexeme [ char_("Ee") >> -char_("+-") >> integer ]);

   auto const decimal_literal_real = as_rule<std::string>(
       x3::lexeme [ (integer >> char_('.') >> integer >> -exponent) ]);

   auto const decimal_literal_int = as_rule<std::string>(
       x3::lexeme [ (integer >> -exponent) ]);

   auto const decimal_literal = as_rule<std::string>(
       x3::lexeme [
                decimal_literal_real // not shown tag::real
              | decimal_literal_int  // not shown tag::integer
       ]);
}

int main()
{
   namespace x3 = boost::spirit::x3;

   for(std::string const str: {
           "4711", "123_456", "3.14159_26", "6.023_46E+2_4"
   }) {
     auto iter = str.begin(), end = str.end();

     std::string attr;
     bool r = x3::phrase_parse(iter, end, parser::decimal_literal, x3::space, attr);

     std::cout << "parse '" << str << "': ";
     if (r && iter == end) {
       std::cout << "succeeded: '" << attr << "'\n";
       if(attr.find('\0') != std::string::npos) {
           std::cout << "found '\\0'\n";
       }
     } else {
       std::cout << "*** failed ***\n";
     }
   }

   return 0;
}
