/*
 * name.hpp
 *
 *  Created on: 05.04.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_NAME_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_NAME_HPP_


#include <eda/vhdl/ast/util/variant.hpp>

#include <eda/vhdl/ast/util/nullary.hpp>
#include <eda/vhdl/ast/indexed_name.hpp>
#include <eda/vhdl/ast/operator_symbol.hpp>
#include <eda/vhdl/ast/selected_name.hpp>
#include <eda/vhdl/ast/simple_name.hpp>


namespace eda { namespace vhdl { namespace ast {


// name ::=
//      simple_name
//    | operator_symbol
//    | selected_name
//    | indexed_name
//    | slice_name
//    | attribute_name
struct name : variant<
    nullary,
    simple_name,
    operator_symbol,
    selected_name
    //indexed_name
    // slice_name
    // attribute_name,
>
{
    using base_type::base_type;
    using base_type::operator=;
};


} } } // namespace eda.vhdl.ast



#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_NAME_HPP_ */
