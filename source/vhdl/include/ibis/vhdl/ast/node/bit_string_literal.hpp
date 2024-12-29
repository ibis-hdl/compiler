//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-or-later
//

#pragma once

#include <ibis/vhdl/ast/util/position_tagged.hpp>

#include <ibis/vhdl/ast/util/string_span.hpp>

#include <iosfwd>

namespace ibis::vhdl::ast {

struct bit_string_literal : position_tagged {
    enum class base_specifier : std::uint8_t { unspecified, bin, oct, hex };

    ast::string_span literal;
    base_specifier base_type;
};

// required for BOOST_SPIRIT_X3_DEBUG
std::ostream& operator<<(std::ostream& os, ast::bit_string_literal::base_specifier specifier);

}  // namespace ibis::vhdl::ast
