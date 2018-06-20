/*
 * entity_declarative_part.hpp
 *
 *  Created on: 17.06.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_ENTITY_DECLARATIVE_PART_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_ENTITY_DECLARATIVE_PART_HPP_


#include <eda/vhdl/ast/util/variant.hpp>

#include <eda/vhdl/ast/util/nullary.hpp>
#include <eda/vhdl/ast/alias_declaration.hpp>
#include <eda/vhdl/ast/attribute_declaration.hpp>
#include <eda/vhdl/ast/attribute_specification.hpp>
#include <eda/vhdl/ast/constant_declaration.hpp>
#include <eda/vhdl/ast/disconnection_specification.hpp>
#include <eda/vhdl/ast/file_declaration.hpp>
#include <eda/vhdl/ast/group_declaration.hpp>
#include <eda/vhdl/ast/group_template_declaration.hpp>
#include <eda/vhdl/ast/signal_declaration.hpp>
#include <eda/vhdl/ast/subprogram_body.hpp>
#include <eda/vhdl/ast/subprogram_declaration.hpp>
#include <eda/vhdl/ast/subtype_declaration.hpp>
#include <eda/vhdl/ast/type_declaration.hpp>
#include <eda/vhdl/ast/use_clause.hpp>
#include <eda/vhdl/ast/variable_declaration.hpp>
#include <vector>


namespace eda { namespace vhdl { namespace ast {


using entity_declarative_item = variant<
    nullary,
    alias_declaration,
    attribute_declaration,
    attribute_specification,
    constant_declaration,
    disconnection_specification,
    file_declaration,
    group_declaration,
    group_template_declaration,
    variable_declaration,   // shared_variable_declaration
    signal_declaration,
    subprogram_body,
    subprogram_declaration,
    subtype_declaration,
    type_declaration,
    use_clause
>;


struct entity_declarative_part : std::vector<ast::entity_declarative_item> { };


} } } // namespace eda.vhdl.ast



#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_ENTITY_DECLARATIVE_PART_HPP_ */
