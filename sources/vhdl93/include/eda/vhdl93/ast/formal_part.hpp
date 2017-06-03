/*
 * formal_part.hpp
 *
 *  Created on: 03.06.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_FORMAL_PART_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_FORMAL_PART_HPP_


#include <eda/vhdl93/ast/namespace_alias.hpp>

#include <eda/vhdl93/ast/name.hpp>
#include <eda/vhdl93/ast/formal_designator.hpp>

#include <boost/spirit/home/x3/support/ast/variant.hpp>


namespace eda { namespace vhdl93 { namespace ast {


struct formal_part_chunk { // helper class
    ast::name               context_tied_name; // function_name | type_mark(name)
    ast::formal_designator  formal_designator;
};


struct formal_part : x3::variant<
    formal_designator,
    formal_part_chunk
>
{
    using base_type::base_type;
    using base_type::operator=;
};


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_FORMAL_PART_HPP_ */
