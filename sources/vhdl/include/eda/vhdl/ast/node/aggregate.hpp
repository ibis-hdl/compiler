/*
 * aggregate.hpp
 *
 *  Created on: 11.06.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_AGGREGATE_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_AGGREGATE_HPP_


#include <eda/vhdl/ast/node/element_association.hpp>
#include <vector>


namespace eda { namespace vhdl { namespace ast {


struct aggregate : std::vector<ast::element_association> { };


} } } // namespace eda.vhdl.ast


#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_AGGREGATE_HPP_ */