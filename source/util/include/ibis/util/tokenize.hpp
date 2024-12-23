//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-or-later
//

#pragma once

#include <string_view>
#include <vector>
#include <cstddef>

namespace ibis::util {

///
/// Tokenize a `std::string_view` by given delimiter into vector
///
/// @param sv The Input to tokenize.
/// @param vector_sv Destination of tokenized string views.
/// @param delimiter The delimiter where to tokenize.
///
/// @see [coliru](https://coliru.stacked-crooked.com/a/0eb51327cb759036)
///
inline void tokenize(std::string_view sv, std::vector<std::string_view>& vector_sv, char delimiter)
{
    std::size_t start = 0;
    std::size_t end = 0;

    while ((start = sv.find_first_not_of(delimiter, end)) != std::string_view::npos) {
        end = sv.find(delimiter, start);
        vector_sv.emplace_back(sv.substr(start, end - start));
    }
}

}  // namespace ibis::util
