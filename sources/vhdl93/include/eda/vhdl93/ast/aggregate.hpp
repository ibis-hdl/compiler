/*
 * aggregate.hpp
 *
 *  Created on: 11.06.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_AGGREGATE_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_AGGREGATE_HPP_


#include <eda/vhdl93/ast/namespace_alias.hpp>
#include <eda/vhdl93/ast/position_tagged.hpp>

#include <eda/vhdl93/ast/element_association.hpp>
#include <vector>


namespace eda { namespace vhdl93 { namespace ast {


struct aggregate : std::vector<ast::element_association> { };


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_AGGREGATE_HPP_ */
