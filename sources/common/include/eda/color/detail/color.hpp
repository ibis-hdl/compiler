/*
 * color.hpp
 *
 *  Created on: 09.08.2018
 *      Author: olaf
 */

#ifndef SOURCES_COMMON_INCLUDE_EDA_COLOR_DETAIL_COLOR_HPP_
#define SOURCES_COMMON_INCLUDE_EDA_COLOR_DETAIL_COLOR_HPP_

#include <eda/configuration.hpp>
#include <eda/predef.hpp>

// clang-format off
#if BOOST_OS_WINDOWS && !EDA_ON_WINDOWS_USE_ANSII_COLOR
// not fully C++17 MinGW g++
#  include <eda/compiler/detail/compiler_push.hpp>
#  if defined(__GNUC__) && !defined(__clang__)
#    pragma GCC diagnostic ignored "-Wimplicit-fallthrough"
#  endif
#  include <eda/color/detail/winapi_color.hpp>
//#  warning "Using Windows Console API"
#  include <eda/compiler/detail/compiler_pop.hpp>
#else
#  include <eda/color/detail/ansii_color.hpp>
//#  warning "Use ANSII colors"
#endif
// clang-format on

#include <optional>

namespace eda {
namespace color {

std::optional<color::attribute> text_attr(std::string_view const& name);
std::optional<color::attribute> foreground_attr(std::string_view const& name);
std::optional<color::attribute> background_attr(std::string_view const& name);

} // namespace color
} // namespace eda

#endif /* SOURCES_COMMON_INCLUDE_EDA_COLOR_DETAIL_COLOR_HPP_ */
