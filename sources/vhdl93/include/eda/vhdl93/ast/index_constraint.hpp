/*
 * index_constraint.hpp
 *
 *  Created on: 21.05.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_INDEX_CONSTRAINT_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_INDEX_CONSTRAINT_HPP_


#include <eda/vhdl93/ast/discrete_range.hpp>
#include <vector>


namespace eda { namespace vhdl93 { namespace ast {


struct index_constraint : std::vector<ast::discrete_range> { };


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_INDEX_CONSTRAINT_HPP_ */
