//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-or-later
//

#include <ibis/vhdl/ast/node/operator_token.hpp>

#include <ibis/util/cxx_bug_fatal.hpp>
#include <iostream>

namespace ibis::vhdl::ast {

std::string_view as_string_view(operator_token token)
{
    std::string_view token_sv{};

    // clang-format off
    switch (token) {
        // miscellaneous_operator
        case operator_token::EXPONENT:        token_sv = "EXPONENT";      break;
        case operator_token::ABS:             token_sv = "ABS";           break;
        case operator_token::NOT:             token_sv = "NOT";           break;
        // multiplying_operator
        case operator_token::MUL:             token_sv = "MUL";           break;
        case operator_token::DIV:             token_sv = "DIV";           break;
        case operator_token::MOD:             token_sv = "MOD";           break;
        case operator_token::REM:             token_sv = "REM";           break;
        // sign_operator
        case operator_token::SIGN_POS:        token_sv = "SIGN_POS";      break;
        case operator_token::SIGN_NEG:        token_sv = "SIGN_NEG";      break;
        // adding_operator
        case operator_token::ADD:             token_sv = "ADD";           break;
        case operator_token::SUB:             token_sv = "SUB";           break;
        case operator_token::CONCAT:          token_sv = "CONCAT";        break;
        // shift_operator
        case operator_token::SLL:             token_sv = "SLL";           break;
        case operator_token::SRL:             token_sv = "SRL";           break;
        case operator_token::SLA:             token_sv = "SLA";           break;
        case operator_token::SRA:             token_sv = "SRA";           break;
        case operator_token::ROL:             token_sv = "ROL";           break;
        case operator_token::ROR:             token_sv = "ROR";           break;
        // relational_operator
        case operator_token::EQUAL:           token_sv = "EQUAL";         break;
        case operator_token::NOT_EQUALS:      token_sv = "NOT_EQUALS";    break;
        case operator_token::LESS:            token_sv = "LESS";          break;
        case operator_token::LESS_EQUALS:     token_sv = "LESS_EQUALS";   break;
        case operator_token::GREATER:         token_sv = "GREATER";       break;
        case operator_token::GREATER_EQUALS:  token_sv = "GREATER_EQUALS"; break;
        // logical_operator
        case operator_token::AND:             token_sv = "AND";           break;
        case operator_token::OR:              token_sv = "OR";            break;
        case operator_token::NAND:            token_sv = "NAND";          break;
        case operator_token::NOR:             token_sv = "NOR";           break;
        case operator_token::XOR:             token_sv = "XOR";           break;
        case operator_token::XNOR:            token_sv = "XNOR";          break;

        case operator_token::UNSPECIFIED:
        // probably got a default constructed token
            cxx_bug_fatal("keyword_token not specified!");

        default:// unreachable_bug_triggered
            cxx_unreachable_bug_triggered();
    }
    // clang-format on

    return token_sv;
}

#if 0
///
/// VHDL operator arity helper
///
/// @note unused and not required since BNCF takes care on it. Only here as archive.
///
unsigned arity(operator_token token)
{
    switch(token) {
        case ast::operator_token::ABS:      [[fallthrough]];
        case ast::operator_token::NOT:      [[fallthrough]];
        case ast::operator_token::SIGN_NEG: [[fallthrough]];
        case ast::operator_token::SIGN_POS: return 1;
        default:                            return 2;
    }

    cxx_unreachable_bug_triggered();
}


///
/// VHDL operator precedence helper
///
/// @note unused and not required since BNCF takes care on it. Only here as archive.
///
/// ==== =======================     =================================
/// Prio      operator group                     operator
/// ==== =======================     =================================
/// 6    miscellaneous operators     ** | abs | not
/// 5    multiplying operators       * | / | mod | rem
/// 4    sign operators              + | -
/// 3    adding operators            + | - | &
/// 2    shift operators             sll | srl | sla | sra | rol | ror
/// 1    relational operators        = | /= | < | <= | > | >=
/// 0    logical operators           and | or | nand| nor | xor | xnor
/// ==== =======================     =================================
/// Prio 6 is the highest priority level
///
unsigned precedence(operator_token token)
{
    switch(token) {
        // miscellaneous_operator
        case operator_token::EXPONENT:      [[fallthrough]];
        case operator_token::ABS:           [[fallthrough]];
        case operator_token::NOT:           { return 6; }

        // multiplying_operator
        case operator_token::MUL:           [[fallthrough]];
        case operator_token::DIV:           [[fallthrough]];
        case operator_token::MOD:           [[fallthrough]];
        case operator_token::REM:           { return 5; }

        // unary
        case operator_token::SIGN_NEG:      [[fallthrough]];
        case operator_token::SIGN_POS:      { return 4; }

        // adding_operator
        case operator_token::ADD:           [[fallthrough]];
        case operator_token::SUB:           [[fallthrough]];
        case operator_token::CONCAT:        { return 3; }

        // shift_operator
        case operator_token::SLL:           [[fallthrough]];
        case operator_token::SRL:           [[fallthrough]];
        case operator_token::SLA:           [[fallthrough]];
        case operator_token::SRA:           [[fallthrough]];
        case operator_token::ROL:           [[fallthrough]];
        case operator_token::ROR:           { return 2; }

        // relational_operator
        case operator_token::EQUAL:         [[fallthrough]];
        case operator_token::NOT_EQUALS:    [[fallthrough]];
        case operator_token::LESS:          [[fallthrough]];
        case operator_token::LESS_EQUALS:   [[fallthrough]];
        case operator_token::GREATER:       [[fallthrough]];
        case operator_token::GREATER_EQUALS: { return 1; }

        // logical_operator
        case operator_token::AND:           [[fallthrough]];
        case operator_token::OR:            [[fallthrough]];
        case operator_token::NAND:          [[fallthrough]];
        case operator_token::NOR:           [[fallthrough]];
        case operator_token::XOR:           [[fallthrough]];
        case operator_token::XNOR:          { return 0; }

        default:
            cxx_unreachable_bug_triggered();
    }
}
#endif

}  // namespace ibis::vhdl::ast
