/*
 * constraint.hpp
 *
 *  Created on: 20.05.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_CONSTRAINT_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_CONSTRAINT_HPP_


#include <eda/vhdl93/ast/util/namespace_alias.hpp>

#include <eda/vhdl93/ast/util/nullary.hpp>
#include <eda/vhdl93/ast/index_constraint.hpp>
#include <eda/vhdl93/ast/range_constraint.hpp>

#include <boost/spirit/home/x3/support/ast/variant.hpp>


namespace eda { namespace vhdl93 { namespace ast {


struct constraint : x3::variant<
    nullary,
    range_constraint,
    index_constraint
>
{
    using base_type::base_type;
    using base_type::operator=;
};


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_CONSTRAINT_HPP_ */
