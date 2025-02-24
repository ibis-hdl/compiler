//
// Copyright (c) 2017-2025 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-or-later
//

#pragma once

#include <ibis/vhdl/ast/util/numeric_base_specifier.hpp>
#include <ibis/concepts.hpp>
#include <ibis/util/cxx_bug_fatal.hpp>

// #include <ibis/util/compiler/warnings_off.hpp>
#include <boost/spirit/home/x3.hpp>  // IWYU pragma: keep
// #include <ibis/util/compiler/warnings_on.hpp>

#include <ibis/namespace_alias.hpp>  // IWYU pragma: keep

#include <iterator>

namespace ibis::vhdl::ast::detail {

///
/// Utility class for dynamically selecting unsigned integer parser types according numeric base
///
template <std::bidirectional_iterator IteratorT, ibis::unsigned_integer T>
class uint_parser {
public:
    using integer_type = T;
    using iterator_type = IteratorT;

public:
    // select the concrete x3::uint_parser<> using the base_specifier
    constexpr static auto base(numeric_base_specifier base_specifier)
    {
        auto constexpr as_any_parser = [](auto derived_parser) {
            return x3::any_parser<iterator_type, integer_type>{ x3::as_parser(derived_parser) };
        };

        // clang-format off
        switch (base_specifier) {
            using enum ast::numeric_base_specifier;
            case base2: 
            {
                using parser_type = x3::uint_parser<integer_type, 2U>;
                parser_type const uint_parser = parser_type{};
                return as_any_parser(uint_parser);
            }
            case base8: 
            {
                using parser_type = x3::uint_parser<integer_type, 8U>;
                parser_type const uint_parser = parser_type{};
                return as_any_parser(uint_parser);
            }
            case base10: 
            {
                using parser_type = x3::uint_parser<integer_type, 10U>;
                parser_type const uint_parser = parser_type{};
                return as_any_parser(uint_parser);
            }
            case base16: 
            {
                using parser_type = x3::uint_parser<integer_type, 16U>;
                parser_type const uint_parser = parser_type{};
                return as_any_parser(uint_parser);
            }
            [[unlikely]] case unspecified: [[fallthrough]];
            [[unlikely]] case unsupported:
                // The caller must pass checked base_specifier
                cxx_bug_fatal("unspecified or unsupported numeric base");
            //
            // *No* default branch: let the compiler generate warning about enumeration
            // value not handled in switch
            //
        }
        // clang-format on

        std::unreachable();
    }
};

}  // namespace ibis::vhdl::ast::detail
