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
#include <eda/vhdl/ast/alias_declaration.hpp>
#include <eda/vhdl/ast/attribute_declaration.hpp>
#include <eda/vhdl/ast/attribute_specification.hpp>
#include <eda/vhdl/ast/component_declaration.hpp>
#include <eda/vhdl/ast/configuration_specification.hpp>
#include <eda/vhdl/ast/constant_declaration.hpp>
#include <eda/vhdl/ast/disconnection_specification.hpp>
#include <eda/vhdl/ast/file_declaration.hpp>
#include <eda/vhdl/ast/group_declaration.hpp>
#include <eda/vhdl/ast/group_template_declaration.hpp>
#include <eda/vhdl/ast/variable_declaration.hpp>
#include <eda/vhdl/ast/signal_declaration.hpp>
#include <eda/vhdl/ast/subprogram_body.hpp>
#include <eda/vhdl/ast/subprogram_declaration.hpp>
#include <eda/vhdl/ast/subtype_declaration.hpp>
#include <eda/vhdl/ast/type_declaration.hpp>
#include <eda/vhdl/ast/use_clause.hpp>
#include <vector>


namespace eda { namespace vhdl { namespace ast {


struct block_declarative_item : variant<
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
>
{
    using base_type::base_type;
    using base_type::operator=;
};


struct block_declarative_part : std::vector<ast::block_declarative_item> { };


} } } // namespace eda.vhdl.ast


#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_BLOCK_DECLARATIVE_PART_HPP_ */
