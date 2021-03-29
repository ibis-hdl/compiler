#pragma once

#include <iosfwd>

namespace eda::vhdl::ast {

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

}  // namespace eda::vhdl::ast
