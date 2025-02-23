//
// Copyright (c) 2017-2025 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-or-later
//

#pragma once

#include <concepts>
#include <tuple>

// utility functions, too small top put them into own header
namespace ibis::util {

///
/// Get the pair of iterators (range) of the container.
///
/// Lightweight alternative to [Coliru](https://coliru.stacked-crooked.com/a/003c422d426ba69b)
/// @code {.cpp}
/// auto [first, last] = std::ranges::subrange(my_vector);
/// @endcode
///
/// Proof of concept @see [Coliru](https://coliru.stacked-crooked.com/a/642115010e33c5b0)
template <typename ContainerT>
// clang-format off
requires requires(ContainerT container) {
    { container.begin() }  -> std::same_as<typename ContainerT::iterator>;
    { container.end() }    -> std::same_as<typename ContainerT::iterator>;
    { container.cbegin() } -> std::same_as<typename ContainerT::const_iterator>;
    { container.cend() }   -> std::same_as<typename ContainerT::const_iterator>;  
}
// clang-format on
static inline auto get_iterator_pair(ContainerT const& container)
    -> std::tuple<typename ContainerT::const_iterator, typename ContainerT::const_iterator>
{
    return { container.cbegin(), container.cend() };
}

}  // namespace ibis::util
