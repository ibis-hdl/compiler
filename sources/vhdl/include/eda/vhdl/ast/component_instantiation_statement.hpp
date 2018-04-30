/*
 * component_instantiation_statement.hpp
 *
 *  Created on: 20.06.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_COMPONENT_INSTANTIATION_STATEMENT_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_COMPONENT_INSTANTIATION_STATEMENT_HPP_


#include <eda/vhdl/ast/util/position_tagged.hpp>

#include <eda/vhdl/ast/label.hpp>
#include <eda/vhdl/ast/instantiated_unit.hpp>
#include <eda/vhdl/ast/generic_map_aspect.hpp>
#include <eda/vhdl/ast/port_map_aspect.hpp>
#include <eda/vhdl/ast/util/optional.hpp>
#include <vector>


namespace eda { namespace vhdl { namespace ast {


struct component_instantiation_statement : position_tagged
{
    optional<ast::label>                label;
    ast::instantiated_unit              instantiated_unit;
    optional<ast::generic_map_aspect>   generic_map_aspect;
    optional<ast::port_map_aspect>      port_map_aspect;
};


} } } // namespace eda.vhdl.ast


#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_COMPONENT_INSTANTIATION_STATEMENT_HPP_ */
