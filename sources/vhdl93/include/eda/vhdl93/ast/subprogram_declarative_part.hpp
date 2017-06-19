/*
 * subprogram_declarative_part.hpp
 *
 *  Created on: 20.06.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_SUBPROGRAM_DECLARATIVE_PART_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_SUBPROGRAM_DECLARATIVE_PART_HPP_


#include <eda/vhdl93/ast/util/namespace_alias.hpp>

#include <eda/vhdl93/ast/util/nullary.hpp>
#include <eda/vhdl93/ast/subprogram_declaration.hpp>
//#include <eda/vhdl93/ast/subprogram_body.hpp>
#include <eda/vhdl93/ast/type_declaration.hpp>
#include <eda/vhdl93/ast/subtype_declaration.hpp>
#include <eda/vhdl93/ast/constant_declaration.hpp>
#include <eda/vhdl93/ast/variable_declaration.hpp>
#include <eda/vhdl93/ast/file_declaration.hpp>
#include <eda/vhdl93/ast/alias_declaration.hpp>
#include <eda/vhdl93/ast/attribute_declaration.hpp>
#include <eda/vhdl93/ast/attribute_specification.hpp>
#include <eda/vhdl93/ast/use_clause.hpp>
#include <eda/vhdl93/ast/group_template_declaration.hpp>
#include <eda/vhdl93/ast/group_declaration.hpp>
#include <vector>

#include <boost/spirit/home/x3/support/ast/variant.hpp>


namespace eda { namespace vhdl93 { namespace ast {


struct subprogram_declarative_item : x3::variant<
    ast::nullary,
    ast::subprogram_declaration,
    //ast::subprogram_body,
    ast::type_declaration,
    ast::subtype_declaration,
    ast::constant_declaration,
    ast::variable_declaration,
    ast::file_declaration,
    ast::alias_declaration,
    ast::attribute_declaration,
    ast::attribute_specification,
    ast::use_clause,
    ast::group_template_declaration,
    ast::group_declaration
>
{
    using base_type::base_type;
    using base_type::operator=;
};


struct subprogram_declarative_part : std::vector<ast::subprogram_declarative_item> { };


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_SUBPROGRAM_DECLARATIVE_PART_HPP_ */
