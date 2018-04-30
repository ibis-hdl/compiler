/*
 * context_item.hpp
 *
 *  Created on: 17.06.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_CONTEXT_ITEM_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_CONTEXT_ITEM_HPP_


#include <eda/vhdl/ast/util/variant.hpp>

#include <eda/vhdl/ast/util/nullary.hpp>
#include <eda/vhdl/ast/library_clause.hpp>
#include <eda/vhdl/ast/use_clause.hpp>


namespace eda { namespace vhdl { namespace ast {


struct context_item : variant<
    ast::nullary,
    ast::library_clause,
    ast::use_clause
>
{
    using base_type::base_type;
    using base_type::operator=;
};


} } } // namespace eda.vhdl.ast


#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_CONTEXT_ITEM_HPP_ */
