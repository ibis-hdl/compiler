/*
 * delay_mechanism.hpp
 *
 *  Created on: 16.05.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_DELAY_MECHANISM_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_DELAY_MECHANISM_HPP_


#include <eda/vhdl93/ast/namespace_alias.hpp>
#include <eda/vhdl93/ast/position_tagged.hpp>

#include <eda/vhdl93/ast/expression.hpp>
#include <boost/optional.hpp>


namespace eda { namespace vhdl93 { namespace ast {


struct delay_mechanism : position_tagged
{
    enum class delay_type { TRANSPORT_DELAY, INERTIAL_DELAY };

    delay_type                          type;
    boost::optional<ast::expression>    time_expression; // [REJECT ...]
};


} } } // namespace eda.vhdl93.ast



#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_DELAY_MECHANISM_HPP_ */