/*
 * attribute_name.hpp
 *
 *  Created on: 14.05.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_ATTRIBUTE_NAME_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_ATTRIBUTE_NAME_HPP_


#include <eda/vhdl93/ast/util/namespace_alias.hpp>
#include <eda/vhdl93/ast/position_tagged.hpp>

#include <eda/vhdl93/ast/prefix.hpp>
#include <eda/vhdl93/ast/signature.hpp>
#include <eda/vhdl93/ast/simple_name.hpp>
#include <eda/vhdl93/ast/expression.hpp>
#include <eda/vhdl93/ast/util/optional.hpp>


namespace eda { namespace vhdl93 { namespace ast {


struct attribute_name : position_tagged
{
    ast::prefix                         prefix;
    optional<ast::signature>            signature;
    ast::simple_name                    attribute_designator;
    optional<ast::expression>           expression;
};


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_ATTRIBUTE_NAME_HPP_ */
