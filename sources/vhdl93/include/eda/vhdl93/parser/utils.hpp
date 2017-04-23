/*
 * utils.hpp
 *
 *  Created on: 18.04.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_PARSER_UTILS_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_PARSER_UTILS_HPP_


#include <boost/spirit/home/x3/nonterminal/rule.hpp>
#include <boost/spirit/home/x3/core/parser.hpp>
#include <eda/vhdl93/parser/namespace_alias.hpp>

/*
 * IEEE Standard VHDL Language Reference Manual
 * (IEEE Std. 1076-1993)
 * http://rti.etf.bg.ac.rs/rti/ri5rvl/tutorial/TUTORIAL/IEEE/HTML/1076_TOC.HTM
 *
 * http://www.amos.eguru-il.com/vhdl_info/vhdl93_syntax.html
 */


namespace eda { namespace vhdl93 { namespace parser {


/*
 * Parser helper
 */
template<typename T>
auto as_type = [](auto p) { return x3::rule<struct _, T>{ "as" } = x3::as_parser(p); };



} } } // namespace eda.vhdl93.parser




#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_PARSER_UTILS_HPP_ */
