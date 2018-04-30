/*
 * package_body_declarative_part.hpp
 *
 *  Created on: 21.06.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_PACKAGE_BODY_DECLARATIVE_PART_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_PACKAGE_BODY_DECLARATIVE_PART_HPP_


#include <eda/vhdl/ast/util/variant.hpp>

#include <eda/vhdl/ast/util/nullary.hpp>
#include <eda/vhdl/ast/subprogram_declaration.hpp>
#include <eda/vhdl/ast/subprogram_body.hpp>
#include <eda/vhdl/ast/type_declaration.hpp>
#include <eda/vhdl/ast/subtype_declaration.hpp>
#include <eda/vhdl/ast/constant_declaration.hpp>
#include <eda/vhdl/ast/variable_declaration.hpp>
#include <eda/vhdl/ast/file_declaration.hpp>
#include <eda/vhdl/ast/alias_declaration.hpp>
#include <eda/vhdl/ast/use_clause.hpp>
#include <eda/vhdl/ast/group_template_declaration.hpp>
#include <eda/vhdl/ast/group_declaration.hpp>
#include <vector>


namespace eda { namespace vhdl { namespace ast {


struct package_body_declarative_item : variant<
    ast::nullary,
    ast::subprogram_declaration,
    ast::subprogram_body,
    ast::type_declaration,
    ast::subtype_declaration,
    ast::constant_declaration,
    ast::variable_declaration,  // shared_variable_declaration
    ast::file_declaration,
    ast::alias_declaration,
    ast::use_clause,
    ast::group_template_declaration,
    ast::group_declaration
>
{
    using base_type::base_type;
    using base_type::operator=;
};


struct package_body_declarative_part : std::vector<ast::configuration_declarative_item> { };


} } } // namespace eda.vhdl.ast


#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_PACKAGE_BODY_DECLARATIVE_PART_HPP_ */
