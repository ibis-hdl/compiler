/*
 * numeric_literal.hpp
 *
 *  Created on: 17.03.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_NUMERIC_LITERAL_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_NUMERIC_LITERAL_HPP_


#include <boost/spirit/home/x3/support/ast/variant.hpp>
#include <eda/vhdl/ast/abstract_literal.hpp>
#include <eda/vhdl/ast/physical_literal.hpp>
#include <eda/vhdl/ast/util/namespace_alias.hpp>
#include <eda/vhdl/ast/util/nullary.hpp>


namespace eda { namespace vhdl { namespace ast {


using numeric_literal = x3::variant<
	nullary,
	abstract_literal,
	physical_literal
>;


} } } // namespace eda.vhdl.ast



#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_NUMERIC_LITERAL_HPP_ */
