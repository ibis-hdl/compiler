/*
 * package_body.hpp
 *
 *  Created on: 21.06.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_PACKAGE_BODY_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_PACKAGE_BODY_HPP_


#include <eda/vhdl93/ast/util/namespace_alias.hpp>
#include <eda/vhdl93/ast/util/position_tagged.hpp>

#include <eda/vhdl93/ast/identifier.hpp>
#include <eda/vhdl93/ast/package_body_declarative_part.hpp>
#include <eda/vhdl93/ast/util/optional.hpp>


namespace eda { namespace vhdl93 { namespace ast {


struct package_body : position_tagged
{
    ast::identifier                     name;
    ast::package_body_declarative_part  declarative_part;
    optional<ast::identifier>           end_name;
};


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_PACKAGE_BODY_HPP_ */
