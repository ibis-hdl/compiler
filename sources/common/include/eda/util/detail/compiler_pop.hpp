/*
 * compiler_pop.hpp
 *
 *  Created on: 21.06.2018
 *      Author: olaf
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
