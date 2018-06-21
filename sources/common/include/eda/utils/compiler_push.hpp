/*
 * compiler_push.hpp
 *
 *  Created on: 21.06.2018
 *      Author: olaf
 */

#ifndef SOURCES_COMMON_INCLUDE_EDA_UTILS_COMPILER_PUSH_HPP_
#define SOURCES_COMMON_INCLUDE_EDA_UTILS_COMPILER_PUSH_HPP_


/**
 * Push compiler pragma
 *
 * see [Is using #pragma warning push/pop the right way to temporarily alter warning level?](
 * https://stackoverflow.com/questions/4193476/is-using-pragma-warning-push-pop-the-right-way-to-temporarily-alter-warning-lev)
 */
#if defined(__clang__)
#pragma clang diagnostic push
#endif

#if defined(__GNUC__) && !defined(__clang__)
#pragma GCC diagnostic push
#endif

#if defined(_MSC_VER)
#pragma warning(push)
#endif


#endif /* SOURCES_COMMON_INCLUDE_EDA_UTILS_COMPILER_PUSH_HPP_ */
