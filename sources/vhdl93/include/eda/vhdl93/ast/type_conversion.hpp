/*
 * type_conversion.hpp
 *
 *  Created on: 10.06.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_TYPE_CONVERSION_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_TYPE_CONVERSION_HPP_


#include <eda/vhdl93/ast/util/namespace_alias.hpp>
#include <eda/vhdl93/ast/position_tagged.hpp>

#include <eda/vhdl93/ast/type_mark.hpp>
#include <eda/vhdl93/ast/expression.hpp>

#include <string_view>


namespace eda { namespace vhdl93 { namespace ast {


struct type_conversion : position_tagged
{
    ast::type_mark          type_mark;
    ast::expression         expression;
};


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_TYPE_CONVERSION_HPP_ */
