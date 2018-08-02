/*
 * icompare.hpp
 *
 *  Created on: 02.08.2018
 *      Author: olaf
 */

#ifndef SOURCES_COMMON_INCLUDE_EDA_UTIL_STRING_ICOMPARE_HPP_
#define SOURCES_COMMON_INCLUDE_EDA_UTIL_STRING_ICOMPARE_HPP_

#include <string>
#include <cctype>
#include <algorithm>


namespace eda { namespace util {


/* \see [Case insensitive sorting of an array of strings](
 *       https://stackoverflow.com/questions/33379846/case-insensitive-sorting-of-an-array-of-strings) */
bool icompare_less(std::string const& lhs, std::string const& rhs)
{
    auto const result = std::mismatch(lhs.cbegin(), lhs.cend(), rhs.cbegin(), rhs.cend(),
        [](const auto& lhs, const auto& rhs) {
            return std::tolower(lhs) == std::tolower(rhs);
        });

    return    result.second != rhs.cend()
           && (result.first == lhs.cend()
           || std::tolower(*result.first) < std::tolower(*result.second));
}


} } // namespace eda.util


#endif /* SOURCES_COMMON_INCLUDE_EDA_UTIL_STRING_ICOMPARE_HPP_ */