//
// Copyright (c) 2017-2025 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-or-later
//

#pragma once

#include <concepts>
// #include <limits>

///
/// Concepts used on ibis project
/// @see [coliru](https://coliru.stacked-crooked.com/a/d37772cdceb0d6b1)
///
namespace ibis {

template <typename T>
concept integer = std::integral<T> && !std::same_as<T, bool>;

template <typename T>
concept unsigned_integer = integer<T> && std::unsigned_integral<T>;

template <typename T>
concept signed_integer = integer<T> && std::signed_integral<T>;

template <typename T>
concept real = std::floating_point<T> /* && std::numeric_limits<T>::is_iec559<T> */;

}  // namespace ibis
