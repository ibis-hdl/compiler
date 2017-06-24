/*
 * primary_unit.hpp
 *
 *  Created on: 21.06.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_PRIMARY_UNIT_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_PRIMARY_UNIT_HPP_


#include <eda/vhdl/ast/util/namespace_alias.hpp>

#include <eda/vhdl/ast/util/nullary.hpp>
#include <eda/vhdl/ast/entity_declaration.hpp>
#include <eda/vhdl/ast/configuration_declaration.hpp>
#include <eda/vhdl/ast/package_declaration.hpp>

#include <boost/spirit/home/x3/support/ast/variant.hpp>


namespace eda { namespace vhdl { namespace ast {


struct primary_unit : x3::variant<
    ast::nullary,
    ast::entity_declaration,
    ast::configuration_declaration,
    ast::package_declaration
>
{
    using base_type::base_type;
    using base_type::operator=;
};


} } } // namespace eda.vhdl.ast


#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_PRIMARY_UNIT_HPP_ */
