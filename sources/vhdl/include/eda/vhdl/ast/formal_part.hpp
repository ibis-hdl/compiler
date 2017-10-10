/*
 * formal_part.hpp
 *
 *  Created on: 03.06.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_FORMAL_PART_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_FORMAL_PART_HPP_


#include <boost/spirit/home/x3/support/ast/variant.hpp>
#include <eda/vhdl/ast/formal_designator.hpp>
#include <eda/vhdl/ast/name.hpp>
#include <eda/vhdl/ast/util/namespace_alias.hpp>


namespace eda { namespace vhdl { namespace ast {


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


} } } // namespace eda.vhdl.ast


#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_FORMAL_PART_HPP_ */