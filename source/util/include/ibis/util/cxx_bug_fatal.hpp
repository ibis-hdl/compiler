//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-or-later
//

#pragma once

#include <format>
#include <iostream>
#include <cstdlib>

namespace ibis::util::detail {

template <typename CharT>
void assertion_failed_msg(const CharT* expr, const char msg[], const char function[],
                          const char file[], long line)
{
    std::cerr << std::format(
        "\n"
        "****************************************\n"
        "***** Internal Fatal Program Error *****\n"
        "****************************************\n"
        "in file:     {0}:{1}\n"
        "in function: {2}\n"
        "assertion:   {3}\n"
        "message:     {4}\n",
        file,      // {0}
        line,      // {1}
        function,  // {2}
        expr,      // {3}
        msg        // {4}
    );
    std::cerr << std::flush;
}

}  // namespace ibis::util::detail

#if defined(__GNUC__)
#define CXX_FUNCTION_NAME __PRETTY_FUNCTION__
#else
#define CXX_FUNCTION_NAME __FUNCTION__
#endif

#define cxx_assert(condition, message)                         \
    ((condition) ? ((void)0)                                   \
                 : ::ibis::util::detail::assertion_failed_msg( \
                       #condition, message, CXX_FUNCTION_NAME, __FILE__, __LINE__))

#define cxx_bug_fatal(message)  \
    cxx_assert(false, message); \
    std::quick_exit(EXIT_FAILURE);

#define cxx_unreachable_bug_triggered()                   \
    cxx_assert(false, "unreachable code path triggered"); \
    std::quick_exit(EXIT_FAILURE);
