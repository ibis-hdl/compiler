#pragma once

#include <utility>  // pair

namespace ibis::vhdl::util {

///
/// Returns a beautified, shortened string using ellipsis.
///
/// There are cases in error handling, where possible long literals are to
/// process. If the length exceeds the length \c len the given string \c str is
/// in the middle filled with ellipsis '...' to fit the given length \c len.
///
template <typename RangeType>
inline std::string literal_ellipsis(RangeType const& range, std::size_t len)
{
    static std::string const ellipsis = "...";

    std::string const str{ std::addressof(*range.begin()), std::addressof(*range.end()) };

    if (str.size() < len + 1) return str;

    std::size_t const offset = (len - ellipsis.length()) / 2;

    using range_t = std::pair<std::size_t, std::size_t>;

    range_t const left{ 0, offset };
    range_t const right{ (str.length() - offset - 1), str.length() };

    return std::string{ str.substr(left.first, left.second) + ellipsis +
                        str.substr(right.first, right.second) };
}

}  // namespace ibis::vhdl::util
