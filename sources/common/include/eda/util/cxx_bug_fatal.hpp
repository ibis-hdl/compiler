/*
 * cxx_bug_fatal.hpp
 *
 *  Created on: 19.03.2017
 *      Author: olaf
 */

#ifndef INCLUDE_EDA_UTILS_CXX_BUG_FATAL_HPP_
#define INCLUDE_EDA_UTILS_CXX_BUG_FATAL_HPP_

#include <cstdlib>
#include <iostream>

#include <eda/compiler/compiler_support.hpp>

namespace eda {
namespace util {
namespace detail {

template <typename CharT>
void assertion_failed_msg(
    const CharT* expr, const char msg[], const char function[], const char file[], long line)
{
    std::cerr << "\n****************************************\n"
              << "***** Internal Fatal Program Error *****\n"
              << "****************************************\n"
              << "assertion:   " << expr << '\n'
              << "what failed: " << msg << '\n'
              << "in function:\n"
              << function << ":\n"
              << file << '(' << line << ")" << std::endl; // flush

    std_quick_exit(EXIT_FAILURE);
}

} // namespace detail
} // namespace util
} // namespace eda

#if defined(__GNUC__)
#define CXX_FUNCTION_NAME __PRETTY_FUNCTION__
#else
#define CXX_FUNCTION_NAME __FUNCTION__
#endif

#define cxx_assert(condition, message)                                                             \
    (cxx_expect(condition) ? ((void)0)                                                             \
                           : ::eda::util::detail::assertion_failed_msg(                            \
                                 #condition, message, CXX_FUNCTION_NAME, __FILE__, __LINE__))

#define cxx_bug_fatal(message)                                                                     \
    cxx_assert(false, message);                                                                    \
    cxx_unreachable(message);

#define cxx_unreachable_bug_triggered()                                                            \
    cxx_assert(false, "unreachable code path triggered");                                          \
    cxx_unreachable();

#endif /* INCLUDE_EDA_UTILS_CXX_BUG_FATAL_HPP_ */
