/*
 * actual_designator.hpp
 *
 *  Created on: 03.06.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_ACTUAL_DESIGNATOR_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_ACTUAL_DESIGNATOR_HPP_


#include <eda/vhdl/ast/util/variant.hpp>

#include <eda/vhdl/ast/util/nullary.hpp>
#include <eda/vhdl/ast/node/expression.hpp>
#include <eda/vhdl/ast/node/keyword_token.hpp>


namespace eda { namespace vhdl { namespace ast {


// actual_designator ::=                                             [§ 4.3.2.2]
//       expression
//     | signal_name
//     | variable_name
//     | file_name
//     | open

struct actual_designator : variant<
    nullary,
    expression,             // also for {signal,variable,file}_name
    ast::keyword_token      // OPEN
>
{
    using base_type::base_type;
    using base_type::operator=;
};


} } } // namespace eda.vhdl.ast


#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_ACTUAL_DESIGNATOR_HPP_ */
