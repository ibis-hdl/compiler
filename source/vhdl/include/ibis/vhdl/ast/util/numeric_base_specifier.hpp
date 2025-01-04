//
// Copyright (c) 2017-2025 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-or-later
//

#pragma once

#include <cstdint>

#include <ibis/util/cxx_bug_fatal.hpp>

namespace ibis::vhdl::ast {

/// @brief Numeric base specifier used on AST and numeric conversion utilities
enum class numeric_base_specifier : std::uint8_t {
    unspecified,
    base2 = 2,
    base8 = 8,
    base10 = 10,
    base16 = 16,
    unsupported = static_cast<std::underlying_type_t<numeric_base_specifier>>(-1)
};

///
/// @brief All numeric based which are supported by ibis:vhdl
/// @param base_specifier The numeric base
/// @return true if supported, otherwise false
///
static constexpr bool supported_base(numeric_base_specifier base_specifier)
{
    // clang-format off
    switch (base_specifier) {
        case numeric_base_specifier::base2:  [[fallthrough]];
        case numeric_base_specifier::base8:  [[fallthrough]];
        case numeric_base_specifier::base10: [[fallthrough]];
        case numeric_base_specifier::base16: return true;
        default: return false;
    }
    // clang-format on

    std::unreachable();
}

static constexpr auto to_base_specifier(unsigned base)
{
    // clang-format off
    switch (base) {
        case 2:  return numeric_base_specifier::base2;
        case 8:  return numeric_base_specifier::base8;
        case 10: return numeric_base_specifier::base10;
        case 16: return numeric_base_specifier::base16;
        default: return numeric_base_specifier::unsupported;
    }
    // clang-format on

    std::unreachable();
}

template <typename TargetT, typename SourceT>
constexpr TargetT convert_to([[maybe_unused]] SourceT const& arg)
{
    static_assert(false, "no specialized version implemented");
}

template <>
// NOLINTNEXTLINE(readability-inconsistent-declaration-parameter-name)
constexpr numeric_base_specifier convert_to<numeric_base_specifier, unsigned>(unsigned const& base)
{
    return to_base_specifier(base);
}

}  // namespace ibis::vhdl::ast