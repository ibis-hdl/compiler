/*
 * type_definition.hpp
 *
 *  Created on: 09.06.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_TYPE_DEFINITION_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_TYPE_DEFINITION_HPP_


#include <eda/vhdl93/ast/util/namespace_alias.hpp>

#include <eda/vhdl93/ast/util/nullary.hpp>
#include <eda/vhdl93/ast/scalar_type_definition.hpp>
#include <eda/vhdl93/ast/composite_type_definition.hpp>
#include <eda/vhdl93/ast/access_type_definition.hpp>
#include <eda/vhdl93/ast/file_type_definition.hpp>

#include <boost/spirit/home/x3/support/ast/variant.hpp>


namespace eda { namespace vhdl93 { namespace ast {


using type_definition = x3::variant<
    ast::nullary,
    ast::scalar_type_definition,
    ast::composite_type_definition,
    ast::access_type_definition,
    ast::file_type_definition
>;


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_TYPE_DEFINITION_HPP_ */
