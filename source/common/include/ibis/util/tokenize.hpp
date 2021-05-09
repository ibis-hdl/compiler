#pragma once

#include <string_view>
#include <vector>

namespace ibis::util {

///
/// @brief Tokenize a `std::string_view` by given delimiter into vector
///
/// @param sv The Input to tokenize.
/// @param vector_sv Destination of tokenized string views.
/// @param delimiter The delimiter where to tokenize.
///
/// @see [coliru](https://coliru.stacked-crooked.com/a/0eb51327cb759036)
///
void tokenize(std::string_view sv, std::vector<std::string_view>& vector_sv, char delimiter)
{
    std::size_t start = 0;
    std::size_t end = 0;

    while ((start = sv.find_first_not_of(delimiter, end)) != std::string_view::npos) {
        end = sv.find(delimiter, start);
        vector_sv.emplace_back(sv.substr(start, end - start));
    }
}

}  // namespace ibis::util
