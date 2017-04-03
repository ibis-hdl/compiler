/*
 * direction.hpp
 *
 *  Created on: 03.04.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_DIRECTION_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_DIRECTION_HPP_


namespace eda { namespace vhdl93 { namespace ast {


struct direction
{
    enum class direction_type { to, downto };
    direction_type          direction;
};


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_DIRECTION_HPP_ */
