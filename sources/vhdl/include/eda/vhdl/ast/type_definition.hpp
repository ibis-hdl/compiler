/*
 * type_definition.hpp
 *
 *  Created on: 09.06.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_TYPE_DEFINITION_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_TYPE_DEFINITION_HPP_


#include <eda/vhdl/ast/util/namespace_alias.hpp>

#include <eda/vhdl/ast/util/nullary.hpp>
#include <eda/vhdl/ast/scalar_type_definition.hpp>
#include <eda/vhdl/ast/composite_type_definition.hpp>
#include <eda/vhdl/ast/access_type_definition.hpp>
#include <eda/vhdl/ast/file_type_definition.hpp>

#include <boost/spirit/home/x3/support/ast/variant.hpp>


namespace eda { namespace vhdl { namespace ast {


using type_definition = x3::variant<
    ast::nullary,
    ast::scalar_type_definition,
    ast::composite_type_definition,
    ast::access_type_definition,
    ast::file_type_definition
>;


} } } // namespace eda.vhdl.ast


#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_TYPE_DEFINITION_HPP_ */
