/*
 * instantiated_unit.hpp
 *
 *  Created on: 19.06.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_INSTANTIATED_UNIT_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_INSTANTIATED_UNIT_HPP_


#include <eda/vhdl93/ast/util/namespace_alias.hpp>
#include <eda/vhdl93/ast/util/position_tagged.hpp>

#include <eda/vhdl93/ast/name.hpp>
#include <eda/vhdl93/ast/identifier.hpp>
#include <eda/vhdl93/ast/util/optional.hpp>

#include <boost/spirit/home/x3/support/ast/variant.hpp>


namespace eda { namespace vhdl93 { namespace ast {


struct instantiated_unit_chunk
{
    ast::name                   entity_name;
    optional<ast::identifier>   architecture_identifier;
};


struct instantiated_unit : x3::variant<
    ast::nullary,
    ast::name,  // {component, configuration}_name
    ast::instantiated_unit_chunk
>
{
    using base_type::base_type;
    using base_type::operator=;
};


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_INSTANTIATED_UNIT_HPP_ */
