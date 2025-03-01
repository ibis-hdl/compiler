//
// Copyright (c) 2017-2025 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-or-later
//

#pragma once

#include <ibis/concepts.hpp>
#include <concepts>
#include <type_traits>
#include <utility>

namespace ibis::util {

///
/// @brief Strong type for integral type
///
/// This type is opaque to prevent unwanted allocation by accident or chance
///
/// @tparam T The underlying integral type
///
/// @see [Strong types for strong interfaces](
///       https://www.fluentcpp.com/2016/12/08/strong-types-for-strong-interfaces/)
/// @see [Overloading the Spaceship Operator, A Recipe](
///       https://indii.org/blog/overloading-the-spaceship-operator/)
///
/// For proof of concept, see [godbolt](https://godbolt.org/z/zGqcPrPEz)
///
template <typename T, typename uniqueTag>
    requires ibis::integer<T>
class strong_type {
public:
    constexpr strong_type() = default;

    constexpr explicit strong_type(T const& val)
        : value{ val }
    {
    }

    constexpr explicit strong_type(T&& val)
        : value{ std::move(val) }
    {
    }

public:
    using value_type = std::remove_cv_t<T>;

public:
    auto operator<=>(strong_type const&) const = default;

public:
    [[nodiscard]] constexpr const value_type& get() const { return value; }
    [[nodiscard]] constexpr operator value_type() const { return value; }

private:
    value_type value;
};

template <typename T, typename uniqueTag, typename U>
    requires std::integral<U> && std::equality_comparable_with<T, U>
constexpr bool operator==(strong_type<T, uniqueTag> lhs, U rhs)
{
    return std::cmp_equal(lhs.get(), rhs);
}

template <typename T, typename uniqueTag, typename U>
    requires std::integral<U> && std::equality_comparable_with<T, U>
constexpr auto operator<=>(strong_type<T, uniqueTag> lhs, U rhs)
{
    return lhs.get() <=> rhs;
}

}  // namespace ibis::util
