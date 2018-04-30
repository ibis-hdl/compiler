/*
 * type_conversion.hpp
 *
 *  Created on: 10.06.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_TYPE_CONVERSION_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_TYPE_CONVERSION_HPP_


#include <eda/vhdl/ast/util/position_tagged.hpp>

#include <eda/vhdl/ast/name.hpp>
#include <eda/vhdl/ast/expression.hpp>


namespace eda { namespace vhdl { namespace ast {


struct type_conversion : position_tagged
{
    ast::name               type_mark;
    ast::expression         expression;
};


} } } // namespace eda.vhdl.ast


#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_TYPE_CONVERSION_HPP_ */
