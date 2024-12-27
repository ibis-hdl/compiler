//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-or-later
//

#pragma once

#include <ibis/vhdl/ast/util/position_tagged.hpp>

#include <ibis/vhdl/ast/util/string_span.hpp>

namespace ibis::vhdl::ast {

struct bit_string_literal : position_tagged {
    enum class base_specifier { bin, oct, hex };

    ast::string_span literal;
    base_specifier base_type;   // ToDo: add enum unspecified
};

inline std::ostream& operator<<(std::ostream& os, ast::bit_string_literal::base_specifier specifier)
{
    // ToDo[C++20] Use std::formatter
    using base_specifier = ast::bit_string_literal::base_specifier;
    auto const lookup = [&os](base_specifier specifier) {
        switch (specifier) {
            case base_specifier::bin:
                os << "bin";
                break;
            case base_specifier::oct:
                os << "oct";
                break;
            case base_specifier::hex:
                os << "hex";
                break;
            default:
                os << "N/A";
        }
    };
    
    lookup(specifier);
    return os;
}

}  // namespace ibis::vhdl::ast
