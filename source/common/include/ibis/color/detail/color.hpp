#pragma once

#include <ibis/platform.hpp>

#if defined(IBIS_BUILD_PLATFORM_WIN32)
// not fully C++17 MinGW g++-7.3.0
// #  include <ibis/compiler/detail/compiler_push.hpp>
// #  if defined(__GNUC__) && !defined(__clang__)
// #    pragma GCC diagnostic ignored "-Wimplicit-fallthrough"
// #  endif
#include <ibis/color/detail/winapi_printer.hpp>
// #  include <ibis/compiler/detail/compiler_pop.hpp>
#else
#include <ibis/color/detail/ansi_esc_printer.hpp>
#endif
