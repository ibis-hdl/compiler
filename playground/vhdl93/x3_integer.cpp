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
#include <vector>
#include <algorithm> // for copy
#include <iterator>  // for ostream_iterator
#include <sstream>

namespace std {
    template<class T>
    std::ostream& operator<<(std::ostream& os, std::vector<T> const& v) {
        std::copy(v.begin(), v.end(), std::ostream_iterator<T>(os, ", "));
        return os;
    }
}

namespace parser {

  namespace x3 = boost::spirit::x3;
  namespace iso8859_1 = boost::spirit::x3::iso8859_1;

  using iso8859_1::char_;

  typedef x3::rule<struct integer_class, std::vector<int>> integer_type;

  integer_type const integer { "integer" };


  auto combine_to_uint = [](auto &ctx) {
    auto const &v = x3::_attr(ctx);
    std::ostringstream ss;
    std::copy(v.begin(), v.end(), std::ostream_iterator<int>(ss, ""));
    uint int_ { 0 };
    x3::parse(ss.str().begin(), ss.str().end(), x3::uint_, int_);
    std::cout << int_ << '\n';
  };

  x3::uint_parser<int, 10, 1, 1>  const digit = { };

  // Parse '1_000' as 1000
  auto const integer_def = integer %=
    (
     digit >> *( x3::omit[ -char_('_') ] >> digit )
    )[combine_to_uint]
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
      "42_666_4711"
      };

  typedef std::string::const_iterator iterator_type;

  for(auto str: test_cases) {
    iterator_type iter = str.begin();
    iterator_type const end = str.end();

    auto& rule = parser::integer;

    std::cout << "parse `" << str << "´:\n";

    std::vector<int> i;

    bool r = x3::phrase_parse(iter, end, rule, x3::space, i);

    if (r && iter == end) {
      std::cout << "succeeded\n";
      //std::copy(i.begin(), i.end(), std::ostream_iterator<int>(std::cout, " "));
      std::cout << '\n';
    } else {
      std::cout << "failed\n";
    }
  }

  return 0;
}

