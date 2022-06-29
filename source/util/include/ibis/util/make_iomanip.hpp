//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-or-later
//

#pragma once

#include <iostream>
#include <type_traits>

namespace ibis::util {

///
/// Helper to make a 'streamable' C++ lambda function
///
/// Example:
/// \code{.cpp}
/// auto const answer = [](size_t count) {
///   return make_iomanip([count](std::ostream& os) {
///        if(count) {
///           os << "The answer is " << count;
///       }
///   });
/// };
/// ...
/// std::cout << answer(42) << std::endl;
/// \endcode
///
/// see [WandBox.Org](https://wandbox.org/permlink/wGDqfmxCKwqob5mp)
///
template <typename T>
struct A {
    T x;

    friend std::ostream& operator<<(std::ostream& os, A const& a)
    {
        a.x(os);
        return os;
    }
};

template <typename T>
A<std::decay_t<T>> make_iomanip(T&& x)
{
    return { std::forward<T>(x) };
}

}  // namespace ibis::util
