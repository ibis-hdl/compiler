/*
 * package_declarative_part.hpp
 *
 *  Created on: 21.06.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_PACKAGE_DECLARATIVE_PART_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_PACKAGE_DECLARATIVE_PART_HPP_


#include <eda/vhdl/ast/util/namespace_alias.hpp>

#include <eda/vhdl/ast/util/nullary.hpp>
#include <eda/vhdl/ast/subprogram_declaration.hpp>
#include <eda/vhdl/ast/type_declaration.hpp>
#include <eda/vhdl/ast/subtype_declaration.hpp>
#include <eda/vhdl/ast/constant_declaration.hpp>
#include <eda/vhdl/ast/signal_declaration.hpp>
#include <eda/vhdl/ast/variable_declaration.hpp>
#include <eda/vhdl/ast/file_declaration.hpp>
#include <eda/vhdl/ast/alias_declaration.hpp>
#include <eda/vhdl/ast/component_declaration.hpp>
#include <eda/vhdl/ast/attribute_declaration.hpp>
#include <eda/vhdl/ast/attribute_specification.hpp>
#include <eda/vhdl/ast/disconnection_specification.hpp>
#include <eda/vhdl/ast/use_clause.hpp>
#include <eda/vhdl/ast/group_template_declaration.hpp>
#include <eda/vhdl/ast/group_declaration.hpp>
#include <vector>

#include <boost/spirit/home/x3/support/ast/variant.hpp>


namespace eda { namespace vhdl { namespace ast {


struct package_declarative_item : x3::variant<
    ast::nullary,
    ast::subprogram_declaration,
    ast::type_declaration,
    ast::subtype_declaration,
    ast::constant_declaration,
    ast::signal_declaration,
    ast::variable_declaration,  // shared_variable_declaration
    ast::file_declaration,
    ast::alias_declaration,
    ast::component_declaration,
    ast::attribute_declaration,
    ast::attribute_specification,
    ast::disconnection_specification,
    ast::use_clause,
    ast::group_template_declaration,
    ast::group_declaration
>
{
    using base_type::base_type;
    using base_type::operator=;
};


struct package_declarative_part : std::vector<ast::package_declarative_item> { };


} } } // namespace eda.vhdl.ast


#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_PACKAGE_DECLARATIVE_PART_HPP_ */
