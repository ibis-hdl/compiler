/*
 * constraint.hpp
 *
 *  Created on: 20.05.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_CONSTRAINT_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_CONSTRAINT_HPP_


#include <eda/vhdl/ast/util/namespace_alias.hpp>

#include <eda/vhdl/ast/util/nullary.hpp>
#include <eda/vhdl/ast/index_constraint.hpp>
#include <eda/vhdl/ast/range_constraint.hpp>

#include <boost/spirit/home/x3/support/ast/variant.hpp>


namespace eda { namespace vhdl { namespace ast {


struct constraint : x3::variant<
    nullary,
    range_constraint,
    index_constraint
>
{
    using base_type::base_type;
    using base_type::operator=;
};


} } } // namespace eda.vhdl.ast


#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_CONSTRAINT_HPP_ */
