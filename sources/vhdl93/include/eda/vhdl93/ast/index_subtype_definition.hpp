/*
 * index_subtype_definition.hpp
 *
 *  Created on: 09.06.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_INDEX_SUBTYPE_DEFINITION_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_INDEX_SUBTYPE_DEFINITION_HPP_


#include <eda/vhdl93/ast/util/namespace_alias.hpp>

#include <eda/vhdl93/ast/type_mark.hpp>


namespace eda { namespace vhdl93 { namespace ast {


struct index_subtype_definition : position_tagged
{
    ast::type_mark          type_mark;
};


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_INDEX_SUBTYPE_DEFINITION_HPP_ */
