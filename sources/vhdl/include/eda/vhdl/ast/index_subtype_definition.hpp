/*
 * index_subtype_definition.hpp
 *
 *  Created on: 09.06.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_INDEX_SUBTYPE_DEFINITION_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_INDEX_SUBTYPE_DEFINITION_HPP_


#include <eda/vhdl/ast/util/position_tagged.hpp>

#include <eda/vhdl/ast/name.hpp>


namespace eda { namespace vhdl { namespace ast {


struct index_subtype_definition : position_tagged
{
    ast::name               type_mark;
};


} } } // namespace eda.vhdl.ast


#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_INDEX_SUBTYPE_DEFINITION_HPP_ */
