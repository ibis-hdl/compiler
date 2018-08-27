/*
 * literal_ellipsis.hpp
 *
 *  Created on: 20.03.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_UTIL_STRING_LITERAL_ELLIPSIS_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_UTIL_STRING_LITERAL_ELLIPSIS_HPP_


#include <utility> // pair


namespace eda { namespace vhdl { namespace util {


/**
 * Returns a beautified, shortened string using ellipsis.
 *
 * There are cases in error handling, where possible long literals are to
 * process. If the length exceeds the length \c len the given string \c str is
 * in the middle filled with ellipsis '...' to fit the given length \c len.
 */
template<typename RangeType>
static inline
std::string literal_ellipsis(RangeType const& range, std::size_t len)
{
    static std::string const ellipsis = "...";

    std::string const str{
        std::addressof(*range.begin()),
        std::addressof(*range.end())
    };

    if(str.size() < len + 1)
        return str;

    std::size_t const offset = (len - ellipsis.length())/2;

    using range_t = std::pair<std::size_t, std::size_t>;

    range_t const left  { 0,                           offset       };
    range_t const right { (str.length() - offset - 1), str.length() };

    return std::string {
          str.substr(left.first, left.second)
        + ellipsis
        + str.substr(right.first, right.second)
    };
}


} } } // namespace eda.vhdl.util



#endif /* SOURCES_VHDL_INCLUDE_EDA_UTIL_STRING_LITERAL_ELLIPSIS_HPP_ */