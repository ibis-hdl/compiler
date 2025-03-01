//
// Copyright (c) 2017-2025 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-or-later
//

#pragma once

#include <source_location>
#include <string_view>

namespace ibis::util::detail {

[[noreturn]] void assertion_failed_msg(const char* expr, std::string_view message,
                                       std::source_location const& location);

[[noreturn]] void cxx_bug_fatal(std::string_view message, std::source_location const& location =
                                                              std::source_location::current());

}  // namespace ibis::util::detail

using ibis::util::detail::cxx_bug_fatal;

#define cxx_assert(condition, message)                                             \
    ((condition) ? ((void)0)                                                       \
                 : ::ibis::util::detail::assertion_failed_msg(#condition, message, \
                                                              std::source_location::current()))
