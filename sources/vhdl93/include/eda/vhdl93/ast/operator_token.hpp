/*
 * operator.hpp
 *
 *  Created on: 02.03.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_OPERATOR_TOKEN_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_OPERATOR_TOKEN_HPP_


#include <eda/utils/cxx_bug_fatal.hpp>

#include <iosfwd>


namespace eda { namespace vhdl93 { namespace ast {


enum class operator_token {
    // miscellaneous_operator
    EXPONENT, ABS, NOT,
    // multiplying_operator
    MUL, DIV, MOD, REM,
    // sign operator
    SIGN_POS, SIGN_NEG,
    // adding_operator
    ADD, SUB, CONCAT,
    // shift_operator
    SLL, SRL, SLA, SRA, ROL, ROR,
    // relational_operator
    EQUAL, NOT_EQUALS, LESS, LESS_EQUALS, GREATER, GREATER_EQUALS,
    // logical_operator
    AND, OR, NAND, NOR, XOR, XNOR
};


std::ostream& operator<<(std::ostream& os, operator_token token);


static inline
unsigned arity(operator_token token)
{
    switch(token) {
        case ast::operator_token::ABS:
            [[ falltrough]]
        case ast::operator_token::NOT:
            [[ falltrough]]
        case ast::operator_token::SIGN_NEG:
            [[ falltrough]]
        case ast::operator_token::SIGN_POS: {
            return 1;
        }
        default: {
            return 2;
        }
    }

    // shouldn't never be here
    return 0;
}


unsigned precedence(operator_token token);


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_OPERATOR_TOKEN_HPP_ */
