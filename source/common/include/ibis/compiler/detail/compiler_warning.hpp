//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-only
//


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
#pragma GCC diagnostic ignored "-Wdeprecated-copy"
#pragma GCC diagnostic ignored "-Wimplicit-fallthrough"
// see MSVC C4146
#pragma GCC diagnostic ignored "-Wsign-conversion"
#endif

// CLang++ only
#if defined(__clang__)
#pragma GCC diagnostic ignored "-Weverything"
#pragma GCC diagnostic ignored "-Wimplicit-int-float-conversion"
#endif

// G++ only
#if defined(__GNUC__) && !defined(__clang__)
#pragma GCC diagnostic ignored "-Wmaybe-uninitialized"
#pragma GCC diagnostic ignored "-Wpedantic"
#pragma GCC diagnostic ignored "-Wfloat-conversion"
#endif

#if defined(_MSC_VER)
// C4146: unary minus operator applied to unsigned type, result still unsigned
#pragma warning(disable : 4146)
#endif
