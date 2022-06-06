//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-only
//

#pragma once

// pre C++20 to avoid lint warnings
#if defined(IBIS_HAVE_EXPERIMENTAL_SOURCE_LOCATION)
#include <experimental/source_location>  // IWYU pragma: keep
#endif

#include <string_view>
#include <iostream>

namespace ibis::vhdl::ast::numeric_convert {

namespace detail {

template <typename RangeType, typename RangeFiltType, typename AttributeType>
void trace_report(RangeType const& range, RangeFiltType const& range_f, bool parse_ok,
                  AttributeType attribute, std::string_view file, unsigned line,
                  std::string_view function)
{
    std::cout << file << ":" << line << " " << function << "('" << range << "')"
              << " -> ['" << range_f << "']: " << std::boolalpha << "parse_ok = " << parse_ok
              << ", attribute = " << attribute << '\n';
}

}  // namespace detail

/// FixMe: If we got C++20 standard once here, get rid off the macro stuff which is used only
///        to gather source location. Unfortunately, we will still stick with it since
///        MS VisualStudio doesn't support P1208R6 std::source_location in year [2021](
///        https://docs.microsoft.com/de-de/cpp/overview/visual-cpp-language-conformance?view=msvc-160)
#if defined(IBIS_HAVE_EXPERIMENTAL_SOURCE_LOCATION)
template <typename RangeType, typename RangeFiltType, typename AttributeType>
inline void dbg_trace(RangeType const& range, RangeFiltType const& range_f, bool parse_ok,
                      AttributeType attribute,
                      std::experimental::source_location const& location =
                          std::experimental::source_location::current())
{
    detail::trace_report(range, range_f, parse_ok, attribute, location.file_name(), location.line(),
                         location.function_name());
}
#else
// NOLINTNEXTLINE(cppcoreguidelines-macro-usage)
#define dbg_trace(range, range_f, parse_ok, attribute)                                          \
    ibis::vhdl::ast::numeric_convert::detail::trace_report(range, range_f, parse_ok, attribute, \
                                                           __FILE__, __LINE__, __FUNCTION__)
#endif

}  // namespace ibis::vhdl::ast::numeric_convert
