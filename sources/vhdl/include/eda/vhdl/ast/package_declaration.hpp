/*
 * package_declaration.hpp
 *
 *  Created on: 21.06.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_PACKAGE_DECLARATION_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_PACKAGE_DECLARATION_HPP_


#include <eda/vhdl/ast/identifier.hpp>
#include <eda/vhdl/ast/package_declarative_part.hpp>
#include <eda/vhdl/ast/util/namespace_alias.hpp>
#include <eda/vhdl/ast/util/optional.hpp>
#include <eda/vhdl/ast/util/position_tagged.hpp>


namespace eda { namespace vhdl { namespace ast {


struct package_declaration : position_tagged
{
    ast::identifier                     identifier;
    ast::package_declarative_part       declarative_part;
    optional<ast::identifier>           end_label;
};


} } } // namespace eda.vhdl.ast


#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_PACKAGE_DECLARATION_HPP_ */
