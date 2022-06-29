//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-or-later
//

#pragma once

#include <algorithm>
#include <cctype>
#include <cstring>
#include <string>
#include <string_view>

namespace ibis::util {

///
/// Case insensitive less compare function for `std::string_view`
///
/// @param lhs left string_view
/// @param rhs right string_view
/// @return true if lhs <= rhs
/// @return false if lhs > rhs
///
/// @see [Case insensitive sorting of an array of strings](
///       https://stackoverflow.com/questions/33379846/case-insensitive-sorting-of-an-array-of-strings)
///
inline bool icompare_less(std::string_view lhs, std::string_view rhs)
{
    // clang-format off
    auto const result = std::mismatch(lhs.cbegin(), lhs.cend(), rhs.cbegin(), rhs.cend(),
        [](unsigned char  c1, unsigned char  c2) {
            return std::tolower(c1) == std::tolower(c2);
        });

    return result.second != rhs.cend()
        && (result.first == lhs.cend() || std::tolower(*result.first) < std::tolower(*result.second));
    // clang-format on
}

///
/// Case insensitive compare function for `std::string_view`
///
/// @param lhs left string_view
/// @param rhs right string_view
/// @return true lhs equals to rhs
/// @return false lhs doesn not equals to rhs
///
inline bool icompare(std::string_view lhs, std::string_view rhs)
{
    // clang-format off
    return lhs.size() == rhs.size()
        && std::equal(lhs.begin(), lhs.end(), rhs.begin(),
               [](unsigned char c1, unsigned char c2) {
                   return std::tolower(c1) == std::tolower(c2);
        });
    // clang-format on
}

}  // namespace ibis::util
