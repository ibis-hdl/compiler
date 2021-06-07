#pragma once

#include <ibis/platform.hpp>

#if defined(IBIS_BUILD_PLATFORM_WIN32)
#include <ibis/color/detail/platform_windows.hpp>
#else
#include <ibis/color/detail/platform_unix.hpp>
#endif

namespace ibis::color::detail {

#if defined(IBIS_BUILD_PLATFORM_WIN32)
using platform_windows::isatty;
#else
using platform_unix::isatty;
#endif

}  // namespace ibis::color::detail
