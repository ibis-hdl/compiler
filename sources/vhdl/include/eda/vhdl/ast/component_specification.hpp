/*
 * component_specification.hpp
 *
 *  Created on: 17.06.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_COMPONENT_SPECIFICATION_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_COMPONENT_SPECIFICATION_HPP_


#include <eda/vhdl/ast/util/namespace_alias.hpp>
#include <eda/vhdl/ast/util/position_tagged.hpp>

#include <eda/vhdl/ast/instantiation_list.hpp>
#include <eda/vhdl/ast/name.hpp>


namespace eda { namespace vhdl { namespace ast {


struct component_specification : position_tagged
{
    ast::instantiation_list         instantiation_list;
    ast::name                       component_name;
};


} } } // namespace eda.vhdl.ast


#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_COMPONENT_SPECIFICATION_HPP_ */
