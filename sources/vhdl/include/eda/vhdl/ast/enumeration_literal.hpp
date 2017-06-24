/*
 * enumeration_literal.hpp
 *
 *  Created on: 17.03.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_ENUMERATION_LITERAL_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_ENUMERATION_LITERAL_HPP_


#include <boost/spirit/home/x3/support/ast/variant.hpp>
#include <eda/vhdl/ast/character_literal.hpp>
#include <eda/vhdl/ast/identifier.hpp>
#include <eda/vhdl/ast/util/namespace_alias.hpp>
#include <eda/vhdl/ast/util/nullary.hpp>


namespace eda { namespace vhdl { namespace ast {


using enumeration_literal = x3::variant<
	nullary,
	identifier,
	character_literal
>;


} } } // namespace eda.vhdl.ast



#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_ENUMERATION_LITERAL_HPP_ */
