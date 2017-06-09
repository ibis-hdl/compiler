/*
 * entity_aspect.hpp
 *
 *  Created on: 09.06.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_ENTITY_ASPECT_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_ENTITY_ASPECT_HPP_


#include <eda/vhdl93/ast/namespace_alias.hpp>

#include <eda/vhdl93/ast/nullary.hpp>
#include <eda/vhdl93/ast/name.hpp>
#include <eda/vhdl93/ast/subtype_indication.hpp>
#include <eda/vhdl93/ast/keyword_token.hpp>
#include <boost/optional.hpp>

#include <boost/spirit/home/x3/support/ast/variant.hpp>


namespace eda { namespace vhdl93 { namespace ast {


struct entity_aspect_entity : position_tagged
{
    ast::name                           name;
    boost::optional<ast::identifier>    architecture_identifier;
};


struct entity_aspect_configuration : position_tagged
{
    ast::name                           name;
};


struct entity_aspect : x3::variant<
    ast::nullary,
    ast::entity_aspect_entity,
    ast::entity_aspect_configuration,
    ast::keyword_token  // OPEN
>
{
    using base_type::base_type;
    using base_type::operator=;
};


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_ENTITY_ASPECT_HPP_ */
