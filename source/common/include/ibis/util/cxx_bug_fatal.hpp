#pragma once

#include <cstdlib>
#include <iostream>

#include <ibis/compiler/compiler_support.hpp>

namespace ibis::util::detail {

template <typename CharT>
void assertion_failed_msg(const CharT* expr, const char msg[], const char function[],
                          const char file[], long line)
{
    std::cerr << "\n****************************************\n"
              << "***** Internal Fatal Program Error *****\n"
              << "****************************************\n"
              << "assertion:   " << expr << '\n'
              << "what failed: " << msg << '\n'
              << "in function:\n"
              << function << ":\n"
              << file << '(' << line << ")" << std::endl;  // flush

    std::quick_exit(EXIT_FAILURE);
}

}  // namespace ibis::util::detail

#if defined(__GNUC__)
#define CXX_FUNCTION_NAME __PRETTY_FUNCTION__
#else
#define CXX_FUNCTION_NAME __FUNCTION__
#endif

#define cxx_assert(condition, message)                                   \
    (cxx_expect(condition) ? ((void)0)                                   \
                           : ::ibis::util::detail::assertion_failed_msg( \
                                 #condition, message, CXX_FUNCTION_NAME, __FILE__, __LINE__))

#define cxx_bug_fatal(message)  \
    cxx_assert(false, message); \
    cxx_unreachable()

#define cxx_unreachable_bug_triggered()                   \
    cxx_assert(false, "unreachable code path triggered"); \
    cxx_unreachable()
