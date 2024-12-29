//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-or-later
//

#pragma once

#include <iterator>
#include <type_traits>
#include <ostream>

namespace ibis::util {

///
/// \see
/// - [Printing lists with commas C++](
///  https://stackoverflow.com/questions/3496982/printing-lists-with-commas-c)
/// - [infix_iterator code](
///  https://codereview.stackexchange.com/questions/13176/infix-iterator-code)
///
/// Usage:
/// \code
/// std::vector<int> numbers = {1, 2, 3, 4};
/// std::copy(numbers.begin(), numbers.end(),
///          infix_ostream_iterator<int>(std::cout, ", "));
/// \endcode
///
/// gives:
/// \code{.unparsed}
/// 1, 2, 3, 4
/// \endcode
///
/// \note This may come obsolete with [std::experimental::ostream_joiner](
///      https://en.cppreference.com/w/cpp/experimental/ostream_joiner)
/// \note std::iterator is deprecated with C++17, hence isn't derived from this.
///
template <class T, class CharT = char, class TraitsT = std::char_traits<CharT>>
class infix_ostream_iterator {
public:
    using iterator_category = std::output_iterator_tag;
    using value_type = void;
    using difference_type = void;
    using pointer = void;
    using reference = void;

    using ostream_type = std::basic_ostream<CharT, TraitsT>;

public:
    infix_ostream_iterator(ostream_type& os_)
        : os{ &os_ }
        , actual_delimiter{ nullptr }
    {
        // Check iterator requirements; especially MSVC copy requires CopyConstructible
        // ToDo Concept Check
        static_assert(std::is_copy_constructible_v<T>, "Iterator must satisfies CopyConstructible");
        static_assert(std::is_copy_assignable_v<T>, "Iterator must satisfies CopyAssignable");
    }

    infix_ostream_iterator(ostream_type& os_, CharT const* delimiter_)
        : os{ &os_ }
        , actual_delimiter{ delimiter_ }
    {
    }

    infix_ostream_iterator<T, CharT, TraitsT>& operator=(
        infix_ostream_iterator<T, CharT, TraitsT> const& other) = default;

    infix_ostream_iterator<T, CharT, TraitsT>& operator=(T const& item)
    {
        (*os) << delimiter << item;
        delimiter = actual_delimiter;
        return *this;
    }

    infix_ostream_iterator<T, CharT, TraitsT>& operator*() { return *this; }
    infix_ostream_iterator<T, CharT, TraitsT>& operator++() { return *this; }
    infix_ostream_iterator<T, CharT, TraitsT>& operator++(int) { return *this; }

private:
    ostream_type* os;
    CharT const* actual_delimiter;
    CharT const* delimiter = "";
};

}  // namespace ibis::util
