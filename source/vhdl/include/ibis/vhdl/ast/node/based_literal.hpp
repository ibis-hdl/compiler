//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-or-later
//

#pragma once

#include <ibis/vhdl/ast/util/position_tagged.hpp>

#include <ibis/vhdl/ast/util/string_span.hpp>

#include <iosfwd>

namespace ibis::vhdl::ast {

///
/// @code{.bnf}
/// based_literal ::= base # based_integer [ . based_integer ] # [ exponent ]
/// @endcode
///
struct based_literal : position_tagged {
    enum class numeric_type_specifier : std::uint8_t { unspecified, integer, real };

    struct number_chunk {
        ast::string_span integer_part;
        ast::string_span fractional_part;
        ast::string_span exponent;
        numeric_type_specifier type_specifier;
    };

    unsigned base;
    // ast::string_span base;
    number_chunk number;
};

// required for BOOST_SPIRIT_X3_DEBUG
std::ostream& operator<<(std::ostream& os, ast::based_literal::numeric_type_specifier specifier);

}  // namespace ibis::vhdl::ast
