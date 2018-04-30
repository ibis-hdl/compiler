/*
 * allocator.hpp
 *
 *  Created on: 16.06.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_ALLOCATOR_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_ALLOCATOR_HPP_


#include <eda/vhdl/ast/util/variant.hpp>

#include <eda/vhdl/ast/util/nullary.hpp>
#include <eda/vhdl/ast/subtype_indication.hpp>
#include <eda/vhdl/ast/qualified_expression.hpp>


namespace eda { namespace vhdl { namespace ast {


struct allocator : variant<
    ast::nullary,
    ast::subtype_indication,
    ast::qualified_expression
>
{
    using base_type::base_type;
    using base_type::operator=;
};


} } } // namespace eda.vhdl.ast


#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_ALLOCATOR_HPP_ */
