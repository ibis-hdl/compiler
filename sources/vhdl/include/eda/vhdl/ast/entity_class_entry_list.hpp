/*
 * entity_class_entry_list.hpp
 *
 *  Created on: 17.06.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_ENTITY_CLASS_ENTRY_LIST_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_ENTITY_CLASS_ENTRY_LIST_HPP_


#include <eda/vhdl/ast/keyword_token.hpp>
#include <vector>


namespace eda { namespace vhdl { namespace ast {


struct entity_class_entry_list : std::vector<ast::keyword_token> { };


} } } // namespace eda.vhdl.ast


#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_ENTITY_CLASS_ENTRY_LIST_HPP_ */
