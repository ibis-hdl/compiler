/*
 * entity_class_entry_list.hpp
 *
 *  Created on: 17.06.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_ENTITY_CLASS_ENTRY_LIST_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_ENTITY_CLASS_ENTRY_LIST_HPP_


#include <eda/vhdl93/ast/util/namespace_alias.hpp>

#include <eda/vhdl93/ast/keyword_token.hpp>
#include <vector>


namespace eda { namespace vhdl93 { namespace ast {


struct entity_class_entry_list : std::vector<ast::keyword_token> { };


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_ENTITY_CLASS_ENTRY_LIST_HPP_ */
