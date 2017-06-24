/*
 * delay_mechanism.hpp
 *
 *  Created on: 16.05.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_DELAY_MECHANISM_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_DELAY_MECHANISM_HPP_


#include <eda/vhdl/ast/util/namespace_alias.hpp>
#include <eda/vhdl/ast/util/position_tagged.hpp>

#include <eda/vhdl/ast/expression.hpp>
#include <eda/vhdl/ast/util/optional.hpp>


namespace eda { namespace vhdl { namespace ast {


struct delay_mechanism : position_tagged
{
    enum class delay_type { TRANSPORT_DELAY, INERTIAL_DELAY };

    optional<ast::expression>           time_expression; // [REJECT ...]
    delay_mechanism::delay_type         type;
};


} } } // namespace eda.vhdl.ast


#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_DELAY_MECHANISM_HPP_ */
