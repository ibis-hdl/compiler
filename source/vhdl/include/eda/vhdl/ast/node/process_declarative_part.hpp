/*
 * process_declarative_part.hpp
 *
 *  Created on: 17.06.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_PROCESS_DECLARATIVE_PART_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_PROCESS_DECLARATIVE_PART_HPP_


#include <eda/vhdl/ast/util/variant.hpp>

#include <eda/vhdl/ast/util/nullary.hpp>
#include <eda/vhdl/ast/node/alias_declaration.hpp>
#include <eda/vhdl/ast/node/attribute_declaration.hpp>
#include <eda/vhdl/ast/node/attribute_specification.hpp>
#include <eda/vhdl/ast/node/constant_declaration.hpp>
#include <eda/vhdl/ast/node/file_declaration.hpp>
#include <eda/vhdl/ast/node/group_declaration.hpp>
#include <eda/vhdl/ast/node/group_template_declaration.hpp>
#include <eda/vhdl/ast/node/subprogram_body.hpp>
#include <eda/vhdl/ast/node/subprogram_declaration.hpp>
#include <eda/vhdl/ast/node/subtype_declaration.hpp>
#include <eda/vhdl/ast/node/type_declaration.hpp>
#include <eda/vhdl/ast/node/use_clause.hpp>
#include <eda/vhdl/ast/node/variable_declaration.hpp>
#include <vector>


namespace eda { namespace vhdl { namespace ast {


using process_declarative_item = variant<
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
>;


struct process_declarative_part : std::vector<ast::process_declarative_item> { };


} } } // namespace eda.vhdl.ast



#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_PROCESS_DECLARATIVE_PART_HPP_ */
