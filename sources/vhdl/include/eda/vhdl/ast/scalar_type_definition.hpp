/*
 * scalar_type_definition.hpp
 *
 *  Created on: 09.06.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_SCALAR_TYPE_DEFINITION_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_SCALAR_TYPE_DEFINITION_HPP_


#include <eda/vhdl/ast/util/namespace_alias.hpp>

#include <eda/vhdl/ast/util/nullary.hpp>
#include <eda/vhdl/ast/enumeration_type_definition.hpp>
#include <eda/vhdl/ast/range_constraint.hpp>
#include <eda/vhdl/ast/physical_type_definition.hpp>

#include <boost/spirit/home/x3/support/ast/variant.hpp>


namespace eda { namespace vhdl { namespace ast {


//using integer_type_definition = ast::range_constraint;
//using floating_type_definition = ast::range_constraint;


using scalar_type_definition = x3::variant<
    ast::nullary,
    ast::enumeration_type_definition,
    ast::range_constraint, // {integer,floating}_type_definition
    ast::physical_type_definition
>;


} } } // namespace eda.vhdl.ast


#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_SCALAR_TYPE_DEFINITION_HPP_ */
