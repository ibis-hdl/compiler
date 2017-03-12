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

namespace ast {

    struct decimal_literal {
        enum class tag { integer, real };
        std::string                 literal;
        tag                         hint;
    };

    std::ostream& operator<<(std::ostream& os, decimal_literal::tag const& tag);
    using boost::fusion::operator<<;
}

BOOST_FUSION_ADAPT_STRUCT(
    ast::decimal_literal,
    (std::string,                   literal)
    (ast::decimal_literal::tag,     hint)
)


namespace parser {

   namespace x3 = boost::spirit::x3;

   using x3::char_;

   auto const show_attr = [](auto const& ctx) {
       //std::cout << "ctx=" << boost::typeindex::type_id<decltype(ctx)>().pretty_name() << "\n";
       std::cout << "attr= " << boost::typeindex::type_id<decltype(x3::_attr(ctx))>().pretty_name() << "\n";
   };

   auto const integer_ = x3::rule<struct integer_class, std::string> { "integer" } =
           +char_("0-9") >> *(char_("0-9") | "_")
       ;
   auto const integer = x3::rule<struct _, std::string> {} =
       +char_("0-9") >> *(char_("0-9") | "_")
       ;

   auto const exponent = x3::rule<struct exponent_class, std::string> { "exponent" } =
       x3::lexeme [
           char_("Ee") >> -char_("+-") >> integer
       ]
       ;

   auto const decimal_literal_real = x3::rule<struct based_literal_class, std::string> { "decimal_literal<real>" } =
           x3::lexeme [
                    (integer >> char_('.') >> integer >> -exponent)
           ]
           ;

   auto const decimal_literal_int = x3::rule<struct based_literal_class, std::string> { "decimal_literal<int>" } =
           x3::lexeme [
                  (integer >> -exponent)
           ]
           ;

   auto const decimal_literal = x3::rule<struct based_literal_class, ast::decimal_literal> { "decimal_literal" } =
           x3::lexeme [
                    decimal_literal_real >> x3::attr(ast::decimal_literal::tag::real)
                  | decimal_literal_int  >> x3::attr(ast::decimal_literal::tag::integer)
           ]//[show_attr]
           ;
}

int main()
{
   namespace x3 = boost::spirit::x3;

   for(std::string const str: {
           // Integer literals
           "12", "0", "1e6", "123_456",
           // Real literals
           "12.0", "0.0", "0.456", "3.14159_26",
           // Real literals with exponents
           "1.34E-12", "1.0E+6", "6.023_46E+2_4",
   }) {
     auto iter = str.begin(), end = str.end();

     ast::decimal_literal attr;
     //std::string attr;
     bool r = x3::phrase_parse(iter, end, parser::decimal_literal, x3::space, attr);

     std::cout << "parse '" << str << "': ";
     if (r && iter == end) {
       std::cout << "succeeded: '" << attr << "'\n";
     } else {
       std::cout << "*** failed ***\n";
     }
   }

   return 0;
}


namespace ast {
    std::ostream& operator<<(std::ostream& os, decimal_literal::tag const& tag) {
        switch(tag) {
        case decimal_literal::tag::integer: os << "<int>";    break;
        case decimal_literal::tag::real:    os << "<double>"; break;
        default: os << "N/A";
        }
        return os;
    }
}

/* Note, funny things happened here, seen at eclipse console, but not linux-term:
 * $ bin/x3_decimal_literal  | strings
parse '12': succeeded: '(12 <int>)'
parse '0': succeeded: '(0 <int>)'
parse '1e6': succeeded: '(1e6 <int>)'
parse '123_456': succeeded: '(123
456 <int>)'
parse '12.0': succeeded: '(12.0 <double>)'
parse '0.0': succeeded: '(0.0 <double>)'
parse '0.456': succeeded: '(0.456 <double>)'
parse '3.14159_26': succeeded: '(3.14159
26 <double>)'
parse '1.34E-12': succeeded: '(1.34E-12 <double>)'
parse '1.0E+6': succeeded: '(1.0E+6 <double>)'
parse '6.023_46E+2_4': succeeded: '(6.023
46E+2
4 <double>)'
 */
