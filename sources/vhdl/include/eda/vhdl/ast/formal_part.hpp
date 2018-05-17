/*
 * formal_part.hpp
 *
 *  Created on: 03.06.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_FORMAL_PART_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_FORMAL_PART_HPP_


#include <eda/vhdl/ast/util/position_tagged.hpp>

#include <vector>


namespace eda { namespace vhdl { namespace ast {


struct name;


struct formal_part : position_tagged
{
    std::vector<ast::name>  context_tied_names;
};


} } } // namespace eda.vhdl.ast


#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_FORMAL_PART_HPP_ */
