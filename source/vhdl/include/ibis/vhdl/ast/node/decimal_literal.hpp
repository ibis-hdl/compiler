//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-or-later
//

#pragma once

#include <ibis/vhdl/ast/util/position_tagged.hpp>

#include <ibis/vhdl/ast/util/string_span.hpp>

namespace ibis::vhdl::ast {

///
/// @code{.bnf}
/// decimal_literal ::= integer [ . integer ] [ exponent ]
/// @endcode
///
/// @note `decimal_literal` is parsed as complete (real|integer) literal and tagged accordingly.
///
struct decimal_literal : position_tagged {
    enum class numeric_type_specifier { unspecified, integer, real };

    ast::string_span literal;
    numeric_type_specifier type_specifier;
};

// required for BOOST_SPIRIT_X3_DEBUG
std::ostream& operator<<(std::ostream& os, ast::decimal_literal::numeric_type_specifier specifier);

}  // namespace ibis::vhdl::ast
