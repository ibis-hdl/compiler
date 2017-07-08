/*
 * association_list.hpp
 *
 *  Created on: 03.06.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_ASSOCIATION_LIST_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_ASSOCIATION_LIST_HPP_


#include <eda/vhdl/ast/util/namespace_alias.hpp>

#include <eda/vhdl/ast/association_element.hpp>
#include <vector>


namespace eda { namespace vhdl { namespace ast {


struct association_list : std::vector<ast::association_element> { };


} } } // namespace eda.vhdl.ast


#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_ASSOCIATION_LIST_HPP_ */
