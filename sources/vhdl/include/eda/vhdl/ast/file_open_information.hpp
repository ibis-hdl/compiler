/*
 * file_open_information.hpp
 *
 *  Created on: 07.06.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_FILE_OPEN_INFORMATION_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_FILE_OPEN_INFORMATION_HPP_


#include <eda/vhdl/ast/expression.hpp>
#include <eda/vhdl/ast/file_logical_name.hpp>
#include <eda/vhdl/ast/util/namespace_alias.hpp>
#include <eda/vhdl/ast/util/optional.hpp>
#include <eda/vhdl/ast/util/position_tagged.hpp>
#include <vector>


namespace eda { namespace vhdl { namespace ast {


struct file_open_information : position_tagged
{
    optional<ast::expression>           file_open_kind_expression;
    ast::file_logical_name              file_logical_name; // type: string_expression
};


} } } // namespace eda.vhdl.ast


#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_FILE_OPEN_INFORMATION_HPP_ */
