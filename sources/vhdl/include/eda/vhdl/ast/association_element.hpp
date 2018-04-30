/*
 * association_element.hpp
 *
 *  Created on: 03.06.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_ASSOCIATION_ELEMENT_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_ASSOCIATION_ELEMENT_HPP_


#include <eda/vhdl/ast/util/variant.hpp>

#include <eda/vhdl/ast/actual_part.hpp>
#include <eda/vhdl/ast/formal_part.hpp>
#include <eda/vhdl/ast/util/optional.hpp>


namespace eda { namespace vhdl { namespace ast {


struct association_element : position_tagged
{
    optional<ast::formal_part>          formal_part;
    ast::actual_part                    actual_part;
};


} } } // namespace eda.vhdl.ast


#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_ASSOCIATION_ELEMENT_HPP_ */
