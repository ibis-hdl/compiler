#include <iostream>
//#define BOOST_SPIRIT_X3_DEBUG

#include <boost/spirit/home/x3.hpp>
#include <boost/optional/optional_io.hpp>
#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/fusion/include/io.hpp>

#include <boost/type_index.hpp>

#include <boost/fusion/algorithm/iteration/for_each.hpp>
#include <boost/fusion/include/for_each.hpp>

#include <boost/integer.hpp>

#include <algorithm>
#include <iterator>


namespace ast {

    struct based_integer {
        char    extended_digit;
    };

    using boost::fusion::operator<<;
}

namespace parser {

   namespace x3 = boost::spirit::x3;
   namespace fu = boost::fusion;

   using x3::char_;

   auto const show_me = [](auto &ctx) {

       namespace fu = boost::fusion;
       
       /*
        * Val: std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >
        * Attr: boost::fusion::deque<char, std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > >
        */
       std::cout << "\nVal: " << boost::typeindex::type_id<decltype(x3::_val(ctx))>().pretty_name() << "\n";
       std::cout << "Attr: " << boost::typeindex::type_id<decltype(x3::_attr(ctx))>().pretty_name() << "\n";

       auto const inner_attr = [](auto& i) {
           std::cout << "InnerAttr: " << boost::typeindex::type_id<i>().pretty_name() << "\n";
       };

       //fu::for_each(x3::_attr(ctx), inner_attr);
        //x3::_val(ctx) = static_cast<value_type>(acc);
   };

   auto const integer = x3::rule<struct integer_class, uint> { "integer" } =
           x3::uint_
           ;

   auto const base = x3::rule<struct base_class, uint> { "base" } =
           integer
           ;

   auto const extended_digit = x3::rule<struct extended_digit_class, char> { "extended_digit" } =
           char_("0-9") | char_("A-Fa-f")
           ;

   auto const underline = x3::rule<struct underline_class> { "underline" } = char_('_');
   auto const based_integer = x3::rule<struct based_integer_class, std::string> { "based_integer" } =
           x3::lexeme[
                  extended_digit >> *( -x3::lit('_') >> extended_digit )
           ] //[ show_me]
           ;

   auto signum_pos = [](auto& ctx) { x3::_val(ctx) = false; };
   auto signum_neg = [](auto& ctx) { x3::_val(ctx) = true;  };
   auto const signum = x3::rule<struct signum_class, bool> { "signum" } =
             x3::lit('+')[ signum_pos ]
           | x3::lit('-')[ signum_neg ]
           | x3::eps[ signum_pos]
           ;

   auto combine_exp = [](auto& ctx) {
       x3::_val(ctx) = fu::at_c<0>(x3::_attr(ctx)) ? -fu::at_c<1>(x3::_attr(ctx)) : fu::at_c<1>(x3::_attr(ctx));
   };
   auto const exponent = x3::rule<struct exponent_class, int32_t> { "exponent" } =
           x3::lexeme [
                   (x3::lit("E") | "e") >> signum >> integer
           ] [combine_exp]
           ;

   auto const based_literal = x3::rule<struct _, std::string> {} =
           x3::lexeme [

                  base >> '#' >> based_integer /* .... */ >> '#' >> exponent
           ]// [show_me]
           ;
}


int main()
{
   namespace x3 = boost::spirit::x3;

   typedef std::string::const_iterator iterator_type;


   {
       std::vector<std::string> const test_cases {
           "E3",
           "e42",
           "E2147483647",  // INT_MAX
           "E+2147483647", // INT_MAX
           "E-2147483648", // INT_MIN
           "E-0",
           };

       for(auto str: test_cases) {
         iterator_type iter = str.begin();
         iterator_type const end = str.end();

         auto& rule = parser::exponent;
         int32_t attr;

         std::cout << "parse `" << str << ": ";

         bool r = x3::phrase_parse(iter, end, rule, x3::space, attr);

         if (r && iter == end) {
           std::cout << "succeeded: " << attr;
           std::cout << '\n';
         } else {
           std::cout << "*** failed ***\n";
         }
       }
   }
   {
       std::vector<std::string> const test_cases {
           " 1111_1111 ",
           " AA_FF_FF_EE"
           };

       for(auto str: test_cases) {
         iterator_type iter = str.begin();
         iterator_type const end = str.end();

         auto& rule = parser::based_integer;
         std::string attr;

         std::cout << "parse `" << str << ": ";

         bool r = x3::phrase_parse(iter, end, rule, x3::space, attr);

         if (r && iter == end) {
           std::cout << "succeeded:\n";
           std::copy(attr.begin(), attr.end(), std::ostream_iterator<boost::optional<char>>(std::cout, ", "));
           std::cout << '\n';
         } else {
           std::cout << "*** failed ***\n";
         }
       }
   }
   {
       std::vector<std::string> const test_cases {
           " 4711#1111_1111#E65 ",
           " 42#AA_FF_FF_EE#e42"
           };

       for(auto str: test_cases) {
         iterator_type iter = str.begin();
         iterator_type const end = str.end();

         auto& rule = parser::based_literal;
         std::string attr;

         std::cout << "parse `" << str << ": ";

         bool r = x3::phrase_parse(iter, end, rule, x3::space, attr);

         if (r && iter == end) {
           std::cout << "succeeded:\n";
           std::copy(attr.begin(), attr.end(), std::ostream_iterator<boost::optional<char>>(std::cout, ", "));
           std::cout << '\n';
         } else {
           std::cout << "*** failed ***\n";
         }
       }
   }

   return 0;
}

