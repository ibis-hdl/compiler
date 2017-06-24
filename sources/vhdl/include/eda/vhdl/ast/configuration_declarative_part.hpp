/*
 * configuration_declarative_part.hpp
 *
 *  Created on: 21.06.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_CONFIGURATION_DECLARATIVE_PART_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_CONFIGURATION_DECLARATIVE_PART_HPP_


#include <eda/vhdl/ast/util/namespace_alias.hpp>

#include <eda/vhdl/ast/util/nullary.hpp>
#include <eda/vhdl/ast/attribute_specification.hpp>
#include <eda/vhdl/ast/group_declaration.hpp>
#include <vector>

#include <boost/spirit/home/x3/support/ast/variant.hpp>


namespace eda { namespace vhdl { namespace ast {


struct configuration_declarative_item : x3::variant<
    ast::nullary,
    ast::attribute_specification,
    ast::group_declaration
>
{
    using base_type::base_type;
    using base_type::operator=;
};


struct configuration_declarative_part : std::vector<ast::configuration_declarative_item> { };


} } } // namespace eda.vhdl.ast


#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_CONFIGURATION_DECLARATIVE_PART_HPP_ */
