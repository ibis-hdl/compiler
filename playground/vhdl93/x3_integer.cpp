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

  typedef x3::rule<struct integer_class, uint32_t> integer_type;

  integer_type const integer { "integer" };

  auto print_type_of = [](auto &ctx) {
     std::cout << boost::typeindex::type_id<decltype(ctx)>().pretty_name() << "\n";
  };

  constexpr uint32_t digit_treshold(auto i) {
      return std::numeric_limits<decltype(i)>::max() % 10;
  };

  auto const combine = [](auto &ctx) {
      //typedef decltype(x3::_(ctx)) base_type;
      typedef uint32_t base_type;
      base_type result { 0 };
      uint32_t iter_cnt { 0 };
      for (auto&& ch : x3::_attr(ctx)) {
          switch (ch) {
              case '_': break;
              default:
                  if(iter_cnt > std::numeric_limits<base_type>::digits10) {
                      x3::_pass(ctx) = false;
                      continue;
                  }
                  if(iter_cnt++ < std::numeric_limits<base_type>::digits10) {
                      result = result*10 + (ch - '0');
                      //std::cout << "> c = " << iter_cnt << ", r = " << result << '\n';
                  }
                  else {
#if 0
                      switch(ch - '0') {
                      case 0: // [[fallthrough]];
                      case 1: // [[fallthrough]];
                      case 2: // [[fallthrough]];
                      case 3: // [[fallthrough]];
                      case 4: // [[fallthrough]];
                      case 5:
                          result = result*10 + (ch - '0');
                          //std::cout << ". c = " << iter_cnt << ", r = " << result << '\n';
                          break;
                      default:
                          x3::_pass(ctx) = false;
                      }
#else
                      if((ch - '0') > digit_treshold(result)) { // FixMe: > trshhld! erspart +1 in constexpr()
                    	  x3::_pass(ctx) = false;
                      }
                      else {
                    	  result = result*10 + (ch - '0');
                      }
#endif
                  }
          }
      }

      x3::_val(ctx) = result;
  };

  // Parse '1_000' as 1000
  auto const integer_def =
    x3::lexeme [ +char_("0-9_") ] [combine]
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
      "4_294_967_296",
      "4_294_967_295_0",
      "4_294_967_295_00",
      };

  typedef std::string::const_iterator iterator_type;

  for(auto str: test_cases) {
    iterator_type iter = str.begin();
    iterator_type const end = str.end();

    auto& rule = parser::integer;

    std::cout << "parse `" << str << "´:\n";

    uint32_t i;

    bool r = x3::phrase_parse(iter, end, rule, x3::space, i);

    if (r && iter == end) {
      std::cout << "succeeded: '" << str << "' -> " << i << "\n";
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
