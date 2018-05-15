#include <string>
#include <string_view>
#include <iostream>

#include <boost/range/iterator_range.hpp>
#include <boost/spirit/home/support/string_traits.hpp>
#include <iterator>     // std::iterator_traits

#include <boost/type_index.hpp>


template <typename IteratorT>
static inline constexpr
auto as_string_view(boost::iterator_range<IteratorT> const& range)
{
  using char_type = typename std::iterator_traits<IteratorT>::value_type;

  std::cout << boost::typeindex::type_id<char_type>().pretty_name() << '\n';

  static_assert(boost::spirit::traits::is_char<char_type>::value, "CharType required");

  return std::basic_string_view<char_type>{ std::addressof(*range.begin()), range.size() };
}


int main()
{
  std::string const input{ "This is cool" };

  boost::iterator_range<std::string::const_iterator> range{ input.begin(), input.end() };
  
  std::cout << range << '\n';
  std::cout << as_string_view(range) << '\n';
}
