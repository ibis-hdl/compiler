/*
 * entity_aspect.hpp
 *
 *  Created on: 09.06.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_ENTITY_ASPECT_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_ENTITY_ASPECT_HPP_


#include <boost/spirit/home/x3/support/ast/variant.hpp>
#include <eda/vhdl/ast/keyword_token.hpp>
#include <eda/vhdl/ast/name.hpp>
#include <eda/vhdl/ast/subtype_indication.hpp>
#include <eda/vhdl/ast/util/namespace_alias.hpp>
#include <eda/vhdl/ast/util/nullary.hpp>
#include <eda/vhdl/ast/util/optional.hpp>


namespace eda { namespace vhdl { namespace ast {


struct entity_aspect_entity : position_tagged
{
    ast::name                           name;
    optional<ast::identifier>           architecture_identifier;
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


} } } // namespace eda.vhdl.ast


#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_ENTITY_ASPECT_HPP_ */
