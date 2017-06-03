/*
 * actual_part.hpp
 *
 *  Created on: 03.06.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_ACTUAL_PART_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_ACTUAL_PART_HPP_


#include <eda/vhdl93/ast/namespace_alias.hpp>

#include <eda/vhdl93/ast/name.hpp>
#include <eda/vhdl93/ast/actual_designator.hpp>

#include <boost/spirit/home/x3/support/ast/variant.hpp>


namespace eda { namespace vhdl93 { namespace ast {


struct actual_part_chunk { // helper class
    ast::name               context_tied_name; // function_name | type_mark(name)
    ast::actual_designator  actual_designator;
};


struct actual_part : x3::variant<
    actual_designator,
    actual_part_chunk
>
{
    using base_type::base_type;
    using base_type::operator=;
};


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_ACTUAL_PART_HPP_ */
