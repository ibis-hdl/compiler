#pragma once

#include <ibis/configuration.hpp>
#include <boost/predef/os/windows.h>

#if BOOST_OS_WINDOWS && !IBIS_WITH_ANSI_COLOR_ON_WINDOWS
// not fully C++17 MinGW g++-7.3.0
#include <ibis/compiler/detail/compiler_push.hpp>
#if defined(__GNUC__) && !defined(__clang__)
#pragma GCC diagnostic ignored "-Wimplicit-fallthrough"
#endif
#include <ibis/color/detail/winapi_color.hpp>
//#  warning "Using Windows Console API"
#include <ibis/compiler/detail/compiler_pop.hpp>
#else
#include <ibis/color/detail/ansi_color.hpp>
//#  warning "Use ANSI colors"
#endif
