/*
 * skipper.hpp
 *
 *  Created on: 14.06.2018
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_PARSER_SKIPPER_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_PARSER_SKIPPER_HPP_

#include <eda/support/boost/spirit_x3.hpp>

#include <eda/namespace_alias.hpp>

/*
 * VHDL Skipper
 */
namespace eda {
namespace vhdl {
namespace parser {

struct skipper_class;
using skipper_type = x3::rule<skipper_class>;

#if !defined(DOXYGEN)
BOOST_SPIRIT_DECLARE(skipper_type);
#endif

skipper_type const skipper{ "skipper" };

using iso8859_1::char_;
using iso8859_1::space;

auto const skipper_def =
    // clang-format off
      space
    | "--" >> *(char_ - x3::eol) >> x3::eol
    ;
    // clang-format off

#if !defined(DOXYGEN)
#include <eda/compiler/warnings_off.hpp> // IWYU pragma: keep
BOOST_SPIRIT_DEFINE(skipper)
#include <eda/compiler/warnings_on.hpp> // IWYU pragma: keep
#endif

} } } // namespace eda.vhdl.parser


#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_PARSER_SKIPPER_HPP_ */
