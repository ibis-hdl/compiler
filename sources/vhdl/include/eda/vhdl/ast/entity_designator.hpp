/*
 * entity_designator.hpp
 *
 *  Created on: 16.05.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_ENTITY_DESIGNATOR_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_ENTITY_DESIGNATOR_HPP_


#include <eda/vhdl/ast/util/namespace_alias.hpp>
#include <eda/vhdl/ast/util/position_tagged.hpp>

#include <eda/vhdl/ast/entity_tag.hpp>
#include <eda/vhdl/ast/signature.hpp>
#include <eda/vhdl/ast/util/optional.hpp>


namespace eda { namespace vhdl { namespace ast {


struct entity_designator : position_tagged
{
    ast::entity_tag                 entity_tag;
    optional<ast::signature>        signature;
};


} } } // namespace eda.vhdl.ast


#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_ENTITY_DESIGNATOR_HPP_ */
