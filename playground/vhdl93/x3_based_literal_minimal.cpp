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

   using x3::char_;
   using x3::lit;
   using x3::int_;

   auto const part = x3::rule<struct _, std::string> {} =
           x3::lexeme[ +char_("0-9") ]
           ;

   auto const exponent = x3::rule<struct _, int32_t> {} =
           (x3::lexeme [
                      (lit("E") | "e") >> int_
           ]
           | x3::attr(1)) // doesn't work???
           ;

   auto const literal = x3::rule<struct _, ast::literal> {} =
           x3::lexeme [
                  // int         string   optional<string>    int
                  int_ >> '#' >> part >> -('.' >> part) >> '#' >> exponent
           ]
           ;
}


int main()
{
   namespace x3 = boost::spirit::x3;

   for(std::string const str: {
           "4711#11111111.32#e42",
           "4711#11111111.32#E-65",
           "4711#11112222#",
   }) {
     auto iter = str.begin(), end = str.end();

     ast::literal attr;
     bool r = x3::phrase_parse(iter, end, parser::literal, x3::space, attr);

     if (r && iter == end) {
       std::cout << "succeeded: " << attr << "\n";
     } else {
       std::cout << "*** failed ***\n";
     }
   }

   return 0;
}

