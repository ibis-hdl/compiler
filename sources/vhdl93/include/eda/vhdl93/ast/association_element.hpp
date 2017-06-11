/*
 * association_element.hpp
 *
 *  Created on: 03.06.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_ASSOCIATION_ELEMENT_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_ASSOCIATION_ELEMENT_HPP_


#include <eda/vhdl93/ast/namespace_alias.hpp>

#include <eda/vhdl93/ast/name.hpp>
#include <eda/vhdl93/ast/actual_part.hpp>
#include <eda/vhdl93/ast/formal_part.hpp>
#include <eda/vhdl93/ast/optional.hpp>

#include <boost/spirit/home/x3/support/ast/variant.hpp>


namespace eda { namespace vhdl93 { namespace ast {


struct association_element : position_tagged
{
    optional<ast::formal_part>          formal_part;
    ast::actual_part                    actual_part;
};


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_ASSOCIATION_ELEMENT_HPP_ */
