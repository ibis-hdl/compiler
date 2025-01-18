//
// Copyright (c) 2017-2025 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-or-later
//

#pragma once

#include <ibis/concepts.hpp>
#include <concepts>

namespace ibis::util {

///
/// @brief Strong type for integral type
///        This type is opaque to prevent unwanted allocation by accident or chance
/// @tparam T The underlying integral type
/// @see [Strong types for strong interfaces](
///       https://www.fluentcpp.com/2016/12/08/strong-types-for-strong-interfaces/)
/// @see [Overloading the Spaceship Operator, A Recipe](
///       https://indii.org/blog/overloading-the-spaceship-operator/)
///
template <typename T, typename uniqueTag>
    requires ibis::integer<T>
class strong_type {
    T val_;

public:
    constexpr strong_type() = default;

    constexpr explicit strong_type(T const& val)
        : val_{ val }
    {
    }

    constexpr explicit strong_type(T&& val)
        : val_{ std::move(val) }
    {
    }

public:
    using underlying_type = T;

public:
    auto operator<=>(strong_type const&) const = default;

public:
    [[nodiscard]] constexpr auto get() const -> const T& { return val_; }
    [[nodiscard]] constexpr operator T() const { return val_; }
};

template <typename T, typename uniqueTag, typename U>
    requires std::equality_comparable_with<T, U>
constexpr bool operator==(strong_type<T, uniqueTag> lhs, U rhs)
{
    return lhs.get() == rhs;
}

template <typename T, typename uniqueTag, typename U>
    requires std::totally_ordered_with<T, U>
constexpr auto operator<=>(strong_type<T, uniqueTag> lhs, U rhs)
{
    return lhs.get() <=> rhs;
}

}  // namespace ibis::util