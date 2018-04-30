/*
 * entity_specification.hpp
 *
 *  Created on: 16.05.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_ENTITY_SPECIFICATION_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_ENTITY_SPECIFICATION_HPP_


#include <eda/vhdl/ast/util/position_tagged.hpp>

#include <eda/vhdl/ast/entity_name_list.hpp>
#include <eda/vhdl/ast/keyword_token.hpp>


namespace eda { namespace vhdl { namespace ast {


struct entity_specification : position_tagged
{
    ast::entity_name_list       entity_name_list;
    ast::keyword_token          entity_class;
};


} } } // namespace eda.vhdl.ast



#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_ENTITY_SPECIFICATION_HPP_ */
