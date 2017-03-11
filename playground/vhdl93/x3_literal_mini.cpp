#include <iostream>
//#define BOOST_SPIRIT_X3_DEBUG

#include <boost/spirit/home/x3.hpp>
#include <boost/optional/optional_io.hpp>
#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/fusion/include/io.hpp>


namespace ast {

    struct literal {
        int32_t                     base;
        std::string                 a_part;
        boost::optional<std::string> b_part;
        int32_t                     exponent;
    };

    using boost::fusion::operator<<;
}

BOOST_FUSION_ADAPT_STRUCT(
    ast::literal,
    (int32_t,                      base)
    (std::string,                  a_part)
    (boost::optional<std::string>, b_part)
    (int32_t,                      exponent)
)

namespace parser {

   namespace x3 = boost::spirit::x3;
   namespace fu = boost::fusion;

   using x3::char_;

   auto const part = x3::rule<struct based_integer_class, std::string> { "part" } =
           x3::lexeme[ +char_("0-9") ]
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
           (x3::lexeme [
                      (x3::lit("E") | "e") >> signum >> x3::int_
           ][combine_exp]
           | x3::attr(1)) // doesn't work???
           ;

   auto const literal = x3::rule<struct _, std::string> { "literal" } =
           x3::lexeme [
                  // int             string   optional<string>        int
                  x3::int_ >> '#' >> part >> -('.' >> part) >> '#' >> exponent
           ]
           ;
}


int main()
{
   namespace x3 = boost::spirit::x3;

   typedef std::string::const_iterator iterator_type;

   std::vector<std::string> const test_cases {
       "4711#11111111.32#e42",
       "4711#11111111.32#E-65",
       "4711#11112222#", // why is attr<3> = 0, expected = 1 ???
       };

   for(auto str: test_cases) {
     iterator_type iter = str.begin();
     iterator_type const end = str.end();

     auto& rule = parser::literal;
     ast::literal attr;

     std::cout << "parse `" << str << ": ";

     bool r = x3::phrase_parse(iter, end, rule, x3::space /*, attr */);

     if (r && iter == end) {
       std::cout << "succeeded:\n";

       std::cout << '\n';
     } else {
       std::cout << "*** failed ***\n";
     }
   }

   return 0;
}

