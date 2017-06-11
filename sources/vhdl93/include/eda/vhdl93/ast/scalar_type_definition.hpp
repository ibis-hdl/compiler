/*
 * scalar_type_definition.hpp
 *
 *  Created on: 09.06.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_SCALAR_TYPE_DEFINITION_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_SCALAR_TYPE_DEFINITION_HPP_


#include <eda/vhdl93/ast/namespace_alias.hpp>

#include <eda/vhdl93/ast/nullary.hpp>
#include <eda/vhdl93/ast/enumeration_type_definition.hpp>
#include <eda/vhdl93/ast/integer_type_definition.hpp>
#include <eda/vhdl93/ast/floating_type_definition.hpp>
#include <eda/vhdl93/ast/physical_type_definition.hpp>

#include <boost/spirit/home/x3/support/ast/variant.hpp>


namespace eda { namespace vhdl93 { namespace ast {


using scalar_type_definition = x3::variant<
    ast::nullary,
    ast::enumeration_type_definition,
    ast::integer_type_definition,
    ast::floating_type_definition,
    ast::physical_type_definition
>;


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_SCALAR_TYPE_DEFINITION_HPP_ */