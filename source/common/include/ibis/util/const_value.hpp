//
// Copyright (c) 2017-2024 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-or-later
//

#pragma once

#include <concepts>
#include <utility>
#include <type_traits>

namespace ibis::util {

///
/// @brief Wrapper to express const values
/// @tparam T Integral type
///
/// This wrapper/help is based on articles from Arthur O'Dwyer [const all the things?](
/// https://quuxplusone.github.io/blog/2022/01/23/dont-const-all-the-things/) and
/// Lesley Lai [The implication of const or reference member variables in C++](
/// https://lesleylai.info/en/const-and-reference-member-variables/).
/// One is tempted to make constant class members explicit `const`. However, in C++ this
/// is expressed via private members and public getter functions. In addition, `const`
/// members make the move semantic impossible.
/// But now you often have smaller auxiliary classes expressed as `struct` - it would
/// simply be too complex there, hence this wrapper. It also makes Clang-Tidy
/// *[cppcoreguidelines-avoid-const-or-ref-data-members](
/// https://clang.llvm.org/extra/clang-tidy/checks/cppcoreguidelines/avoid-const-or-ref-data-members.html)*
/// happy :)
/// For proof of concept @see [godbolt](https://godbolt.org/z/97vrx87K6)
///
template <typename T>
    requires(!std::is_reference_v<T>)
class const_value {
    T val_;

public:
    constexpr const_value() = default;
    constexpr explicit const_value(T const& val)
        : val_{ val }
    {
    }
    constexpr const_value(T&& val)
        : val_{ std::move(val) }
    {
    }
    auto operator<=>(const_value const&) const = default;

    [[nodiscard]] constexpr const T& get() const noexcept { return val_; }
    // NOLINTNEXTLINE(hicpp-explicit-conversions), implicit intended for POD like behaviour
    [[nodiscard]] constexpr operator T() const noexcept { return val_; }
};

template <typename T, typename U>
    requires std::integral<U> && std::equality_comparable_with<T, U>
constexpr bool operator==(const_value<T> lhs, U rhs) noexcept
{
    // note, std::cmp_equal is noexcept
    return std::cmp_equal(lhs.get(), rhs);
}

template <typename T, typename U>
    requires std::integral<U> && std::totally_ordered_with<T, U>
constexpr auto operator<=>(const_value<T> lhs, U rhs) noexcept
{
    return lhs.get() <=> rhs;
}

}  // namespace ibis::util
