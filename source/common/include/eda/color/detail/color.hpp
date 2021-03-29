#pragma once

#include <eda/configuration.hpp>
#include <boost/predef/os/windows.h>

#if BOOST_OS_WINDOWS && !EDA_ON_WINDOWS_USE_ANSII_COLOR
// not fully C++17 MinGW g++-7.3.0
#include <eda/compiler/detail/compiler_push.hpp>
#if defined(__GNUC__) && !defined(__clang__)
#pragma GCC diagnostic ignored "-Wimplicit-fallthrough"
#endif
#include <eda/color/detail/winapi_color.hpp>
//#  warning "Using Windows Console API"
#include <eda/compiler/detail/compiler_pop.hpp>
#else
#include <eda/color/detail/ansii_color.hpp>
//#  warning "Use ANSII colors"
#endif
