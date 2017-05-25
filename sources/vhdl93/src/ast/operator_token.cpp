/*
 * operator_token.cpp
 *
 *  Created on: 06.04.2017
 *      Author: olaf
 */


// check on C++17 compiler features
#if defined(__has_cpp_attribute)
#if     __has_cpp_attribute(fallthrough)
#define     FALLTHROUGH [[fallthrough]]
#elif     __has_cpp_attribute(clang::fallthrough)
#define     FALLTHROUGH [[clang::fallthrough]]
#else
#define FALLTHROUGH        // [[fallthrough]]
#endif
#else
#define FALLTHROUGH        // [[fallthrough]]
#endif


#include <eda/vhdl93/ast/operator_token.hpp>

#include <iostream>


namespace eda { namespace vhdl93 { namespace ast {


std::ostream& operator<<(std::ostream& os, operator_token token)
{
    switch(token) {
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

        // expression related, non-BNF
        case operator_token::EXPR_BGN:        os << "EXPR_BGN";      break;
        case operator_token::EXPR_END:        os << "EXPR_END";      break;

        default:                              os << "FAILURE";
    }

    return os;
}


/**
 * VHDL operator precedence helper
 *
 * ==== =======================     =================================
 * Prio      operator group                     operator
 * ==== =======================     =================================
 * 6    miscellaneous operators     ** | abs | not
 * 5    multiplying operators       * | / | mod | rem
 * 4    sign operators              + | -
 * 3    adding operators            + | - | &
 * 2    shift operators             sll | srl | sla | sra | rol | ror
 * 1    relational operators        = | /= | < | <= | > | >=
 * 0    logical operators           and | or | nand| nor | xor | xnor
 * ==== =======================     =================================
 * Prio 6 is the highest priority level
 */
unsigned precedence(operator_token token)
{
    switch(token) {
        // expression related, non-BNF
        case operator_token::EXPR_BGN:
            FALLTHROUGH;
        case operator_token::EXPR_END: { return 7; }

        // miscellaneous_operator
        case operator_token::EXPONENT:
            FALLTHROUGH;
        case operator_token::ABS:
            FALLTHROUGH;
        case operator_token::NOT: { return 6; }

        // multiplying_operator
        case operator_token::MUL:
            FALLTHROUGH;
        case operator_token::DIV:
            FALLTHROUGH;
        case operator_token::MOD:
            FALLTHROUGH;
        case operator_token::REM: { return 5; }

        // unary
        case operator_token::SIGN_NEG:
            FALLTHROUGH;
        case operator_token::SIGN_POS: { return 4; }

        // adding_operator
        case operator_token::ADD:
            FALLTHROUGH;
        case operator_token::SUB:
            FALLTHROUGH;
        case operator_token::CONCAT: { return 3; }

        // shift_operator
        case operator_token::SLL:
            FALLTHROUGH;
        case operator_token::SRL:
            FALLTHROUGH;
        case operator_token::SLA:
            FALLTHROUGH;
        case operator_token::SRA:
            FALLTHROUGH;
        case operator_token::ROL:
            FALLTHROUGH;
        case operator_token::ROR: { return 2; }

        // relational_operator
        case operator_token::EQUAL:
            FALLTHROUGH;
        case operator_token::NOT_EQUALS:
            FALLTHROUGH;
        case operator_token::LESS:
            FALLTHROUGH;
        case operator_token::LESS_EQUALS:
            FALLTHROUGH;
        case operator_token::GREATER:
            FALLTHROUGH;
        case operator_token::GREATER_EQUALS: { return 1; }

        // logical_operator
        case operator_token::AND:
            FALLTHROUGH;
        case operator_token::OR:
            FALLTHROUGH;
        case operator_token::NAND:
            FALLTHROUGH;
        case operator_token::NOR:
            FALLTHROUGH;
        case operator_token::XOR:
            FALLTHROUGH;
        case operator_token::XNOR: { return 0; }

        default:
            cxx_bug_fatal("vhdl93/ast operator_token out of range");
    }
}


} } } // namespace eda.vhdl93.ast




