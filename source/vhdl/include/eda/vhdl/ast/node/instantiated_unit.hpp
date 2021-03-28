/*
 * instantiated_unit.hpp
 *
 *  Created on: 19.06.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_INSTANTIATED_UNIT_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_INSTANTIATED_UNIT_HPP_


#include <eda/vhdl/ast/util/variant.hpp>

#include <eda/vhdl/ast/node/name.hpp>
#include <eda/vhdl/ast/node/identifier.hpp>
#include <eda/vhdl/ast/util/optional.hpp>


namespace eda { namespace vhdl { namespace ast {


struct instantiated_unit_component
{
    ast::name                   name;
};

struct instantiated_unit_entity
{
    ast::name                   name;
    optional<ast::identifier>   architecture_identifier;
};

struct instantiated_unit_configuration
{
    ast::name                   name;
};


struct instantiated_unit : variant<
    ast::nullary,
    ast::instantiated_unit_component,
    ast::instantiated_unit_entity,
    ast::instantiated_unit_configuration
>
{
    using base_type::base_type;
    using base_type::operator=;
};


} } } // namespace eda.vhdl.ast


#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_INSTANTIATED_UNIT_HPP_ */
