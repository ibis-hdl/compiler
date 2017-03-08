/*
 * x3_integer.cpp
 *
 *  Created on: 06.03.2017
 *      Author: olaf
 */

/*
 * consider: BOOST_TEST_CONTEXT and BOOST_TEST_INFO
 * http://www.boost.org/doc/libs/1_60_0/libs/test/doc/html/boost_test/test_output/contexts.html
 */

 /*
 * x3_integer.cpp
 *
 *  Created on: 06.03.2017
 *      Author: olaf
 */

/*
 * consider: BOOST_TEST_CONTEXT and BOOST_TEST_INFO
 * http://www.boost.org/doc/libs/1_60_0/libs/test/doc/html/boost_test/test_output/contexts.html
 */
 
#include <iosfwd>
//#define BOOST_SPIRIT_X3_DEBUG

#include <boost/spirit/home/x3.hpp>

#include <iostream>
#include <vector>
#include <algorithm> // for copy
#include <iterator>  // for ostream_iterator
#include <sstream>

#include <boost/type_index.hpp>


namespace parser {

  namespace x3 = boost::spirit::x3;
  namespace iso8859_1 = boost::spirit::x3::iso8859_1;

  using iso8859_1::char_;

  typedef x3::rule<struct integer_class, std::vector<int>> integer_type;

  integer_type const integer { "integer" };

  auto type_of = [](auto &ctx) {
     std::cout << boost::typeindex::type_id<decltype(ctx)>().pretty_name() << "\n";
  };

  auto combine_to_uint = [](auto &ctx) {
    auto const &v = x3::_attr(ctx);
    std::ostringstream ss;
    std::copy(v.begin(), v.end(), std::ostream_iterator<int>(ss, ""));
    uint int_ { 0 };
    x3::_pass(ctx) = x3::parse(ss.str().begin(), ss.str().end(), x3::long_, int_);
    std::cout << int_ << '\n';
    x3::_val(ctx) = std::move(std::vector<int>() = {1,2,3,4});
  };

  x3::uint_parser<int, 10, 1, 1>  const digit = { };

  // Parse '1_000' as 1000
  auto const integer_def = integer %=
    (
     digit[type_of] >> *( -x3::lit('_') >> digit )
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
      "42_666_4711",
      "4_294_967_295", // uint32::max
      "4_294_967_296" // ??? how to get message about UINT_MAX failed??
      };

  typedef std::string::const_iterator iterator_type;

  for(auto str: test_cases) {
    iterator_type iter = str.begin();
    iterator_type const end = str.end();

    auto& rule = parser::integer;

    std::cout << "parse `" << str << "´:\n";

    std::vector<int> v;

    bool r = x3::phrase_parse(iter, end, rule, x3::space, v);

    if (r && iter == end) {
      std::cout << "succeeded: ";
      std::copy(v.begin(), v.end(), std::ostream_iterator<int>(std::cout, ""));
      std::cout << "\n";
    } else {
      std::cout << "failed\n";
    }
  }

  return 0;
}


/*
boost::spirit::x3::context<boost::spirit::x3::attr_context_tag, std::vector<int, std::allocator<int> >, 
boost::spirit::x3::context<boost::spirit::x3::where_context_tag, boost::iterator_range<__gnu_cxx::__normal_iterator<char const*, std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > > >, 
boost::spirit::x3::context<boost::spirit::x3::rule_val_context_tag, std::vector<int, std::allocator<int> >, 
boost::spirit::x3::context<boost::spirit::x3::parse_pass_context_tag, bool, boost::spirit::x3::context<boost::spirit::x3::skipper_tag, boost::spirit::x3::char_class<boost::spirit::char_encoding::standard, boost::spirit::x3::space_tag> const, boost::spirit::x3::unused_type> > > > >
*/

/* type_of()
boost::spirit::x3::context<boost::spirit::x3::attr_context_tag, int, 
boost::spirit::x3::context<boost::spirit::x3::where_context_tag, boost::iterator_range<__gnu_cxx::__normal_iterator<char const*, std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > > >, 
boost::spirit::x3::context<boost::spirit::x3::rule_val_context_tag, std::vector<int, std::allocator<int> >, 
boost::spirit::x3::context<boost::spirit::x3::parse_pass_context_tag, bool, boost::spirit::x3::context<boost::spirit::x3::skipper_tag, boost::spirit::x3::char_class<boost::spirit::char_encoding::standard, boost::spirit::x3::space_tag> const, boost::spirit::x3::unused_type> > > > >
*/