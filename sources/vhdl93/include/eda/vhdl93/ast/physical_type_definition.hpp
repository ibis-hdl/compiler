/*
 * physical_type_definition.hpp
 *
 *  Created on: 09.06.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_PHYSICAL_TYPE_DEFINITION_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_PHYSICAL_TYPE_DEFINITION_HPP_


#include <eda/vhdl93/ast/namespace_alias.hpp>
#include <eda/vhdl93/ast/position_tagged.hpp>

#include <eda/vhdl93/ast/range_constraint.hpp>
#include <eda/vhdl93/ast/base_unit_declaration.hpp>
#include <eda/vhdl93/ast/secondary_unit_declaration.hpp>
#include <eda/vhdl93/ast/simple_name.hpp>
#include <vector>
#include <boost/optional.hpp>


namespace eda { namespace vhdl93 { namespace ast {


struct physical_type_definition : position_tagged
{
    ast::range_constraint                           range_constraint;
    ast::base_unit_declaration                      base_unit_declaration;
    std::vector<ast::secondary_unit_declaration>    secondary_unit_declarations;
    boost::optional<ast::simple_name>               physical_type_simple_name;
};


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_PHYSICAL_TYPE_DEFINITION_HPP_ */
