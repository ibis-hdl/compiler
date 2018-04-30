/*
 * actual_part.hpp
 *
 *  Created on: 03.06.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_ACTUAL_PART_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_ACTUAL_PART_HPP_


#include <eda/vhdl/ast/util/variant.hpp>

#include <eda/vhdl/ast/actual_designator.hpp>
#include <eda/vhdl/ast/name.hpp>


namespace eda { namespace vhdl { namespace ast {


/* Note, the actual_part is ambiguous here, see BNF, hence using a chunk
 * here to elaborate the context later on. */
struct actual_part_chunk {
    ast::name               context_tied_name; // function_name | type_mark(name)
    ast::actual_designator  actual_designator;
};


struct actual_part : variant<
    actual_designator,
    actual_part_chunk
>
{
    using base_type::base_type;
    using base_type::operator=;
};


} } } // namespace eda.vhdl.ast


#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_ACTUAL_PART_HPP_ */
