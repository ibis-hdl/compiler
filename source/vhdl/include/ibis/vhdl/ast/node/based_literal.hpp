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

///
/// @code{.bnf}
/// based_literal ::= base # based_integer [ . based_integer ] # [ exponent ]
/// @endcode
///
struct based_literal : position_tagged {
    enum class numeric_type_specifier : std::uint8_t { unspecified, integer, real };

    enum class numeric_base_specifier : std::uint8_t {
        unspecified = static_cast<std::uint8_t>(ast::numeric_base_specifier::unspecified),
        base2 = static_cast<std::uint8_t>(ast::numeric_base_specifier::base2),
        base8 = static_cast<std::uint8_t>(ast::numeric_base_specifier::base8),
        base10 = static_cast<std::uint8_t>(ast::numeric_base_specifier::base10),
        base16 = static_cast<std::uint8_t>(ast::numeric_base_specifier::base16),
        unsupported = static_cast<std::uint8_t>(ast::numeric_base_specifier::unsupported)
    };

    struct number_chunk {
        ast::string_span integer_part;
        ast::string_span fractional_part;
        ast::string_span exponent;
        numeric_type_specifier type_specifier;
    };

    // Idea:
    // - ast::numeric_base_specifier base;
    // - get the string_span of base identifier, convert to numeric_base_specifier immediately
    // - tag the base, no error handling at parse stage any more
    // - this requires a simple function for filter_view to get rid of '_'
    // - this requires to_numeric_base_specifier() function or equivalent
    // - error handling is delay at conversion time, here will rising the unsupported etc. message
    // - this makes it more conform to other numeric_convert functions
    // - after AST traverse can simply trigger a warning
    unsigned base_id;  // ToDo Revert Spirit.X3 here, make mini-parser for 3-chars-width and convert
    numeric_base_specifier base_specifier;

    number_chunk number;

    static constexpr bool supported_base(numeric_base_specifier base)
    {
        // clang-format off
        switch (base) {
            case numeric_base_specifier::base2:  [[fallthrough]];
            case numeric_base_specifier::base8:  [[fallthrough]];
            case numeric_base_specifier::base10: [[fallthrough]];
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
            case 10: return numeric_base_specifier::base10;
            case 16: return numeric_base_specifier::base16;
            // catch-them-all
            default: return numeric_base_specifier::unsupported;
        }
        // clang-format on

        std::unreachable();
    }
};

template <>
constexpr ast::based_literal::numeric_base_specifier
convert_to<ast::based_literal::numeric_base_specifier, unsigned>(unsigned const& base)
{
    return ast::based_literal::to_base_specifier(base);
}

// required for BOOST_SPIRIT_X3_DEBUG
std::ostream& operator<<(std::ostream& os, ast::based_literal::numeric_type_specifier specifier);

}  // namespace ibis::vhdl::ast
