/*
 * process_declarative_part.hpp
 *
 *  Created on: 17.06.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_PROCESS_DECLARATIVE_PART_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_PROCESS_DECLARATIVE_PART_HPP_


#include <eda/vhdl93/ast/util/namespace_alias.hpp>

#include <eda/vhdl93/ast/util/nullary.hpp>
#include <eda/vhdl93/ast/alias_declaration.hpp>
#include <eda/vhdl93/ast/attribute_declaration.hpp>
#include <eda/vhdl93/ast/attribute_specification.hpp>
#include <eda/vhdl93/ast/constant_declaration.hpp>
#include <eda/vhdl93/ast/file_declaration.hpp>
#include <eda/vhdl93/ast/group_declaration.hpp>
#include <eda/vhdl93/ast/group_template_declaration.hpp>
#include <eda/vhdl93/ast/subprogram_body.hpp>
#include <eda/vhdl93/ast/subprogram_declaration.hpp>
#include <eda/vhdl93/ast/subtype_declaration.hpp>
#include <eda/vhdl93/ast/type_declaration.hpp>
#include <eda/vhdl93/ast/use_clause.hpp>
#include <eda/vhdl93/ast/variable_declaration.hpp>
#include <vector>

#include <boost/spirit/home/x3/support/ast/variant.hpp>


namespace eda { namespace vhdl93 { namespace ast {


struct process_declarative_item : x3::variant<
    nullary,
    alias_declaration,
    attribute_declaration,
    attribute_specification,
    constant_declaration,
    file_declaration,
    group_declaration,
    group_template_declaration,
    subprogram_body,
    subprogram_declaration,
    subtype_declaration,
    type_declaration,
    use_clause,
    variable_declaration
>
{
    using base_type::base_type;
    using base_type::operator=;
};


struct process_declarative_part : std::vector<ast::process_declarative_item> { };


} } } // namespace eda.vhdl93.ast



#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_PROCESS_DECLARATIVE_PART_HPP_ */
