/*
 * compiler_warning.hpp
 *
 *  Created on: 21.06.2018
 *      Author: olaf
 */

#ifndef SOURCES_COMMON_INCLUDE_EDA_UTILS_COMPILER_WARNING_HPP_
#define SOURCES_COMMON_INCLUDE_EDA_UTILS_COMPILER_WARNING_HPP_


/**
 * Compiler Warning
 *
 * see [Is using #pragma warning push/pop the right way to temporarily alter warning level?](
 * https://stackoverflow.com/questions/4193476/is-using-pragma-warning-push-pop-the-right-way-to-temporarily-alter-warning-lev)
 */
#if defined(__GNUC__)
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#endif

#if defined(__GNUC__) && !defined(__clang__)
#pragma GCC diagnostic ignored "-Wmaybe-uninitialized"
#endif

#if defined(_MSC_VER)
// ...
#endif



#endif /* SOURCES_COMMON_INCLUDE_EDA_UTILS_COMPILER_WARNING_HPP_ */
