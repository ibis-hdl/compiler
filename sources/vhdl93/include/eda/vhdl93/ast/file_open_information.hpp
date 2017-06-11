/*
 * file_open_information.hpp
 *
 *  Created on: 07.06.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_FILE_OPEN_INFORMATION_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_FILE_OPEN_INFORMATION_HPP_


#include <eda/vhdl93/ast/namespace_alias.hpp>
#include <eda/vhdl93/ast/position_tagged.hpp>

#include <eda/vhdl93/ast/expression.hpp>
#include <eda/vhdl93/ast/file_logical_name.hpp>
#include <eda/vhdl93/ast/optional.hpp>
#include <vector>


namespace eda { namespace vhdl93 { namespace ast {


struct file_open_information : position_tagged
{
    optional<ast::expression>           file_open_kind_expression;
    ast::file_logical_name              file_logical_name; // type: string_expression
};


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_FILE_OPEN_INFORMATION_HPP_ */
