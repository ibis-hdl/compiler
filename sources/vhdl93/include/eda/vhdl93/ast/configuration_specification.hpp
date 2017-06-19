/*
 * configuration_specification.hpp
 *
 *  Created on: 19.06.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_CONFIGURATION_SPECIFICATION_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_CONFIGURATION_SPECIFICATION_HPP_


#include <eda/vhdl93/ast/util/namespace_alias.hpp>
#include <eda/vhdl93/ast/util/position_tagged.hpp>

#include <eda/vhdl93/ast/component_specification.hpp>
#include <eda/vhdl93/ast/binding_indication.hpp>


namespace eda { namespace vhdl93 { namespace ast {


struct configuration_specification : position_tagged
{
    ast::component_specification    component_specification;
    ast::binding_indication         binding_indication;
};


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_CONFIGURATION_SPECIFICATION_HPP_ */
