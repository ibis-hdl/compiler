//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-only
//

#pragma once

#include <iosfwd>

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

std::ostream& operator<<(std::ostream& os, operator_token token);

unsigned arity(operator_token token);
unsigned precedence(operator_token token);

}  // namespace ibis::vhdl::ast
