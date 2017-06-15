/*
 * optional.hpp
 *
 *  Created on: 11.06.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_UTIL_OPTIONAL_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_UTIL_OPTIONAL_HPP_


#include <boost/optional.hpp>


namespace eda { namespace vhdl93 { namespace ast {


/** convenience alias */
template<typename T>
using optional = boost::optional<T>;


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_UTIL_OPTIONAL_HPP_ */
