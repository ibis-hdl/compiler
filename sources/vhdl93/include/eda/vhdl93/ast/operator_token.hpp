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
    exponent,
    abs,
    not_,
    // multiplying_operator
    mul,
    div,
    mod,
    rem,
    // sign_operator
    sign_pos,
    sign_neg,
    // adding_operator
    add,
    sub,
    concat,
    // shift_operator
    sll,
    srl,
    sla,
    sra,
    rol,
    ror,
    // relational_operator
    equal,
    not_equals,
    less,
    less_equals,
    greater,
    greater_equals,
    // logical_operator
    and_,
    or_,
    nand,
    nor,
    xor_,
    xnor
};


std::ostream& operator<<(std::ostream& os, operator_token op_token);


unsigned precedence(operator_token token);


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_OPERATOR_TOKEN_HPP_ */
