#pragma once

#if defined(_WIN32)
#include <eda/color/detail/api_windows.hpp>
#else
#include <eda/color/detail/api_unix.hpp>
#endif

namespace eda::color::detail {

#if defined(_WIN32)
using api_windows::isatty;
using api_windows::stream_handle;
#else
using api_unix::isatty;
#endif

}  // namespace eda::color::detail
