/*
 * context_item.hpp
 *
 *  Created on: 17.06.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_CONTEXT_ITEM_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_CONTEXT_ITEM_HPP_


#include <eda/vhdl93/ast/util/namespace_alias.hpp>

#include <eda/vhdl93/ast/util/nullary.hpp>
#include <eda/vhdl93/ast/library_clause.hpp>
#include <eda/vhdl93/ast/use_clause.hpp>

#include <boost/spirit/home/x3/support/ast/variant.hpp>


namespace eda { namespace vhdl93 { namespace ast {


struct context_item : x3::variant<
    ast::nullary,
    ast::library_clause,
    ast::use_clause
>
{
    using base_type::base_type;
    using base_type::operator=;
};


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_CONTEXT_ITEM_HPP_ */
