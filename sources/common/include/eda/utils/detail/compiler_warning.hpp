/*
 * compiler_warning.hpp
 *
 *  Created on: 21.06.2018
 *      Author: olaf
 */

/**
 * Compiler Warning disabled for 3rd party sources
 *
 * see [Is using #pragma warning push/pop the right way to temporarily alter warning level?](
 * https://stackoverflow.com/questions/4193476/is-using-pragma-warning-push-pop-the-right-way-to-temporarily-alter-warning-lev)
 */
#if defined(__clang__)
#pragma clang diagnostic ignored "-Wunused-parameter"
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
#pragma clang diagnostic ignored "-Wimplicit-fallthrough"
#endif

#if defined(__GNUC__) && !defined(__clang__)
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#pragma GCC diagnostic ignored "-Wimplicit-fallthrough"
#pragma GCC diagnostic ignored "-Wmaybe-uninitialized"
#endif

#if defined(_MSC_VER)
// ...
#endif
