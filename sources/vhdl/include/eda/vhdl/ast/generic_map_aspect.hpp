/*
 * generic_map_aspect.hpp
 *
 *  Created on: 09.06.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_GENERIC_MAP_ASPECT_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_GENERIC_MAP_ASPECT_HPP_


#include <eda/vhdl/ast/util/namespace_alias.hpp>

#include <eda/vhdl/ast/association_list.hpp>
#include <vector>


namespace eda { namespace vhdl { namespace ast {


struct generic_map_aspect : position_tagged
{
    ast::association_list   association_list;
};


} } } // namespace eda.vhdl.ast


#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_GENERIC_MAP_ASPECT_HPP_ */
