/*
 * x3_simple_expr.cpp
 *
 *  Created on: 25.04.2017
 *      Author: olaf
 */

/*
 * expectation error
 */

#include <iostream>
//#define BOOST_SPIRIT_X3_DEBUG
#include <boost/spirit/home/x3.hpp>
#include <boost/optional.hpp>
#include <boost/optional/optional_io.hpp>

namespace x3 = boost::spirit::x3;

namespace parser {

using x3::char_;
using x3::int_;


auto const sign = x3::rule<struct _> { "sign" } =
     char_('-') | '+'
     ;
auto const primary = x3::rule<struct _> { "primary" } =
     int_ | +x3::alpha
     ;
auto const factor = x3::rule<struct _> { "factor" } =
       primary >> "**" >> primary
     | "not" >> primary
     | primary
     ;
auto const multiplying_operator = x3::rule<struct _> { "multiplying_operator" } =
     char_('*') | '/' | "mod"
     ;
auto const term = x3::rule<struct _> { "term" } =
     factor >> *(multiplying_operator > factor)
     ;
auto const adding_operator = x3::rule<struct _> { "adding_operator" } =
     char_('+') | '-' | '&'
     ;
auto const simple_expression = x3::rule<struct _> { "simple_expression" } =
        -sign
     >> term
     >> *(adding_operator > term)
     ;
}

int main()
{
    namespace x3 = boost::spirit::x3;

    for(std::string const str: {
           "-5 mod -3",
    }) {
      auto iter = str.begin(), end = str.end();

      bool r = x3::phrase_parse(iter, end, parser::simple_expression, x3::space);

      std::cout << "parse '" << str << "': ";
      if (r && iter == end) {
        std::cout << "succeeded:\n";
        std::cout << "\n";
      } else {
        std::cout << "*** failed ***\n";
      }
    }


    return 0;
}
