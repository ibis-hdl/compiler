#pragma once

#include <iosfwd>

namespace eda::util {

template <typename Iterator>
struct position_indicator {
    using iterator_type = Iterator;

    position_indicator(iterator_type& first_, iterator_type const& last_, std::size_t tabs,
                       char symbol_)
        : first{ first_ }
        , last{ last_ }
        , tab_sz{ tabs }
        , symbol{ symbol_ }
    {
    }

    std::ostream& print(std::ostream& os) const
    {
        for (; first != last; ++first) {
            auto const chr = *first;

            if (chr == '\r' || chr == '\n') {
                break;
            }
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

    iterator_type& first;
    iterator_type const& last;
    std::size_t tab_sz;
    char symbol;
};

template <typename Iterator>
std::ostream& operator<<(std::ostream& os, position_indicator<Iterator> const indicator)
{
    return indicator.print(os);
}

}  // namespace eda::util