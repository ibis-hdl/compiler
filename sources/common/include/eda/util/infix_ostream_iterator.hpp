/*
 * infix_ostream_iterator.hpp
 *
 *  Created on: 30.07.2018
 *      Author: olaf
 */

#ifndef SOURCES_COMMON_INCLUDE_EDA_UTIL_INFIX_OSTREAM_ITERATOR_HPP_
#define SOURCES_COMMON_INCLUDE_EDA_UTIL_INFIX_OSTREAM_ITERATOR_HPP_

#include <iterator>
#include <ostream>

namespace eda {
namespace util {

/**
 * \see
 * - [Printing lists with commas C++](
 *   https://stackoverflow.com/questions/3496982/printing-lists-with-commas-c)
 * - [infix_iterator code](
 *   https://codereview.stackexchange.com/questions/13176/infix-iterator-code)
 *
 * Usage:
 * \code
 * std::vector<int> numbers = {1, 2, 3, 4};
 * std::copy(begin(numbers), end(numbers),
 *           infix_ostream_iterator<int>(std::cout, ", "));
 * \endcode
 *
 * gives:
 * \code{.unparsed}
 * 1, 2, 3, 4
 * \endcode
 *
 * \note This may come obsolete with [std::experimental::ostream_joiner](
 *       https://en.cppreference.com/w/cpp/experimental/ostream_joiner)
 */
template <class T, class CharT = char, class TraitsT = std::char_traits<CharT>>
class infix_ostream_iterator
{
public:
	using iterator_category = std::output_iterator_tag;
    using value_type = void;
    using difference_type = void;
    using pointer = void;
    using reference = void;

    using ostream_type = std::basic_ostream<CharT, TraitsT>;

public:
    infix_ostream_iterator(ostream_type& os_)
        : os{ os_ }
        , actual_delimiter{ nullptr }
    {
    }

    infix_ostream_iterator(ostream_type& os_, CharT const* delimiter_)
        : os{ os_ }
        , actual_delimiter{ delimiter_ }
    {
    }

    infix_ostream_iterator<T, CharT, TraitsT>& operator=(T const& item)
    {
        os << delimiter << item;
        delimiter = actual_delimiter;
        return *this;
    }

    infix_ostream_iterator<T, CharT, TraitsT>& operator*() { return *this; }
    infix_ostream_iterator<T, CharT, TraitsT>& operator++() { return *this; }
    infix_ostream_iterator<T, CharT, TraitsT>& operator++(int) { return *this; }

private:
    // clang-format off
    std::basic_ostream<CharT, TraitsT>&             os;
    CharT const*                                    actual_delimiter;
    CharT const*                                    delimiter = "";
    // clang-format on
};

} // namespace util
} // namespace eda

#endif /* SOURCES_COMMON_INCLUDE_EDA_UTIL_INFIX_OSTREAM_ITERATOR_HPP_ */
