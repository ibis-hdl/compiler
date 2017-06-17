/*
 * declaration.hpp
 *
 *  Created on: 17.06.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_DECLARATION_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_DECLARATION_HPP_


#include <eda/vhdl93/ast/util/namespace_alias.hpp>

#include <eda/vhdl93/ast/util/nullary.hpp>
#include <eda/vhdl93/ast/alias_declaration.hpp>
#include <eda/vhdl93/ast/attribute_declaration.hpp>
#include <eda/vhdl93/ast/component_declaration.hpp>
//#include <eda/vhdl93/ast/configuration_declaration.hpp>
//#include <eda/vhdl93/ast/entity_declaration.hpp>
//#include <eda/vhdl93/ast/group_declaration.hpp>
//#include <eda/vhdl93/ast/group_template_declaration.hpp>
#include <eda/vhdl93/ast/interface_declaration.hpp>
//#include <eda/vhdl93/ast/object_declaration.hpp>
//#include <eda/vhdl93/ast/package_declaration.hpp>
//#include <eda/vhdl93/ast/subprogram_declaration.hpp>
#include <eda/vhdl93/ast/subtype_declaration.hpp>
#include <eda/vhdl93/ast/type_declaration.hpp>

#include <boost/spirit/home/x3/support/ast/variant.hpp>


namespace eda { namespace vhdl93 { namespace ast {


struct declaration : x3::variant<
    nullary,
    alias_declaration,
    attribute_declaration,
    component_declaration,
    //configuration_declaration,
    //entity_declaration,
    //group_declaration,
    //group_template_declaration,
    interface_declaration,
    //object_declaration,
    //package_declaration,
    //subprogram_declaration,
    subtype_declaration,
    type_declaration
>
{
    using base_type::base_type;
    using base_type::operator=;
};


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_DECLARATION_HPP_ */
