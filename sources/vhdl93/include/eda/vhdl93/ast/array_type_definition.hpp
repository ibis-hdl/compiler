/*
 * array_type_definition.hpp
 *
 *  Created on: 09.06.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_ARRAY_TYPE_DEFINITION_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_ARRAY_TYPE_DEFINITION_HPP_


#include <eda/vhdl93/ast/namespace_alias.hpp>

#include <eda/vhdl93/ast/nullary.hpp>
#include <eda/vhdl93/ast/unconstrained_array_definition.hpp>
#include <eda/vhdl93/ast/constrained_array_definition.hpp>

#include <boost/spirit/home/x3/support/ast/variant.hpp>


namespace eda { namespace vhdl93 { namespace ast {


using array_type_definition = x3::variant<
    ast::nullary,
    ast::unconstrained_array_definition,
    ast::constrained_array_definition
>;


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_ARRAY_TYPE_DEFINITION_HPP_ */