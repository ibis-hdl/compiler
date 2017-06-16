/*
 * entity_specification.hpp
 *
 *  Created on: 16.05.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_ENTITY_SPECIFICATION_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_ENTITY_SPECIFICATION_HPP_


#include <eda/vhdl93/ast/util/namespace_alias.hpp>
#include <eda/vhdl93/ast/util/position_tagged.hpp>

#include <eda/vhdl93/ast/entity_name_list.hpp>
#include <eda/vhdl93/ast/keyword_token.hpp>


namespace eda { namespace vhdl93 { namespace ast {



struct entity_specification : position_tagged
{
    ast::entity_name_list       entity_name_list;
    ast::keyword_token          entity_class;
};


} } } // namespace eda.vhdl93.ast



#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_ENTITY_SPECIFICATION_HPP_ */
