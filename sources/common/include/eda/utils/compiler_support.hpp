/*
 * compiler_support.hpp
 *
 *  Created on: 02.04.2017
 *      Author: olaf
 */

#ifndef SOURCES_COMMON_INCLUDE_EDA_UTILS_COMPILER_SUPPORT_HPP_
#define SOURCES_COMMON_INCLUDE_EDA_UTILS_COMPILER_SUPPORT_HPP_


// use __builtin_expect to provide the compiler with branch prediction information
#if defined(EDA_HAVE_BUILTIN_EXPECT)
#define cxx_expect(x)       __builtin_expect(!!(x), 1)
#define cxx_expect_not(x)   __builtin_expect(!!(x), 0)
#else
#define cxx_expect(x)       x
#define cxx_expect_not(x)   x
#endif


#if defined (EDA_HAVE_BUILTIN_UNREACHABLE)
#define cxx_unreachable(message) __builtin_unreachable();
#else
#define cxx_unreachable(message) ((void)0)
#endif


// check on C++17 compiler features
#if defined(__has_cpp_attribute)
#if     __has_cpp_attribute(fallthrough)
#define     FALLTHROUGH [[fallthrough]]
#elif     __has_cpp_attribute(clang::fallthrough)
#define     FALLTHROUGH [[clang::fallthrough]]
#else
#define FALLTHROUGH        // [[fallthrough]]
#endif
#else
#define FALLTHROUGH        // [[fallthrough]]
#endif


#endif /* SOURCES_COMMON_INCLUDE_EDA_UTILS_COMPILER_SUPPORT_HPP_ */
