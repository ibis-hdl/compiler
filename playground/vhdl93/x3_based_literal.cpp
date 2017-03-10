#include <iosfwd>
//#define BOOST_SPIRIT_X3_DEBUG

#include <boost/spirit/home/x3.hpp>

#include <iostream>

#include <boost/type_index.hpp>

#include <boost/fusion/algorithm/iteration/for_each.hpp>
#include <boost/fusion/include/for_each.hpp>

#include <boost/integer.hpp>

/* -------------------------------------------------------------------------*/
auto print_type_of = [](auto &ctx) {
   std::cout << boost::typeindex::type_id<decltype(ctx)>().pretty_name() << "\n";
};
/* -------------------------------------------------------------------------*/


namespace parser2 {

   namespace x3 = boost::spirit::x3;

   using x3::char_;

   auto const show_me = [](auto &ctx) {

       namespace fu = boost::fusion;
       
       // Attr type is fusion::deque<char, std::string<char,...>>
       std::cout << "Val: " << boost::typeindex::type_id<decltype(x3::_val(ctx))>().pretty_name() << "\n";
       std::cout << "Attr: " << boost::typeindex::type_id<decltype(x3::_attr(ctx))>().pretty_name() << "\n";

        
        //x3::_val(ctx) = static_cast<value_type>(acc);
   };

   typedef x3::rule<struct _, x3::unused_type> based_literal_type;
   based_literal_type const based_literal {};
    // based_literal ::=
	// base # based_literal [ . based_literal ] # [ exponent ]

   auto const based_literal_def = x3::lexeme [
       //(+x3::uint_ > '#'  > +x3::uint_ ) >> -( '.' > +x3::uint_) > '#' >> -x3::uint_
       +x3::uint_ >> '#' >> +x3::uint_  >>  '.'// >> +x3::uint_ //>> '#' >> -x3::uint_
    ] [show_me] ;
;
   BOOST_SPIRIT_DEFINE(based_literal)
}

int main()
{
   namespace x3 = boost::spirit::x3;

   std::vector<std::string> const test_cases {
       "2#1111_1111#",
       "16#FF#",
       "016#0FF#",
       };

   typedef std::string::const_iterator iterator_type;

   for(auto str: test_cases) {
     iterator_type iter = str.begin();
     iterator_type const end = str.end();

     auto& rule = parser2::based_literal;

    // std::cout << "parse `" << str << "´: ";

     bool r = x3::phrase_parse(iter, end, rule, x3::space);

     if (r && iter == end) {
       std::cout << "succeeded: \"" << str << "\n";
     } else {
       //::cout << "*** failed ***\n";
     }
   }

   return 0;
}
