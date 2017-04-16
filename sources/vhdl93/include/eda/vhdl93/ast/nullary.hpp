/*
 * nullary.hpp
 *
 *  Created on: 16.04.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_NULLARY_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_NULLARY_HPP_


namespace eda { namespace vhdl93 { namespace ast {


/**
 * helper class to catch an 'empty' variant. C++ variant ensures a never empty
 * guarantee which isn't always desirable.
 */
struct nullary { };


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_NULLARY_HPP_ */
