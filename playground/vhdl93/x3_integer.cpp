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

#include <boost/type_index.hpp>

#include <boost/fusion/algorithm/iteration/for_each.hpp>
#include <boost/fusion/include/for_each.hpp>
#include <boost/fusion/container/vector/convert.hpp>
#include <boost/fusion/include/as_vector.hpp>

#include <boost/integer.hpp>

/* -------------------------------------------------------------------------*/
auto print_type_of = [](auto &ctx) {
   std::cout << boost::typeindex::type_id<decltype(ctx)>().pretty_name() << "\n";
};
/* -------------------------------------------------------------------------*/


namespace parser {

   namespace x3 = boost::spirit::x3;

   using x3::char_;

   typedef x3::rule<struct integer_class, uint32_t> integer_type;

   integer_type const integer { "integer" };

   //  warning: ISO C++ forbids use of 'auto' in parameter declaration [-Wpedantic]
   constexpr uint32_t digit_treshold(auto i) {
       return std::numeric_limits<decltype(i)>::max() % 10;
   }

   auto const combine = [](auto &ctx) {
       //typedef decltype(x3::_attr(ctx)) value_type; // =>> templated?
       typedef uint32_t value_type;
       typedef boost::uint_t<sizeof(value_type)*8+1>::fast acc_type;
       acc_type result { 0 };
       uint32_t iter_cnt { 0 };
       for (auto&& ch : x3::_attr(ctx)) {
           switch (ch) {
               case '_': break;
               default:
                   if(iter_cnt > std::numeric_limits<value_type>::digits10) {
                       x3::_pass(ctx) = false;
                       continue;
                   }
                   if(iter_cnt++ <
std::numeric_limits<value_type>::digits10) {
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

namespace parser2 {

   namespace x3 = boost::spirit::x3;

   using x3::char_;

   auto const combine_to_uint = [](auto &ctx) {

       namespace fu = boost::fusion;
       
       // Attr type is fusion::deque<char, std::string<char,...>>
       //std::cout << "Val: " << boost::typeindex::type_id<decltype(x3::_val(ctx))>().pretty_name() << "\n";
       //std::cout << "Attr: " << boost::typeindex::type_id<decltype(x3::_attr(ctx))>().pretty_name() << "\n";

       typedef typename std::decay<decltype(x3::_val(ctx))>::type value_type;
       typedef typename boost::uint_t<sizeof(value_type)*8+1>::fast acc_type;
       
       static_assert(sizeof(value_type) < sizeof(acc_type), "Accumulator to small");
       
       auto as_uint = [](auto ch) { return static_cast<uint>(ch - '0'); };
       
       acc_type acc { as_uint(fu::at_c<0>(x3::_attr(ctx))) };
       
        for (auto&& ch : fu::at_c<1>(x3::_attr(ctx))) { 
            switch (ch) {
                case '_': break;
                default:  acc = acc*10 + as_uint(ch);
            }
            if(acc > std::numeric_limits<value_type>::max()) {
                x3::_pass(ctx) = false;
            }
        }
        
        x3::_val(ctx) = static_cast<value_type>(acc);
   };

   typedef x3::rule<struct _, uint32_t> integer_type;
   integer_type const integer {};
   // Parse '1_000' as 1000
   auto const integer_def = x3::lexeme [
       (char_("0-9") >> *char_("0-9_")) 
    ] [combine_to_uint] ;

   BOOST_SPIRIT_DEFINE(integer)
}

namespace parser3 {

   namespace x3 = boost::spirit::x3;

   using x3::char_;

   auto const combine_to_uint = [](auto &ctx) {

       namespace fu = boost::fusion;

       // Attr: boost::fusion::deque<char, std::vector<boost::variant<boost::detail::variant::over_sequence<boost::mpl::v_item<char,
       // boost::mpl::vector<mpl_::na, mpl_::na, mpl_::na, mpl_::na, mpl_::na, mpl_::na, mpl_::na,
       // mpl_::na, mpl_::na, mpl_::na, mpl_::na, mpl_::na, mpl_::na, mpl_::na, mpl_::na, mpl_::na,
       // mpl_::na, mpl_::na, mpl_::na, mpl_::na>, 0> >>,
       std::cout << "\nVal: " << boost::typeindex::type_id<decltype(x3::_val(ctx))>().pretty_name() << "\n";
       std::cout << "Attr: " << boost::typeindex::type_id<decltype(x3::_attr(ctx))>().pretty_name() << "\n";

       typedef typename std::decay<decltype(x3::_val(ctx))>::type value_type;
       typedef typename boost::uint_t<sizeof(value_type)*8+1>::fast acc_type;

       static_assert(sizeof(value_type) < sizeof(acc_type), "Accumulator to small");

       auto as_uint = [](auto ch) { return static_cast<uint>(ch - '0'); };
#if 0
       acc_type acc { as_uint(fu::at_c<0>(x3::_attr(ctx))) };

        for (auto&& ch : fu::at_c<1>(x3::_attr(ctx))) {
            acc = acc*10 + as_uint(ch);
            if(acc > std::numeric_limits<value_type>::max()) {
                x3::_pass(ctx) = false;
            }
        }

        x3::_val(ctx) = static_cast<value_type>(acc);
#endif
   };

   auto const underline = x3::rule<struct _> { "underline" } = char_('_');

   typedef x3::rule<struct _, uint32_t> integer_type;

   integer_type const integer {};
   // Parse '1_000' as 1000
   auto const integer_def = x3::lexeme [
       char_("0-9") >> *(char_("0-9") | underline)
    ] [combine_to_uint] ;

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
       "_42", 
	   "42_", // shouldn't pass !
       };

   typedef std::string::const_iterator iterator_type;

   for(auto str: test_cases) {
     iterator_type iter = str.begin();
     iterator_type const end = str.end();

     auto& rule = parser2::integer;

     std::cout << "parse `" << str << "´: ";

     uint32_t i;

     bool r = x3::phrase_parse(iter, end, rule, x3::space, i);

     if (r && iter == end) {
       std::cout << "succeeded: \"" << str << "\" -> " << i << "\n";
     } else {
       std::cout << "*** failed ***\n";
     }
   }

   return 0;
}
