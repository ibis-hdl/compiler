/*
 * package_declaration.hpp
 *
 *  Created on: 21.06.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_PACKAGE_DECLARATION_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_PACKAGE_DECLARATION_HPP_


#include <eda/vhdl93/ast/util/namespace_alias.hpp>
#include <eda/vhdl93/ast/util/position_tagged.hpp>

#include <eda/vhdl93/ast/identifier.hpp>
#include <eda/vhdl93/ast/package_declarative_part.hpp>
#include <eda/vhdl93/ast/util/optional.hpp>


namespace eda { namespace vhdl93 { namespace ast {


struct package_declaration : position_tagged
{
    ast::identifier                     identifier;
    ast::package_declarative_part       declarative_part;
    optional<ast::identifier>           end_label;
};


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_PACKAGE_DECLARATION_HPP_ */
