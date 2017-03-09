/*
 * x3_integer.cpp
 *
 *  Created on: 06.03.2017
 *      Author: olaf
 */

#include <iosfwd>
//#define BOOST_SPIRIT_X3_DEBUG

#include <boost/spirit/home/x3.hpp>

#include <iostream>


namespace parser {

   namespace x3 = boost::spirit::x3;

   using x3::char_;

   typedef x3::rule<struct integer_class, uint32_t> integer_type;

   integer_type const integer { "integer" };

   constexpr uint32_t digit_treshold(auto i) {
       return std::numeric_limits<decltype(i)>::max() % 10;
   }

   auto const combine = [](auto &ctx) {
       //typedef decltype(x3::_attr(ctx)) base_type; // =>> templated?
       typedef uint32_t base_type;
       base_type result { 0 };
       uint32_t iter_cnt { 0 };
       for (auto&& ch : x3::_attr(ctx)) {
           switch (ch) {
               case '_': break;
               default:
                   if(iter_cnt > std::numeric_limits<base_type>::digits10) {
                       x3::_pass(ctx) = false;
                       continue;
                   }
                   if(iter_cnt++ <
std::numeric_limits<base_type>::digits10) {
                       result = result*10 + (ch - '0');
                   }
                   else {
#if 0
                       switch(ch - '0') {
                       case 0: // [[fallthrough]]
                       case 1: // [[fallthrough]]
                       case 2: // [[fallthrough]]
                       case 3: // [[fallthrough]]
                       case 4: // [[fallthrough]]
                       case 5:
                           result = result*10 + (ch - '0');
                           break;
                       default:
                           x3::_pass(ctx) = false;
                       }
#else
                       if((unsigned)(ch - '0') > digit_treshold(result)) {
                          x3::_pass(ctx) = false;
                       }
                       else {
                          result = result*10 + (ch - '0');
                       }
#endif
                   }
           }
       }

       x3::_val(ctx) = result;
   };

   // Parse '1_000' as 1000
   auto const integer_def =
     //x3::lexeme [ char_("0-9") >> *(char_("0-9_")) ] [combine] /* _val(ctx) => uint */
     x3::lexeme [ +char_("0-9_") ] [combine]
     ;

   BOOST_SPIRIT_DEFINE(integer)
}


int main()
{
   namespace x3 = boost::spirit::x3;

   std::vector<std::string> const test_cases {
       "0",
       "1",
       "01",
       "1_000",
       "42_666_4711",
       "4_294_967_295", // uint32::max
       // below must fail to parse
       "4_294_967_296",
       "4_294_967_295_0",
       "4_294_967_295_00",
       "_42", "42_",
       " 4 2 ", "4 _2"
       };

   typedef std::string::const_iterator iterator_type;

   for(auto str: test_cases) {
     iterator_type iter = str.begin();
     iterator_type const end = str.end();

     auto& rule = parser::integer;

     std::cout << "parse `" << str << "Â´:\n";

     uint32_t i;

     bool r = x3::phrase_parse(iter, end, rule, x3::space, i);

     if (r && iter == end) {
       std::cout << "succeeded: \"" << str << "\" -> " << i << "\n";
     } else {
       std::cout << "failed\n";
     }
   }

   return 0;
}
