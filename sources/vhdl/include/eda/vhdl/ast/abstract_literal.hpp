/*
 * abstract_literal.hpp
 *
 *  Created on: 16.03.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_ABSTRACT_LITERAL_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_ABSTRACT_LITERAL_HPP_


#include <eda/vhdl/ast/util/namespace_alias.hpp>

#include <eda/vhdl/ast/util/nullary.hpp>
#include <eda/vhdl/ast/decimal_literal.hpp>
#include <eda/vhdl/ast/based_literal.hpp>

#include <boost/spirit/home/x3/support/ast/variant.hpp>


namespace eda { namespace vhdl { namespace ast {


using abstract_literal = x3::variant<
	nullary,
	decimal_literal,
	based_literal
>;


} } } // namespace eda.vhdl.ast



#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_ABSTRACT_LITERAL_HPP_ */
