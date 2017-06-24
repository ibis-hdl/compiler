/*
 * attribute_specification.hpp
 *
 *  Created on: 16.05.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_ATTRIBUTE_SPECIFICATION_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_ATTRIBUTE_SPECIFICATION_HPP_


#include <eda/vhdl/ast/util/namespace_alias.hpp>
#include <eda/vhdl/ast/util/position_tagged.hpp>

#include <eda/vhdl/ast/simple_name.hpp>
#include <eda/vhdl/ast/entity_specification.hpp>
#include <eda/vhdl/ast/expression.hpp>


namespace eda { namespace vhdl { namespace ast {


struct attribute_specification : position_tagged
{
    ast::simple_name                attribute_designator;
    ast::entity_specification       entity_specification;
    ast::expression                 expression;
};


} } } // namespace eda.vhdl.ast



#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_ATTRIBUTE_SPECIFICATION_HPP_ */
