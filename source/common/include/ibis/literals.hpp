//
// Copyright (c) 2017-2025 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-or-later
//

#pragma once

namespace ibis::literals::memory {

constexpr unsigned long long operator""_KiB(unsigned long long value)
{
    return value *
           1'024U;  // NOLINT(readability-magic-numbers,cppcoreguidelines-avoid-magic-numbers)
}

constexpr unsigned long long operator""_MiB(unsigned long long value)
{
    return value * 1'024U *
           1_KiB;  // NOLINT(readability-magic-numbers,cppcoreguidelines-avoid-magic-numbers)
}

constexpr unsigned long long operator""_GiB(unsigned long long value)
{
    return value * 1'024U *
           1_MiB;  // NOLINT(readability-magic-numbers,cppcoreguidelines-avoid-magic-numbers)
}

}  // namespace ibis::literals