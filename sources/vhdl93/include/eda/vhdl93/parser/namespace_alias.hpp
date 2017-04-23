/*
 * common.hpp
 *
 *  Created on: 18.04.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_PARSER_NAMESPACE_ALIAS_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_PARSER_NAMESPACE_ALIAS_HPP_


#include <eda/support/boost/namespace_fwd.hpp>



namespace eda { namespace vhdl93 { namespace parser {


// namespace alias
namespace x3 = boost::spirit::x3;

// VHDL char set is iso8859:1
namespace iso8859_1 = boost::spirit::x3::iso8859_1;


} } } // namespace eda.vhdl93.parser



#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_PARSER_NAMESPACE_ALIAS_HPP_ */
