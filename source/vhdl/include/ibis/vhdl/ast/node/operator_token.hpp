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
    UNSPECIFIED_OPERATOR,
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

// required for BOOST_SPIRIT_X3_DEBUG
std::ostream& operator<<(std::ostream& os, operator_token token);

}  // namespace ibis::vhdl::ast
