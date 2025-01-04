//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-or-later
//

#pragma once

#include <format>
#include <source_location>
#include <iostream>
#include <cstdlib>

namespace ibis::util::detail {

template <typename CharT>
void assertion_failed_msg(const CharT* expr, const char msg[], std::source_location const& location)
{
    std::cerr << std::format(
        "\n"
        "*******************************\n"
        "***** Fatal Program Error *****\n"
        "*******************************\n"
        "in file:     {0}:{1}\n"
        "in function: {2}\n"
        "assertion:   {3}\n"
        "message:     {4}\n",
        location.file_name(),      // {0}
        location.line(),           // {1}
        location.function_name(),  // {2}
        expr,                      // {3}
        msg                        // {4}
    );
    std::cerr.flush();
}

}  // namespace ibis::util::detail

#define cxx_assert(condition, message)                                             \
    ((condition) ? ((void)0)                                                       \
                 : ::ibis::util::detail::assertion_failed_msg(#condition, message, \
                                                              std::source_location::current()))

#define cxx_bug_fatal(message)  \
    cxx_assert(false, message); \
    std::quick_exit(EXIT_FAILURE);

#define cxx_unreachable_bug_triggered()                   \
    cxx_assert(false, "unreachable code path triggered"); \
    std::unreachable();                                   \
    std::quick_exit(EXIT_FAILURE);
