/*
 * block_declarative_part.hpp
 *
 *  Created on: 19.06.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_BLOCK_DECLARATIVE_PART_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_BLOCK_DECLARATIVE_PART_HPP_


#include <eda/vhdl/ast/util/variant.hpp>

#include <eda/vhdl/ast/util/nullary.hpp>
#include <eda/vhdl/ast/node/alias_declaration.hpp>
#include <eda/vhdl/ast/node/attribute_declaration.hpp>
#include <eda/vhdl/ast/node/attribute_specification.hpp>
#include <eda/vhdl/ast/node/component_declaration.hpp>
#include <eda/vhdl/ast/node/configuration_specification.hpp>
#include <eda/vhdl/ast/node/constant_declaration.hpp>
#include <eda/vhdl/ast/node/disconnection_specification.hpp>
#include <eda/vhdl/ast/node/file_declaration.hpp>
#include <eda/vhdl/ast/node/group_declaration.hpp>
#include <eda/vhdl/ast/node/group_template_declaration.hpp>
#include <eda/vhdl/ast/node/variable_declaration.hpp>
#include <eda/vhdl/ast/node/signal_declaration.hpp>
#include <eda/vhdl/ast/node/subprogram_body.hpp>
#include <eda/vhdl/ast/node/subprogram_declaration.hpp>
#include <eda/vhdl/ast/node/subtype_declaration.hpp>
#include <eda/vhdl/ast/node/type_declaration.hpp>
#include <eda/vhdl/ast/node/use_clause.hpp>
#include <vector>


namespace eda { namespace vhdl { namespace ast {


using block_declarative_item = variant<
    ast::nullary,
    ast::alias_declaration,
    ast::attribute_declaration,
    ast::attribute_specification,
    ast::component_declaration,
    ast::configuration_specification,
    ast::constant_declaration,
    ast::disconnection_specification,
    ast::file_declaration,
    ast::group_declaration,
    ast::group_template_declaration,
    ast::variable_declaration,   // shared_variable_declaration
    ast::signal_declaration,
    ast::subprogram_body,
    ast::subprogram_declaration,
    ast::subtype_declaration,
    ast::type_declaration,
    ast::use_clause
>;


using block_declarative_part = std::vector<ast::block_declarative_item>;


} } } // namespace eda.vhdl.ast


#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_BLOCK_DECLARATIVE_PART_HPP_ */
