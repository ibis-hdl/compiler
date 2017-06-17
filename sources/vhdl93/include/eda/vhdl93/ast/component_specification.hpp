/*
 * component_specification.hpp
 *
 *  Created on: 17.06.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_COMPONENT_SPECIFICATION_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_COMPONENT_SPECIFICATION_HPP_


#include <eda/vhdl93/ast/util/namespace_alias.hpp>
#include <eda/vhdl93/ast/util/position_tagged.hpp>

#include <eda/vhdl93/ast/instantiation_list.hpp>
#include <eda/vhdl93/ast/name.hpp>


namespace eda { namespace vhdl93 { namespace ast {


struct component_specification : position_tagged
{
    ast::instantiation_list         instantiation_list;
    ast::name                       component_name;
};


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_COMPONENT_SPECIFICATION_HPP_ */
