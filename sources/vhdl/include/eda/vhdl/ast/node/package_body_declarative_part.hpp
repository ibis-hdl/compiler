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
#include <eda/vhdl/ast/node/subprogram_declaration.hpp>
#include <eda/vhdl/ast/node/subprogram_body.hpp>
#include <eda/vhdl/ast/node/type_declaration.hpp>
#include <eda/vhdl/ast/node/subtype_declaration.hpp>
#include <eda/vhdl/ast/node/constant_declaration.hpp>
#include <eda/vhdl/ast/node/variable_declaration.hpp>
#include <eda/vhdl/ast/node/file_declaration.hpp>
#include <eda/vhdl/ast/node/alias_declaration.hpp>
#include <eda/vhdl/ast/node/use_clause.hpp>
#include <eda/vhdl/ast/node/group_template_declaration.hpp>
#include <eda/vhdl/ast/node/group_declaration.hpp>
#include <vector>


namespace eda { namespace vhdl { namespace ast {


using package_body_declarative_item = variant<
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
>;

using package_body_declarative_part = std::vector<ast::package_body_declarative_item>;


} } } // namespace eda.vhdl.ast


#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_PACKAGE_BODY_DECLARATIVE_PART_HPP_ */