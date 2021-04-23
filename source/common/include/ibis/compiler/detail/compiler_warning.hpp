//
// Compiler Warning disabled for 3rd party sources
//
// see [Is using #pragma warning push/pop the right way to temporarily alter warning level?](
// https://stackoverflow.com/questions/4193476/is-using-pragma-warning-push-pop-the-right-way-to-temporarily-alter-warning-lev)
//
// Note: intentionally no header guard / pragma once

#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#pragma GCC diagnostic ignored "-Wimplicit-fallthrough"
#endif

// CLang++ only
#if defined(__clang__)
#pragma GCC diagnostic ignored "-Weverything"
#endif

// G++ only
#if defined(__GNUC__) && !defined(__clang__)
#pragma GCC diagnostic ignored "-Wmaybe-uninitialized"
#endif

#if defined(_MSC_VER)
// ...
#endif
