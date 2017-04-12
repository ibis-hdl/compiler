/*
 * operator_token.cpp
 *
 *  Created on: 06.04.2017
 *      Author: olaf
 */


#include <eda/vhdl93/ast/operator_token.hpp>

#include <iostream>


namespace eda { namespace vhdl93 { namespace ast {


std::ostream& operator<<(std::ostream& os, operator_token op_token)
{
    switch(op_token) {
        // miscellaneous_operator
        case operator_token::exponent:        os << "**";     break;
        case operator_token::abs:             os << "abs";    break;
        case operator_token::not_:            os << "not";    break;
        // multiplying_operator
        case operator_token::mul:             os << "*";      break;
        case operator_token::div:             os << "/";      break;
        case operator_token::mod:             os << "mod";    break;
        case operator_token::rem:             os << "rem";    break;
        // sign_operator
        case operator_token::sign_pos:        os << "+";      break;
        case operator_token::sign_neg:        os << "-";      break;
        // adding_operator
        case operator_token::add:             os << "+";      break;
        case operator_token::sub:             os << "-";      break;
        case operator_token::concat:          os << "&";      break;
        // shift_operator
        case operator_token::sll:             os << "sll";    break;
        case operator_token::srl:             os << "srl";    break;
        case operator_token::sla:             os << "sla";    break;
        case operator_token::sra:             os << "sra";    break;
        case operator_token::rol:             os << "rol";    break;
        case operator_token::ror:             os << "ror";    break;
        // relational_operator
        case operator_token::equal:           os << "=";      break;
        case operator_token::not_equals:      os << "/=";     break;
        case operator_token::less:            os << "<";      break;
        case operator_token::less_equals:     os << "<=";     break;
        case operator_token::greater:         os << ">";      break;
        case operator_token::greater_equals:  os << ">=";     break;
        // logical_operator
        case operator_token::and_:            os << "and";    break;
        case operator_token::or_:             os << "or";     break;
        case operator_token::nand:            os << "nand";   break;
        case operator_token::nor:             os << "nor";    break;
        case operator_token::xor_:            os << "xor";    break;
        case operator_token::xnor:            os << "xnor";   break;

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
        // miscellaneous_operator
        case operator_token::exponent:
            FALLTHROUGH;
        case operator_token::abs:
            FALLTHROUGH;
        case operator_token::not_: { return 6; }

        // multiplying_operator
        case operator_token::mul:
            FALLTHROUGH;
        case operator_token::div:
            FALLTHROUGH;
        case operator_token::mod:
            FALLTHROUGH;
        case operator_token::rem: { return 5; }

        // unary
        case operator_token::sign_neg:
            FALLTHROUGH;
        case operator_token::sign_pos: { return 4; }

        // adding_operator
        case operator_token::add:
            FALLTHROUGH;
        case operator_token::sub:
            FALLTHROUGH;
        case operator_token::concat: { return 3; }

        // shift_operator
        case operator_token::sll:
            FALLTHROUGH;
        case operator_token::srl:
            FALLTHROUGH;
        case operator_token::sla:
            FALLTHROUGH;
        case operator_token::sra:
            FALLTHROUGH;
        case operator_token::rol:
            FALLTHROUGH;
        case operator_token::ror: { return 2; }

        // relational_operator
        case operator_token::equal:
            FALLTHROUGH;
        case operator_token::not_equals:
            FALLTHROUGH;
        case operator_token::less:
            FALLTHROUGH;
        case operator_token::less_equals:
            FALLTHROUGH;
        case operator_token::greater:
            FALLTHROUGH;
        case operator_token::greater_equals: { return 1; }

        // logical_operator
        case operator_token::and_:
            FALLTHROUGH;
        case operator_token::or_:
            FALLTHROUGH;
        case operator_token::nand:
            FALLTHROUGH;
        case operator_token::nor:
            FALLTHROUGH;
        case operator_token::xor_:
            FALLTHROUGH;
        case operator_token::xnor: { return 0; }

        default:
            cxx_bug_fatal("vhdl93/ast operator_token out of range");
    }
}


} } } // namespace eda.vhdl93.ast




