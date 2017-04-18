/*
 * skipper.hpp
 *
 *  Created on: 18.04.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_PARSER_SKIPPER_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_PARSER_SKIPPER_HPP_


#include <eda/vhdl93/parser/common.hpp>

#include <boost/spirit/home/x3/nonterminal/rule.hpp>


/*
 * VHDL Skipper
 */
namespace eda { namespace vhdl93 { namespace parser {


struct skipper_class;
typedef x3::rule<skipper_class> skipper_type;


BOOST_SPIRIT_DECLARE(skipper_type);


parser::skipper_type const& skipper_();


} } } // namespace eda.vhdl93.parser


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_PARSER_SKIPPER_HPP_ */
