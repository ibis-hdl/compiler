/*
 * index_specification.hpp
 *
 *  Created on: 19.06.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_INDEX_SPECIFICATION_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_INDEX_SPECIFICATION_HPP_


#include <eda/vhdl/ast/util/variant.hpp>

#include <eda/vhdl/ast/util/nullary.hpp>
#include <eda/vhdl/ast/node/discrete_range.hpp>
#include <eda/vhdl/ast/node/expression.hpp>


namespace eda { namespace vhdl { namespace ast {


struct index_specification : variant<
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