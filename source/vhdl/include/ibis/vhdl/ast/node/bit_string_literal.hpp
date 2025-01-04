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
    enum class numeric_base_specifier : std::uint8_t {
        unspecified = static_cast<std::uint8_t>(ast::numeric_base_specifier::unspecified),
        base2 = static_cast<std::uint8_t>(ast::numeric_base_specifier::base2),
        base8 = static_cast<std::uint8_t>(ast::numeric_base_specifier::base8),
        base16 = static_cast<std::uint8_t>(ast::numeric_base_specifier::base16),
        unsupported = static_cast<std::uint8_t>(ast::numeric_base_specifier::unsupported)
    };

    ast::string_span literal;
    numeric_base_specifier base_specifier;

    static constexpr bool supported_base(numeric_base_specifier base)
    {
        // clang-format off
        switch (base) {
            case numeric_base_specifier::base2:  [[fallthrough]];
            case numeric_base_specifier::base8:  [[fallthrough]];
            case numeric_base_specifier::base16: return true;
            [[unlikely]] case numeric_base_specifier::unspecified: [[fallthrough]];
            [[unlikely]] case numeric_base_specifier::unsupported: return false;
            // *No* default branch: let the compiler generate warning about enumeration
            // value not handled in switch
            // *Note* on changes, also check `to_base_specifier()!`
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
            case 16: return numeric_base_specifier::base16;
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
