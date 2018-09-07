/*
 * api.hpp
 *
 *  Created on: 07.09.2018
 *      Author: olaf
 */

#ifndef SOURCES_COMMON_INCLUDE_EDA_COLOR_DETAIL_API_HPP_
#define SOURCES_COMMON_INCLUDE_EDA_COLOR_DETAIL_API_HPP_

#if defined(_WIN32)
#include <eda/color/detail/api_windows.hpp>
#else
#include <eda/color/detail/api_unix.hpp>
#endif

namespace eda {
namespace color {
namespace detail {

#if defined(_WIN32)
using api_windows::isatty;
using api_windows::stream_handle;
#else
using api_unix::isatty;
#endif

} // namespace detail
} // namespace color
} // namespace eda



#endif /* SOURCES_COMMON_INCLUDE_EDA_COLOR_DETAIL_API_HPP_ */
