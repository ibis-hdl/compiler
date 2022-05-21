#pragma once

#include <ibis/compiler/warnings_off.hpp>  // [-Wsign-conversion]
#include <boost/spirit/home/x3.hpp>
#include <ibis/compiler/warnings_on.hpp>

#include <ibis/namespace_alias.hpp>

//
// VHDL Skipper
//
namespace ibis::vhdl::parser {

struct skipper_class;
using skipper_type = x3::rule<skipper_class>;

#if !defined(DOXYGEN_DOCUMENTATION_BUILD)
BOOST_SPIRIT_DECLARE(skipper_type)
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

#if !defined(DOXYGEN_DOCUMENTATION_BUILD)
//#include<ibis/compiler/warnings_off.hpp> // IWYU pragma: keep
BOOST_SPIRIT_DEFINE(skipper)
//#include<ibis/compiler/warnings_on.hpp> // IWYU pragma: keep
#endif

}



