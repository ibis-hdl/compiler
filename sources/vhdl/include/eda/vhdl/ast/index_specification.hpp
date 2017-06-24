/*
 * index_specification.hpp
 *
 *  Created on: 19.06.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_INDEX_SPECIFICATION_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_INDEX_SPECIFICATION_HPP_


#include <eda/vhdl/ast/util/namespace_alias.hpp>

#include <eda/vhdl/ast/util/nullary.hpp>
#include <eda/vhdl/ast/discrete_range.hpp>
#include <eda/vhdl/ast/expression.hpp>
#include <vector>

#include <boost/spirit/home/x3/support/ast/variant.hpp>


namespace eda { namespace vhdl { namespace ast {


struct index_specification : x3::variant<
    ast::nullary,
    ast::discrete_range,
    ast::expression         // static_expression
>
{
    using base_type::base_type;
    using base_type::operator=;
};


} } } // namespace eda.vhdl.ast


#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_INDEX_SPECIFICATION_HPP_ */
