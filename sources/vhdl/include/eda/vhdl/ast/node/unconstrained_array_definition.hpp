/*
 * unconstrained_array_definition.hpp
 *
 *  Created on: 09.06.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_UNCONSTRAINED_ARRAY_DEFINITION_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_UNCONSTRAINED_ARRAY_DEFINITION_HPP_


#include <eda/vhdl/ast/util/position_tagged.hpp>

#include <eda/vhdl/ast/node/index_subtype_definition.hpp>
#include <eda/vhdl/ast/node/subtype_indication.hpp>
#include <vector>


namespace eda { namespace vhdl { namespace ast {


struct unconstrained_array_definition : position_tagged
{
    std::vector<ast::index_subtype_definition>  index_subtype_definitions;
    ast::subtype_indication                     element_subtype_indication;
};


} } } // namespace eda.vhdl.ast


#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_UNCONSTRAINED_ARRAY_DEFINITION_HPP_ */
