/*
 * physical_type_definition.hpp
 *
 *  Created on: 09.06.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_PHYSICAL_TYPE_DEFINITION_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_PHYSICAL_TYPE_DEFINITION_HPP_


#include <eda/vhdl/ast/util/position_tagged.hpp>

#include <eda/vhdl/ast/primary_unit_declaration.hpp>
#include <eda/vhdl/ast/range_constraint.hpp>
#include <eda/vhdl/ast/secondary_unit_declaration.hpp>
#include <eda/vhdl/ast/simple_name.hpp>
#include <eda/vhdl/ast/util/optional.hpp>
#include <vector>


namespace eda { namespace vhdl { namespace ast {


struct physical_type_definition : position_tagged
{
    ast::range_constraint                           range_constraint;
    ast::primary_unit_declaration                   primary_unit_declaration;
    std::vector<ast::secondary_unit_declaration>    secondary_unit_declarations;
    optional<ast::simple_name>                      physical_type_simple_name;
};


} } } // namespace eda.vhdl.ast


#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_PHYSICAL_TYPE_DEFINITION_HPP_ */
