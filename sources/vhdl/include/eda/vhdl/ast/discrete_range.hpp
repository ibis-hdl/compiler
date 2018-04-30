/*
 * discrete_range.hpp
 *
 *  Created on: 21.05.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_DISCRETE_RANGE_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_DISCRETE_RANGE_HPP_


#include <eda/vhdl/ast/util/variant.hpp>

#include <eda/vhdl/ast/util/nullary.hpp>
#include <eda/vhdl/ast/range.hpp>


namespace eda { namespace vhdl { namespace ast {


struct subtype_indication;


/**
 * Ast node cyclic dependency as:
 *
 * \dot
 * digraph concurrent_statement  {
 *   subtype_indication -> constraint;
 *   constraint -> index_constraint -> discrete_range;
 *   discrete_range -> subtype_indication [ label="forward"];
 * }
 * \enddot
 */
struct discrete_range : variant<
    ast::nullary,
    forward_ast<ast::subtype_indication>,   // discrete_subtype_indication
    ast::range
>
{
    using base_type::base_type;
    using base_type::operator=;
};


} } } // namespace eda.vhdl.ast


#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_DISCRETE_RANGE_HPP_ */
