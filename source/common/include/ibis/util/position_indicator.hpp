//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-only
//

#pragma once

#include <iosfwd>

namespace ibis::util {

///
/// @brief Print an failure indicator at iterator position
///
/// @tparam Iterator
///
/// @note Based on [../x3/support/utility/error_reporting.hpp](
/// https://github.com/boostorg/spirit/blob/develop/include/boost/spirit/home/x3/support/utility/error_reporting.hpp)
///
template <typename Iterator>
class position_indicator {
    using iterator_type = Iterator;

public:
    ///
    /// @brief Construct a new position indicator object
    ///
    /// @param first_ Iterator to begin of line, modified to point to end-of-line or even last_
    /// @param last_  Iterator to end
    /// @param tabs   tabulator size
    /// @param symbol_ Symbol to print
    ///
    // NOLINTNEXTLINE(bugprone-easily-swappable-parameters)
    position_indicator(iterator_type& first_, iterator_type const& last_, std::size_t tabs,
                       char symbol_)
        : first{ first_ }
        , last{ last_ }
        , tab_sz{ tabs }
        , symbol{ symbol_ }
    {
    }

    std::ostream& print_on(std::ostream& os) const
    {
        for (; first != last; ++first) {
            auto const chr = *first;

            if (chr == '\r' || chr == '\n') {
                break;
            }
            // do not use 'else' after 'break' clang-tidy(readability-else-after-return)
            if (chr == '\t') {
                for (std::size_t i = 0; i != tab_sz; ++i) {
                    os << symbol;
                }
            }
            else {
                os << symbol;
            }
        }

        return os;
    }

private:
    iterator_type& first;
    iterator_type const& last;
    std::size_t tab_sz;
    char symbol;
};

template <typename Iterator>
std::ostream& operator<<(std::ostream& os, position_indicator<Iterator> const& indicator)
{
    return indicator.print_on(os);
}

}  // namespace ibis::util
