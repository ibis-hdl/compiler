/*
 * attribute_specification.hpp
 *
 *  Created on: 16.05.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_ATTRIBUTE_SPECIFICATION_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_ATTRIBUTE_SPECIFICATION_HPP_


#include <eda/vhdl93/ast/util/namespace_alias.hpp>
#include <eda/vhdl93/ast/position_tagged.hpp>

#include <eda/vhdl93/ast/simple_name.hpp>
#include <eda/vhdl93/ast/entity_specification.hpp>
#include <eda/vhdl93/ast/expression.hpp>


namespace eda { namespace vhdl93 { namespace ast {


struct attribute_specification : position_tagged
{
    ast::simple_name                attribute_designator;
    ast::entity_specification       entity_specification;
    ast::expression                 expression;
};


} } } // namespace eda.vhdl93.ast



#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_ATTRIBUTE_SPECIFICATION_HPP_ */
