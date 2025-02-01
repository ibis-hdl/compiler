//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-or-later
//

#pragma once

#include <string_view>
#include <algorithm>

///
/// @brief Trim leading and trailing spaces from std::string_view
///
/// @see [coliru](https://coliru.stacked-crooked.com/a/5fe15808572bbc52) for lambda
/// @see [coliru](https://coliru.stacked-crooked.com/a/c5d1023bb1dbb8ec) for class
///
/// For historical reasons, old approach (with better handling of whitespaces) shown here:
///
/// @code {.cpp}
/// return std::string_view(
///   x.begin(), std::find_if(x.rbegin(), x.rend(), [](char c) { return !std::isspace(c);
///   }).base());
/// @endcode
///
namespace ibis::util {

inline std::string_view ltrim(std::string_view sv)
{
    static constexpr char space = ' ';
    sv.remove_prefix(std::min(sv.find_first_not_of(space), sv.size()));
    return sv;
}

inline std::string_view rtrim(std::string_view sv)
{
    static constexpr char space = ' ';
    sv.remove_suffix(sv.size() - sv.find_last_not_of(space) - 1);
    return sv;
}

inline std::string_view trim(std::string_view sv)
{
    sv = ltrim(sv);
    sv = rtrim(sv);
    return sv;
}

}  // namespace ibis::util
