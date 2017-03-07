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
#include <iterator> // for ostream_iterator
#include <typeinfo>

namespace parser {

  namespace x3 = boost::spirit::x3;
  namespace iso8859_1 = boost::spirit::x3::iso8859_1;

  using iso8859_1::char_;

  typedef x3::rule<struct integer_class, std::vector<int>> integer_type;

  integer_type const integer { "integer" };


  auto combine_to_int = [](auto &ctx) {
    using x3::_val;
    auto& v = _val(ctx);
    std::copy(v.begin(), v.end(), std::ostream_iterator<int>(std::cout, ", "));
  };

  // Parse '1_000' as 1000
  // Note: 'x3::digit >> *( -char_('_') >> x3::digit )' parses also '_' into
#if 1
  auto const integer_def =
    (
     x3::digit >> *( x3::omit[ -char_('_') ] >> x3::digit )
    )
#else
  auto const integer_def %=
    (
     x3::digit >> *( x3::omit[ -char_('_') ] >> x3::digit )
    )[combine_to_int]
#endif
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

    std::cout << "parse " << str << ": ";

    std::vector<int> i;

    bool r = x3::phrase_parse(iter, end, rule, x3::space, i);

    if (r && iter == end) {
      std::cout << "succeeded\n";
      std::copy(i.begin(), i.end(), std::ostream_iterator<char>(std::cout, " "));
      std::cout << '\n';
    } else {
      std::cout << "failed\n";
    }
  }

  return 0;
}

