#include <iostream>
//#define BOOST_SPIRIT_X3_DEBUG

#include <boost/spirit/home/x3.hpp>
#include <boost/optional/optional_io.hpp>
#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/fusion/include/io.hpp>

#include <boost/type_index.hpp>

#include <boost/integer.hpp>

#include <algorithm>
#include <iterator>

/* AST */
#include <experimental/optional>

/* hot fix for C++17 */
namespace stdx {
    template<class T>
    using optional = ::std::experimental::optional<T>;
}

namespace ast {

    struct based_integer {
        int32_t                     base;
        std::string                 integer_part;
        stdx::optional<std::string> fractional_part;
        int32_t                     exponent;
    };

    using boost::fusion::operator<<;
}

BOOST_FUSION_ADAPT_STRUCT(
    ast::based_integer,
    (int32_t, base)
    (std::string, integer_part)
    (boost::optional<std::string>, fractional_part)
    (int32_t, exponent)
)

// ------8<----
#include <boost/fusion/algorithm/iteration/for_each.hpp>
#include <boost/fusion/include/for_each.hpp>

namespace x3_utils {

    namespace x3 = boost::spirit::x3;
    namespace fu = boost::fusion;

    struct x3_info {
        auto operator()(auto& ctx) {

            auto const attr_info = [&n = this->n](auto const& attr) {

                typedef decltype(attr) attr_type;

                std::cout << "attr #" << n++ << ": <"
                          << boost::typeindex::type_id<attr_type>().pretty_name() << "> = '"
                          << attr << "'\n";

            };
            std::cout << "\n---8<------8<---\n";
            std::cout << "value <" << boost::typeindex::type_id<decltype(x3::_val(ctx))>().pretty_name() << ">\n";
            fu::for_each(x3::_attr(ctx), attr_info);
            std::cout << "\n--->8------>8---\n";
        }

        uint  n { 0 };
    };
}
// --->8----

namespace parser {

   namespace x3 = boost::spirit::x3;
   namespace fu = boost::fusion;

   using x3::char_;

   using x3_utils::x3_info;

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

   auto const based_literal_helper = [](auto& ctx) {
   };
   auto const based_literal = x3::rule<struct _, std::string> { "based_literal" } =
           x3::lexeme [
                  base >> '#' >> based_integer >> -('.' >> based_integer) >> '#' >> (exponent | x3::attr(1))
           ] [x3_info()]//[based_literal_helper]
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
           "4711#1111_1111.32#",
           "4711#1111_1111.32#E65",
           "42#AA_FF_FF_EE#e42"
           };

       for(auto str: test_cases) {
         iterator_type iter = str.begin();
         iterator_type const end = str.end();

         auto& rule = parser::based_literal;
         ast::based_integer attr;

         std::cout << "parse `" << str << ": ";

         bool r = x3::phrase_parse(iter, end, rule, x3::space);

         if (r && iter == end) {
           std::cout << "succeeded:\n";

           std::cout << '\n';
         } else {
           std::cout << "*** failed ***\n";
         }
       }
   }

   return 0;
}

