/*
 * compiler_pop.hpp
 *
 *  Created on: 21.06.2018
 *      Author: olaf
 */

#ifndef SOURCES_COMMON_INCLUDE_EDA_UTILS_COMPILER_POP_HPP_
#define SOURCES_COMMON_INCLUDE_EDA_UTILS_COMPILER_POP_HPP_


/**
 * Pop compiler pragma
 *
 * see [Is using #pragma warning push/pop the right way to temporarily alter warning level?](
 * https://stackoverflow.com/questions/4193476/is-using-pragma-warning-push-pop-the-right-way-to-temporarily-alter-warning-lev)
 */
#if defined(__clang__)
#pragma clang diagnostic pop
#endif

#if defined(__GNUC__) && !defined(__clang__)
#pragma GCC diagnostic pop
#endif

#if defined(_MSC_VER)
#pragma warning(pop)
#endif


#endif /* SOURCES_COMMON_INCLUDE_EDA_UTILS_COMPILER_POP_HPP_ */
