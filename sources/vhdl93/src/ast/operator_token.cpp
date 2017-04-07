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
        // multiplying_operator
        case operator_token::mul:             os << "*";      break;
        case operator_token::div:             os << "/";      break;
        case operator_token::mod:             os << "mod";    break;
        case operator_token::rem:             os << "rem";    break;
        // adding_operator
        case operator_token::add:             os << "+";      break;
        case operator_token::sub:             os << "-";      break;
        case operator_token::concat:          os << "&";      break;
        // logical_operator
        case operator_token::and_:            os << "and";    break;
        case operator_token::or_:             os << "or";     break;
        case operator_token::nand:            os << "nand";   break;
        case operator_token::nor:             os << "nor";    break;
        case operator_token::xor_:            os << "xor";    break;
        case operator_token::xnor:            os << "xnor";   break;
        // relational_operator
        case operator_token::equal:           os << "=";      break;
        case operator_token::not_equals:      os << "/=";     break;
        case operator_token::less:            os << "<";      break;
        case operator_token::less_equals:     os << "<=";     break;
        case operator_token::greater:         os << ">";      break;
        case operator_token::greater_equals:  os << ">=";     break;
        // miscellaneous_operator
        case operator_token::exponent:        os << "**";     break;
        case operator_token::abs:             os << "abs";    break;
        case operator_token::not_:            os << "not";    break;
        // shift_operator
        case operator_token::sll:             os << "sll";    break;
        case operator_token::srl:             os << "srl";    break;
        case operator_token::sla:             os << "sla";    break;
        case operator_token::sra:             os << "sra";    break;
        case operator_token::rol:             os << "rol";    break;
        case operator_token::ror:             os << "ror";    break;

        default:                              os << "FAILURE";
    }

    return os;
}


} } } // namespace eda.vhdl93.ast




