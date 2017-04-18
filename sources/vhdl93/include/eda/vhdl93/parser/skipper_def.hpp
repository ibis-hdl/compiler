/*
 * skipper_def.hpp
 *
 *  Created on: 18.04.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_PARSER_SKIPPER_DEF_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_PARSER_SKIPPER_DEF_HPP_


#include <eda/vhdl93/parser/skipper.hpp>

#include <boost/spirit/home/x3.hpp>


/*
 * VHDL Skipper
 */
namespace eda { namespace vhdl93 { namespace parser {


namespace x3 = boost::spirit::x3;

// VHDL char set is iso8859:1
namespace iso8859_1 = boost::spirit::x3::iso8859_1;


using iso8859_1::char_;
using iso8859_1::space;


skipper_type const skipper { "skipper" };


auto const skipper_def =
      space
    | "--" >> *(char_ - x3::eol) >> x3::eol
    ;

BOOST_SPIRIT_DEFINE(skipper)


skipper_type const& skipper_()
{
    return parser::skipper;
}


} } } // namespace eda.vhdl93.parser



#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_PARSER_SKIPPER_DEF_HPP_ */
