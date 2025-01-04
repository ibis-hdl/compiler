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
            case numeric_base_specifier::base2: {
                using parser_type = x3::uint_parser<integer_type, 2>;
                parser_type const uint_parser = parser_type{};
                return as_any_parser(uint_parser);
            }
            case numeric_base_specifier::base8: {
                using parser_type = x3::uint_parser<integer_type, 8>;
                parser_type const uint_parser = parser_type{};
                return as_any_parser(uint_parser);
            }
            case numeric_base_specifier::base10: {
                using parser_type = x3::uint_parser<integer_type, 10>;
                parser_type const uint_parser = parser_type{};
                return as_any_parser(uint_parser);
            }
            case numeric_base_specifier::base16: {
                using parser_type = x3::uint_parser<integer_type, 16>;
                parser_type const uint_parser = parser_type{};
                return as_any_parser(uint_parser);
            }
            [[unlikely]] case numeric_base_specifier::unspecified: [[fallthrough]];
            [[unlikely]] case numeric_base_specifier::unsupported:
                // The caller must pass checked base_specifier
                cxx_unreachable_bug_triggered();
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
