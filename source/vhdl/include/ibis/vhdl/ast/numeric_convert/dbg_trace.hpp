//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-or-later
//

#pragma once

#include <source_location>  // IWYU pragma: keep
#include <format>
#include <string_view>
#include <iostream>

namespace ibis::vhdl::ast::numeric_convert {

namespace detail {

template <typename RangeType, typename RangeFiltType, typename AttributeType>
void trace_report(RangeType const& range, RangeFiltType const& range_f, bool parse_ok,
                  AttributeType attribute, std::string_view file, unsigned line,
                  std::string_view function)
{
    std::cout << std::format("{0}:{1} {2}('{3}') -> '{4}' => attr='{5}' (parse_ok={6})\n",
                             file,       // {0}
                             line,       // {1}
                             function,   // {2}
                             range,      // {3}
                             range_f,    // {4}
                             attribute,  // {5}
                             parse_ok    // {6}
    );
}

}  // namespace detail

template <typename RangeType, typename RangeFiltType, typename AttributeType>
inline void dbg_trace(RangeType const& range, RangeFiltType const& range_f, bool parse_ok,
                      AttributeType attribute,
                      std::source_location const& location = std::source_location::current())
{
    detail::trace_report(range, range_f, parse_ok, attribute, location.file_name(), location.line(),
                         location.function_name());
}

}  // namespace ibis::vhdl::ast::numeric_convert
