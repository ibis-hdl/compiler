/*
 * instantiated_unit.hpp
 *
 *  Created on: 19.06.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_INSTANTIATED_UNIT_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_INSTANTIATED_UNIT_HPP_


#include <eda/vhdl/ast/util/variant.hpp>

#include <eda/vhdl/ast/name.hpp>
#include <eda/vhdl/ast/identifier.hpp>
#include <eda/vhdl/ast/util/optional.hpp>


namespace eda { namespace vhdl { namespace ast {


struct instantiated_unit_chunk
{
    ast::name                   entity_name;
    optional<ast::identifier>   architecture_identifier;
};


struct instantiated_unit : variant<
    ast::nullary,
    ast::name,  // {component, configuration}_name
    ast::instantiated_unit_chunk
>
{
    using base_type::base_type;
    using base_type::operator=;
};


} } } // namespace eda.vhdl.ast


#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_INSTANTIATED_UNIT_HPP_ */
