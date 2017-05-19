/*
 * range.hpp
 *
 *  Created on: 19.05.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_RANGE_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_RANGE_HPP_


#include <eda/vhdl93/ast/namespace_alias.hpp>
#include <eda/vhdl93/ast/position_tagged.hpp>

#include <eda/vhdl93/ast/name.hpp>
#include <eda/vhdl93/ast/simple_expression.hpp>
#include <eda/vhdl93/ast/keyword_token.hpp>


namespace eda { namespace vhdl93 { namespace ast {


using range_attribute_name = ast::name;


struct range_expression : position_tagged
{
    ast::simple_expression      lhs;
    ast::keyword_token          direction;
    ast::simple_expression      rhs;
};


struct range : x3::variant<
    range_attribute_name,
    range_expression
>
{
    using base_type::base_type;
    using base_type::operator=;
};

} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_RANGE_HPP_ */
