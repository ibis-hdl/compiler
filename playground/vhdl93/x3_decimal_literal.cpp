/*
 * decimal_literal.cpp
 *
 *  Created on: 12.03.2017
 *      Author: olaf
 */


#include <iostream>
//#define BOOST_SPIRIT_X3_DEBUG

#include <boost/spirit/home/x3.hpp>
#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/fusion/include/io.hpp>
#include <boost/optional/optional_io.hpp>
#include <boost/range/irange.hpp>

namespace ast {

    using decimal_literal = boost::variant<int32_t, double>;
}

// ------8<----
#include <boost/fusion/algorithm/iteration/for_each.hpp>
#include <boost/fusion/include/for_each.hpp>
#include <boost/type_index.hpp>

namespace x3_utils {

    namespace x3 = boost::spirit::x3;
    namespace fu = boost::fusion;

    struct x3_info {
        x3_info(std::ostream& os = std::cout): os { os } {};
        auto operator()(auto& ctx) {

            auto const attr_info = [&](auto const& attr) {

                typedef decltype(attr) attr_type;

                os << "attr #" << n++ << ": <"
                   << boost::typeindex::type_id<attr_type>().pretty_name() << "> = '"
                   << attr << "'\n";

            };
            os << "\n---8<--- X3 ---8<---\n";
            os << "value <" << boost::typeindex::type_id<decltype(x3::_val(ctx))>().pretty_name() << ">\n";
            fu::for_each(x3::_attr(ctx), attr_info);
            os << "--->8---->8---->8---\n";
        }

        uint  n { 0 };
        std::ostream & os;
    };
}
// --->8----

namespace parser {

   namespace x3 = boost::spirit::x3;
   namespace fu = boost::fusion;

   using x3::char_;

   using x3_utils::x3_info;


   auto const integer = x3::rule<struct integer_class, int> { "integer" } =
       x3::uint_ // in real world more complex
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
       ][combine_exp]
       ;

   auto const as_integer = [](auto& ctx) {
       auto integer =  fu::at_c<0>(x3::_attr(ctx));
       auto exp = fu::at_c<1>(x3::_attr(ctx));
       // Hint: https://stackoverflow.com/questions/2067988/recursive-lambda-functions-in-c11
       auto const pow10 = [](auto n) {
           uint p = 1;
           for(auto i : boost::irange(0, n)) { p *= 10; }
           return p;
       };
       //std::cout << "L: i=" << integer << ", e=" << (exp ? *exp : 0) << "\n";
       if(exp) {
           integer *= pow10(*exp);
       }
       //std::cout << "as_int = " << integer << "\n";
       x3::_val(ctx) = integer;
   };
   auto const as_real = [](auto& ctx) {
       x3::_val(ctx) = 0.0;
   };
   // decimal_literal ::=  integer [ . integer ] [ exponent ]
   auto const decimal_literal = x3::rule<struct based_literal_class, ast::decimal_literal> { "decimal_literal" } =
           x3::lexeme [
                    (integer >> '.' >> integer >> -exponent)[as_real]
                  | (integer >> -exponent)[as_integer]
           ]
           ;
}

int main()
{
   namespace x3 = boost::spirit::x3;

   for(std::string const str: {
           // Integer literals
           "12", "0", "1e6", "123456", // "123_456",
           // Real literals
           "12.0", "0.0", "0.456", "3.1415926", //"3.14159_26",
           // Real literals with exponents
           "1.34E-12", "1.0E+6", "6.02346E+24", //"6.023_46E+2_4",
   }) {
     auto iter = str.begin(), end = str.end();

     ast::decimal_literal attr;
     bool r = x3::phrase_parse(iter, end, parser::decimal_literal, x3::space, attr);

     std::cout << "parse '" << str << "': ";
     if (r && iter == end) {
       std::cout << "succeeded: " << attr << "\n";
     } else {
       std::cout << "*** failed ***\n";
     }
   }

   return 0;
}
