/*
 * abstract_literal.hpp
 *
 *  Created on: 16.03.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_ABSTRACT_LITERAL_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_ABSTRACT_LITERAL_HPP_


#include <eda/vhdl93/ast/namespace_alias.hpp>

#include <eda/vhdl93/ast/nullary.hpp>
#include <eda/vhdl93/ast/decimal_literal.hpp>
#include <eda/vhdl93/ast/based_literal.hpp>

#include <boost/spirit/home/x3/support/ast/variant.hpp>


namespace eda { namespace vhdl93 { namespace ast {


using abstract_literal = x3::variant<
	nullary,
	decimal_literal,
	based_literal
>;


} } } // namespace eda.vhdl93.ast



#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_ABSTRACT_LITERAL_HPP_ */
