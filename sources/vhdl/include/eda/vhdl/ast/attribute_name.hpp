/*
 * attribute_name.hpp
 *
 *  Created on: 14.05.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_ATTRIBUTE_NAME_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_ATTRIBUTE_NAME_HPP_


#include <eda/vhdl/ast/util/position_tagged.hpp>

#include <eda/vhdl/ast/expression.hpp>
#include <eda/vhdl/ast/prefix.hpp>
#include <eda/vhdl/ast/signature.hpp>
#include <eda/vhdl/ast/simple_name.hpp>
#include <eda/vhdl/ast/util/optional.hpp>


namespace eda { namespace vhdl { namespace ast {


struct attribute_name : position_tagged
{
    ast::prefix                         prefix;
    optional<ast::signature>            signature;
    ast::simple_name                    attribute_designator;
    optional<ast::expression>           expression;
};


} } } // namespace eda.vhdl.ast


#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_ATTRIBUTE_NAME_HPP_ */
