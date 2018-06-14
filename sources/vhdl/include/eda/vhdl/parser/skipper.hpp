/*
 * skipper.hpp
 *
 *  Created on: 14.06.2018
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_PARSER_SKIPPER_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_PARSER_SKIPPER_HPP_


#include <eda/vhdl/parser/namespace_alias.hpp>
#include <eda/vhdl/parser/common_types.hpp>

#include <eda/support/boost/spirit_x3.hpp>


/*
 * VHDL Skipper
 */
namespace eda { namespace vhdl { namespace parser {


struct skipper_class;
typedef x3::rule<skipper_class> skipper_type;
BOOST_SPIRIT_DECLARE(skipper_type);


skipper_type const skipper { "skipper" };


using iso8859_1::char_;
using iso8859_1::space;


auto const skipper_def =
      space
    | "--" >> *(char_ - x3::eol) >> x3::eol
    ;


/* get rid off the annoying unused parameter warnings from x3 */
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

BOOST_SPIRIT_DEFINE(skipper);

#pragma GCC diagnostic pop


} } } // namespace eda.vhdl.parser


#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_PARSER_SKIPPER_HPP_ */
