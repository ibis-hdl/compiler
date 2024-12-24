//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-or-later
//

#pragma once

#include <ibis/vhdl/ast/util/position_tagged.hpp>

#include <ibis/vhdl/ast/util/string_span.hpp>

#include <iosfwd>

namespace ibis::vhdl::ast {

struct based_literal : position_tagged {
    enum class numeric_type_specifier : std::uint8_t { integer, real, COUNT };

    struct number_chunk {
        ast::string_span integer_part;
        ast::string_span fractional_part;
        ast::string_span exponent;
        numeric_type_specifier type_specifier;
    };

    unsigned base;
    // ast::string_span base;
    number_chunk number;

    /// convenience access to numeric type represented.
    numeric_type_specifier numeric_type() const { return number.type_specifier; }
};

inline std::ostream& operator<<(std::ostream& os,
                                ast::based_literal::numeric_type_specifier specifier)
{
    using numeric_type_specifier = ast::based_literal::numeric_type_specifier;
    auto const lookup = [&os](numeric_type_specifier specifier) {
        switch (specifier) {
            case numeric_type_specifier::integer:
                os << "integer";
                break;
            case numeric_type_specifier::real:
                os << "real";
                break;
            default:
                os << "N/A";
        }
    };
    lookup(specifier);
    return os;
}

}  // namespace ibis::vhdl::ast
