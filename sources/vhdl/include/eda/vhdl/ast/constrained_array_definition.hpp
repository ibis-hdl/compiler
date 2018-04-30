/*
 * constrained_array_definition.hpp
 *
 *  Created on: 09.06.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_CONSTRAINED_ARRAY_DEFINITION_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_CONSTRAINED_ARRAY_DEFINITION_HPP_


#include <eda/vhdl/ast/util/position_tagged.hpp>

#include <eda/vhdl/ast/index_constraint.hpp>
#include <eda/vhdl/ast/subtype_indication.hpp>


namespace eda { namespace vhdl { namespace ast {


struct constrained_array_definition : position_tagged
{
    ast::index_constraint           index_constraint;
    ast::subtype_indication         element_subtype_indication;
};


} } } // namespace eda.vhdl.ast


#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_CONSTRAINED_ARRAY_DEFINITION_HPP_ */
