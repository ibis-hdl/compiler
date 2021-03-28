/*
 * block_configuration.hpp
 *
 *  Created on: 19.06.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_BLOCK_CONFIGURATION_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_BLOCK_CONFIGURATION_HPP_


#include <eda/vhdl/ast/util/position_tagged.hpp>

#include <eda/vhdl/ast/node/block_specification.hpp>
#include <eda/vhdl/ast/node/use_clause.hpp>
#include <eda/vhdl/ast/node/configuration_item.hpp>
#include <vector>


namespace eda { namespace vhdl { namespace ast {


struct block_configuration : position_tagged
{
    ast::block_specification                block_specification;
    std::vector<ast::use_clause>            use_clause_list;
    std::vector<ast::configuration_item>    configuration_item_list;
};


} } } // namespace eda.vhdl.ast


#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_BLOCK_CONFIGURATION_HPP_ */
