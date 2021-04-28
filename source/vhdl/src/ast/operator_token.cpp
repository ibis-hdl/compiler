#include <ibis/vhdl/ast/node/operator_token.hpp>

#include <ibis/util/cxx_bug_fatal.hpp>
#include <iostream>

namespace ibis::vhdl::ast {

std::ostream& operator<<(std::ostream& os, operator_token token)
{
    // clang-format off
    switch (token) {
        // miscellaneous_operator
        case operator_token::EXPONENT:        os << "EXPONENT";      break;
        case operator_token::ABS:             os << "ABS";           break;
        case operator_token::NOT:             os << "NOT";           break;
        // multiplying_operator
        case operator_token::MUL:             os << "MUL";           break;
        case operator_token::DIV:             os << "DIV";           break;
        case operator_token::MOD:             os << "MOD";           break;
        case operator_token::REM:             os << "REM";           break;
        // sign_operator
        case operator_token::SIGN_POS:        os << "SIGN_POS";      break;
        case operator_token::SIGN_NEG:        os << "SIGN_NEG";      break;
        // adding_operator
        case operator_token::ADD:             os << "ADD";           break;
        case operator_token::SUB:             os << "SUB";           break;
        case operator_token::CONCAT:          os << "CONCAT";        break;
        // shift_operator
        case operator_token::SLL:             os << "SLL";           break;
        case operator_token::SRL:             os << "SRL";           break;
        case operator_token::SLA:             os << "SLA";           break;
        case operator_token::SRA:             os << "SRA";           break;
        case operator_token::ROL:             os << "ROL";           break;
        case operator_token::ROR:             os << "ROR";           break;
        // relational_operator
        case operator_token::EQUAL:           os << "EQUAL";         break;
        case operator_token::NOT_EQUALS:      os << "NOT_EQUALS";    break;
        case operator_token::LESS:            os << "LESS";          break;
        case operator_token::LESS_EQUALS:     os << "LESS_EQUALS";   break;
        case operator_token::GREATER:         os << "GREATER";       break;
        case operator_token::GREATER_EQUALS:  os << "GREATER_EQUALS"; break;
        // logical_operator
        case operator_token::AND:             os << "AND";           break;
        case operator_token::OR:              os << "OR";            break;
        case operator_token::NAND:            os << "NAND";          break;
        case operator_token::NOR:             os << "NOR";           break;
        case operator_token::XOR:             os << "XOR";           break;
        case operator_token::XNOR:            os << "XNOR";          break;

        case operator_token::UNSPECIFIED:
            cxx_bug_fatal("keyword_token not specified!");

        default:
            cxx_unreachable_bug_triggered();
    }
    // clang-format on

    return os;
}

#if 0
///
/// VHDL operator arity helper
///
/// FixMe: unused and not required since BNCF takes care on it.
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
/// FixMe: unused and not required since BNCF takes care on it.
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
