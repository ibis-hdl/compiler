/*
 * association_list.hpp
 *
 *  Created on: 03.06.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_ASSOCIATION_LIST_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_ASSOCIATION_LIST_HPP_


#include <eda/vhdl93/ast/util/namespace_alias.hpp>

#include <eda/vhdl93/ast/association_element.hpp>
#include <vector>


namespace eda { namespace vhdl93 { namespace ast {


struct association_list : std::vector<association_element> { };


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_ASSOCIATION_LIST_HPP_ */
