/*
 * common.hpp
 *
 *  Created on: 18.04.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_PARSER_COMMON_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_PARSER_COMMON_HPP_


namespace boost {

    namespace spirit { namespace x3 {

         namespace iso8859_1 { }

    } }  // namespace spirit.x3

} // namespace boost



namespace eda { namespace vhdl93 { namespace parser {


// namespace alias
namespace x3 = boost::spirit::x3;

// VHDL char set is iso8859:1
namespace iso8859_1 = boost::spirit::x3::iso8859_1;


} } } // namespace eda.vhdl93.parser



#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_PARSER_COMMON_HPP_ */
