/*
 * actual_designator.hpp
 *
 *  Created on: 03.06.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_ACTUAL_DESIGNATOR_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_ACTUAL_DESIGNATOR_HPP_


#include <boost/spirit/home/x3/support/ast/variant.hpp>
#include <eda/vhdl/ast/expression.hpp>
#include <eda/vhdl/ast/keyword_token.hpp>
#include <eda/vhdl/ast/name.hpp>
#include <eda/vhdl/ast/util/namespace_alias.hpp>
#include <eda/vhdl/ast/util/nullary.hpp>


namespace eda { namespace vhdl { namespace ast {


// actual_designator ::=                                             [§ 4.3.2.2]
//       expression
//     | signal_name
//     | variable_name
//     | file_name
//     | open

/* See notes at rule definition */

struct actual_designator : x3::variant<
    nullary,
    name,
    expression,
    ast::keyword_token      // OPEN
>
{
    using base_type::base_type;
    using base_type::operator=;
};


} } } // namespace eda.vhdl.ast


#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_ACTUAL_DESIGNATOR_HPP_ */
