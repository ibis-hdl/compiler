/*
 * cxx_unreachable.hpp
 *
 *  Created on: 19.03.2017
 *      Author: olaf
 */

#ifndef INCLUDE_EDA_UTILS_CXX_BUG_FATAL_HPP_
#define INCLUDE_EDA_UTILS_CXX_BUG_FATAL_HPP_

#include <cstdlib>
#include <iostream>


// based on ideas from Baptiste Wicht <wichtounet>
// https://github.com/wichtounet/cpp_utils/blob/master/assert.hpp

namespace eda { namespace utils { namespace detail {

template <typename CharT>
void assertion_failed_msg(const CharT* expr, const char* msg, const char* function, const char* file, long line) {
    std::cerr
        << "\n****************************************\n"
        <<   "***** Internal Fatal Program Error *****\n"
        <<   "****************************************\n"
        << "assertion (" << expr << ") failed in "
        << function << ":\n"
        << file << '(' << line << "): " << msg << std::endl;
    std::abort();
}

} } } // namespace eda.utils.detail


// use __builtin_expect to provide the compiler with branch prediction information
#if defined(EDA_HAVE_BUILTIN_EXPECT)
#define cxx_expect(x)       __builtin_expect(!!(x), 1)
#define cxx_expect_not(x)   __builtin_expect(!!(x), 0)
#else
#define cxx_expect(x)       x
#define cxx_expect_not(x)   x
#endif


#define cxx_assert(condition, message) \
    (cxx_expect(condition) \
    ? ((void)0)            \
    : ::eda::utils::detail::assertion_failed_msg(#condition, message, \
       __PRETTY_FUNCTION__, __FILE__, __LINE__))


#if defined (EDA_HAVE_BUILTIN_UNREACHABLE)
#define cxx_bug_fatal(message) \
    cxx_assert(false, message);  \
    __builtin_unreachable();
#else
#error "There is no support for __builtin_unreachable()"
#endif


#endif /* INCLUDE_EDA_UTILS_CXX_BUG_FATAL_HPP_ */
