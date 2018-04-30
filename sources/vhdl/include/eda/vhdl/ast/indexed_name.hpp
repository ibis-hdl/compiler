/*
 * indexed_name.hpp
 *
 *  Created on: 12.05.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_INDEXED_NAME_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_INDEXED_NAME_HPP_


#include <eda/vhdl/ast/util/position_tagged.hpp>

#include <eda/vhdl/ast/prefix.hpp>
#include <eda/vhdl/ast/expression.hpp>
#include <vector>


namespace eda { namespace vhdl { namespace ast {


struct expression;      // forward due to cyclic dependency; FixMe: for convince??


struct indexed_name : position_tagged
{
    ast::prefix                     prefix;
    std::vector<expression>         expression_list;
};


} } } // namespace eda.vhdl.ast


#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_INDEXED_NAME_HPP_ */
