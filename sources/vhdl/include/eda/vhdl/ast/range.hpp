/*
 * range.hpp
 *
 *  Created on: 19.05.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_RANGE_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_RANGE_HPP_


#include <eda/vhdl/ast/util/position_tagged.hpp>
#include <eda/vhdl/ast/util/variant.hpp>

#include <eda/vhdl/ast/attribute_name.hpp>
#include <eda/vhdl/ast/simple_expression.hpp>
#include <eda/vhdl/ast/keyword_token.hpp>


namespace eda { namespace vhdl { namespace ast {


using range_attribute_name = ast::attribute_name;


struct range_expression : position_tagged
{
    ast::simple_expression      lhs;
    ast::keyword_token          direction;
    ast::simple_expression      rhs;
};


struct range : variant<
    range_attribute_name,
    range_expression
>
{
    using base_type::base_type;
    using base_type::operator=;
};

} } } // namespace eda.vhdl.ast


#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_RANGE_HPP_ */
