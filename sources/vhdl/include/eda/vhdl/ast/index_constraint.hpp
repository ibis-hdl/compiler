/*
 * index_constraint.hpp
 *
 *  Created on: 21.05.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_INDEX_CONSTRAINT_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_INDEX_CONSTRAINT_HPP_


#include <eda/vhdl/ast/discrete_range.hpp>
#include <vector>


namespace eda { namespace vhdl { namespace ast {


struct index_constraint : std::vector<ast::discrete_range> { };


} } } // namespace eda.vhdl.ast


#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_INDEX_CONSTRAINT_HPP_ */
