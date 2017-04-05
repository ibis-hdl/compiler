/*
 * operator.hpp
 *
 *  Created on: 02.03.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_OPERATOR_TOKEN_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_OPERATOR_TOKEN_HPP_


namespace eda { namespace vhdl93 { namespace ast {


enum class operator_token {
	// logical_operator
	and_,
	or_,
	nand,
	nor,
	xor_,
	xnor,
	// relational_operator
	equal,
	not_equals,
	less,
	less_equals,
	greater,
	greater_equals,
	// miscellaneous_operator
	exponent,
	abs,
	not_,
	// adding_operator
	add,
	sub,
	concat,
	// multiplying_operator
	mul,
	div,
	mod,
	rem,
	// shift_operator
	sll,
	srl,
	sla,
	sra,
	rol,
	ror,
};


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_OPERATOR_TOKEN_HPP_ */
