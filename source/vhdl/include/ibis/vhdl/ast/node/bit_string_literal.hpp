//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-or-later
//

#pragma once

#include <ibis/vhdl/ast/util/position_tagged.hpp>

#include <ibis/vhdl/ast/util/string_span.hpp>
#include <ibis/vhdl/ast/util/numeric_base_specifier.hpp>
#include <ibis/util/cxx_bug_fatal.hpp>

#include <iosfwd>

namespace ibis::vhdl::ast {

struct bit_string_literal : position_tagged {
    // clang-format off
    enum class numeric_base_specifier : std::uint8_t {
        unspecified = std::to_underlying(ast::numeric_base_specifier::unspecified),
        base2       = std::to_underlying(ast::numeric_base_specifier::base2),
        base8       = std::to_underlying(ast::numeric_base_specifier::base8),
        base16      = std::to_underlying(ast::numeric_base_specifier::base16),
        unsupported = std::to_underlying(ast::numeric_base_specifier::unsupported)
    };
    // clang-format on

    ast::string_span literal;
    numeric_base_specifier base_specifier;

    static constexpr bool supported_base(numeric_base_specifier base)
    {
        // clang-format off
        switch (base) {
            using enum bit_string_literal::numeric_base_specifier;
            case base2:  [[fallthrough]];
            case base8:  [[fallthrough]];
            case base16: return true;
            [[unlikely]] case unspecified: [[fallthrough]];
            [[unlikely]] case unsupported: return false;
            // *No* default branch: let the compiler generate warning about enumeration
            // value not handled in switch
        }
        // clang-format on

        std::unreachable();
    }

    static constexpr auto to_base_specifier(unsigned base)
    {
        // clang-format off
        switch (base) {
            case 2U:  return numeric_base_specifier::base2;
            case 8U:  return numeric_base_specifier::base8;
            case 16U: return numeric_base_specifier::base16;
            // catch-them-all
            default: return numeric_base_specifier::unsupported;
        }
        // clang-format on

        std::unreachable();
    }
};

template <>
constexpr ast::bit_string_literal::numeric_base_specifier
convert_to<ast::bit_string_literal::numeric_base_specifier, unsigned>(unsigned const& base)
{
    return ast::bit_string_literal::to_base_specifier(base);
}

// required for BOOST_SPIRIT_X3_DEBUG
std::ostream& operator<<(std::ostream& os,
                         ast::bit_string_literal::numeric_base_specifier specifier);

}  // namespace ibis::vhdl::ast
