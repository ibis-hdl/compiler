/*
 * entity_designator.hpp
 *
 *  Created on: 16.05.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_ENTITY_DESIGNATOR_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_ENTITY_DESIGNATOR_HPP_


#include <eda/vhdl93/ast/namespace_alias.hpp>
#include <eda/vhdl93/ast/position_tagged.hpp>

#include <eda/vhdl93/ast/entity_tag.hpp>
#include <eda/vhdl93/ast/signature.hpp>
#include <boost/optional.hpp>


namespace eda { namespace vhdl93 { namespace ast {


struct entity_designator : position_tagged
{
    ast::entity_tag                 entity_tag;
    boost::optional<ast::signature> signature;
};


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_ENTITY_DESIGNATOR_HPP_ */
