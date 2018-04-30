/*
 * access_type_definition.hpp
 *
 *  Created on: 03.06.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_ACCESS_TYPE_DEFINITION_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_ACCESS_TYPE_DEFINITION_HPP_


#include <eda/vhdl/ast/util/position_tagged.hpp>

#include <eda/vhdl/ast/subtype_indication.hpp>



namespace eda { namespace vhdl { namespace ast {


struct access_type_definition : position_tagged
{
    ast::subtype_indication     subtype_indication;
};


} } } // namespace eda.vhdl.ast


#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_ACCESS_TYPE_DEFINITION_HPP_ */
