/*
 * configuration_specification.hpp
 *
 *  Created on: 19.06.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_CONFIGURATION_SPECIFICATION_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_CONFIGURATION_SPECIFICATION_HPP_


#include <eda/vhdl/ast/util/position_tagged.hpp>

#include <eda/vhdl/ast/component_specification.hpp>
#include <eda/vhdl/ast/binding_indication.hpp>


namespace eda { namespace vhdl { namespace ast {


struct configuration_specification : position_tagged
{
    ast::component_specification    component_specification;
    ast::binding_indication         binding_indication;
};


} } } // namespace eda.vhdl.ast


#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_CONFIGURATION_SPECIFICATION_HPP_ */
