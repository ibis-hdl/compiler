/*
 * composite_type_definition.hpp
 *
 *  Created on: 09.06.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_COMPOSITE_TYPE_DEFINITION_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_COMPOSITE_TYPE_DEFINITION_HPP_


#include <eda/vhdl/ast/util/variant.hpp>

#include <eda/vhdl/ast/util/nullary.hpp>
#include <eda/vhdl/ast/array_type_definition.hpp>
#include <eda/vhdl/ast/record_type_definition.hpp>


namespace eda { namespace vhdl { namespace ast {


struct composite_type_definition : variant<
    nullary,
    array_type_definition,
    record_type_definition
>
{
    using base_type::base_type;
    using base_type::operator=;
};


} } } // namespace eda.vhdl.ast


#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_COMPOSITE_TYPE_DEFINITION_HPP_ */
