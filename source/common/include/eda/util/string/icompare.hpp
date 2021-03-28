/*
 * icompare.hpp
 *
 *  Created on: 02.08.2018
 *      Author: olaf
 */

#ifndef SOURCES_COMMON_INCLUDE_EDA_UTIL_STRING_ICOMPARE_HPP_
#define SOURCES_COMMON_INCLUDE_EDA_UTIL_STRING_ICOMPARE_HPP_

#include <algorithm>
#include <cctype>
#include <cstring>
#include <string>
#include <string_view>

namespace eda {
namespace util {

/* \see [Case insensitive sorting of an array of strings](
 *       https://stackoverflow.com/questions/33379846/case-insensitive-sorting-of-an-array-of-strings)
 */
static inline bool icompare_less(std::string_view lhs, std::string_view rhs)
{
    // clang-format off
    auto const result = std::mismatch(lhs.cbegin(), lhs.cend(), rhs.cbegin(), rhs.cend(),
        [](unsigned char  c1, unsigned char  c2) {
            return std::tolower(c1) == std::tolower(c2);
        });

    return    result.second != rhs.cend()
           && (result.first == lhs.cend()
           || std::tolower(*result.first) < std::tolower(*result.second));
    // clang-format on
}

/**
 * case in-sensitive compare
 *
 * \return Returns true of lhs equals to rhs, otherwise false.
 */
static inline bool icompare(std::string_view lhs, std::string_view rhs)
{
    // clang-format off
    return lhs.size() == rhs.size()
        && std::equal(lhs.begin(), lhs.end(), rhs.begin(),
               [](unsigned char c1, unsigned char c2) {
                   return std::tolower(c1) == std::tolower(c2);
        });
    // clang-format on
}

} // namespace util
} // namespace eda

#endif /* SOURCES_COMMON_INCLUDE_EDA_UTIL_STRING_ICOMPARE_HPP_ */
