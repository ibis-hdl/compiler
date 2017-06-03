/*
 * access_type_definition.hpp
 *
 *  Created on: 03.06.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_ACCESS_TYPE_DEFINITION_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_ACCESS_TYPE_DEFINITION_HPP_


#include <eda/vhdl93/ast/namespace_alias.hpp>
#include <eda/vhdl93/ast/position_tagged.hpp>

#include <eda/vhdl93/ast/subtype_indication.hpp>


namespace eda { namespace vhdl93 { namespace ast {


struct access_type_definition : position_tagged
{
    ast::subtype_indication     subtype_indication;
};


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_ACCESS_TYPE_DEFINITION_HPP_ */
