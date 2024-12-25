//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-or-later
//

#pragma once

#include <iosfwd>
#include <string_view>
#include <format>

namespace ibis::vhdl::ast {

enum class operator_token {
    UNSPECIFIED,
    // miscellaneous_operator
    EXPONENT,
    ABS,
    NOT,
    // multiplying_operator
    MUL,
    DIV,
    MOD,
    REM,
    // sign operator
    SIGN_POS,
    SIGN_NEG,
    // adding_operator
    ADD,
    SUB,
    CONCAT,
    // shift_operator
    SLL,
    SRL,
    SLA,
    SRA,
    ROL,
    ROR,
    // relational_operator
    EQUAL,
    NOT_EQUALS,
    LESS,
    LESS_EQUALS,
    GREATER,
    GREATER_EQUALS,
    // logical_operator
    AND,
    OR,
    NAND,
    NOR,
    XOR,
    XNOR
};

std::string_view as_string_view(operator_token token);

inline std::ostream& operator<<(std::ostream& os, operator_token token)
{
    os << as_string_view(token);

    return os;
}

}  // namespace ibis::vhdl::ast

template <>
struct std::formatter<ibis::vhdl::ast::operator_token> : std::formatter<std::string_view> {
    template <typename FormatContext>
    std::string_view format(ibis::vhdl::ast::operator_token token, FormatContext& ctx) const
    {
        return std::formatter<std::string_view>::format(as_string_view(token), ctx);
    }
};
