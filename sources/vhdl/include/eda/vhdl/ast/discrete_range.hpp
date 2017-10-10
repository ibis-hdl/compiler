/*
 * discrete_range.hpp
 *
 *  Created on: 21.05.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_DISCRETE_RANGE_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_DISCRETE_RANGE_HPP_


#include <eda/vhdl/ast/util/namespace_alias.hpp>

#include <eda/vhdl/ast/util/nullary.hpp>
#include <eda/vhdl/ast/range.hpp>
//FORWARD #include <eda/vhdl/ast/subtype_indication.hpp>

#include <boost/spirit/home/x3/support/ast/variant.hpp>


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
struct discrete_range : x3::variant<
    ast::nullary,
    x3::forward_ast<ast::subtype_indication>,   // discrete_subtype_indication
    ast::range
>
{
    using base_type::base_type;
    using base_type::operator=;
};


} } } // namespace eda.vhdl.ast


#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_DISCRETE_RANGE_HPP_ */