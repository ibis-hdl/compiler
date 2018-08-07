/*
 * ansii_color.hpp
 *
 *  Created on: 05.08.2018
 *      Author: olaf
 */

#ifndef SOURCES_COMMON_INCLUDE_EDA_COLOR_DETAIL_ANSII_COLOR_HPP_
#define SOURCES_COMMON_INCLUDE_EDA_COLOR_DETAIL_ANSII_COLOR_HPP_

#include <iosfwd>
#include <algorithm>
#include <cassert>


namespace eda { namespace color {


namespace ansii {

// http://ascii-table.com/ansi-escape-sequences.php
enum class attribute : uint8_t {
    // Text attribute
    Attributes_Off = 0,
    Text_Bold = 1,
    Text_Underscore = 4,
    Text_Blink = 5,
    Text_Reverse = 7,
    Text_Concealed = 8,
    // Foreground colors
    Foreground_Black = 30,
    Foreground_Red = 31,
    Foreground_Green = 32,
    Foreground_Yellow = 33,
    Foreground_Blue = 34,
    Foreground_Magenta = 35,
    Foreground_Cyan = 36,
    Foreground_White = 37,
    // Background colors
    Background_Black = 40,
    Background_Red = 41,
    Background_Green = 42,
    Background_Yellow = 43,
    Background_Blue = 44,
    Background_Magenta = 45,
    Background_Cyan = 46,
    Background_White = 47,
};

} // namespace ansii


namespace detail {


template<typename enum_type, std::size_t SIZE>
class esc_printer
    : public std::array<typename std::underlying_type<enum_type>::type, SIZE>
{
public:
    typedef typename
        std::underlying_type<enum_type>::type       value_type;

private:
    template<std::size_t ... N>
    explicit esc_printer(std::initializer_list<enum_type> il, std::index_sequence<N ...> )
    : std::array<value_type, SIZE>{ { static_cast<value_type>(il.begin()[N]) ...} }
    , count{ il.size() }
    {
        assert(il.size() <= SIZE && "range error of initializer_list");
    }

public:
    explicit esc_printer(std::initializer_list<enum_type> il)
    : esc_printer(il, std::make_index_sequence<SIZE>{})
    { }

    esc_printer() = default;
    esc_printer(esc_printer const&) = default;
    esc_printer& operator=(esc_printer const&) = default;

public:
    std::ostream& print(std::ostream& os) const {

        if (!count) { return os; }

        os << CSI;
        for (size_t N = (count - 1), i = 0; i != count; ++i) {
            // don't interpret as char_type
            os << static_cast<short>((*this)[i]);
            if (i != N) { os << ";"; }
        }
        os << "m";

        return os;
    }

    void push_back(ansii::attribute code) { /// XXX make me variadic
        assert(count < size && "Code array is full");
        (*this)[count++] = static_cast<value_type>(code);
    }

    esc_printer& operator|=(esc_printer const& other)
    {
       assert((count + other.count) <= size && "Merged size to big");

       std::copy_n(other.begin(), other.count, &(*this)[count]);
       count += other.count;

       return *this;
    }

    esc_printer& operator|=(ansii::attribute code)
    {
       push_back(code);
       return *this;
    }

    void reset()
    {
        (*this).fill(0);
        count = 0;
    }

    std::size_t                                     count = 0;
    static constexpr std::size_t                    size = SIZE;
    /* ANSI Control Sequence Introducer/Initiator */
    static constexpr char                           CSI[] = "\x1B[";
};


template<typename enum_type, std::size_t SIZE>
std::ostream& operator<<(std::ostream& os, esc_printer<enum_type, SIZE> const& printer) {
    return printer.print(os);
}

template<typename enum_type, std::size_t SIZE>
esc_printer<enum_type, SIZE> operator|(esc_printer<enum_type, SIZE> lhs, esc_printer<enum_type, SIZE> const& rhs) {
     lhs |= rhs;
    return lhs;
}

} // namespace detail


template<typename enum_type, std::size_t SIZE>
using esc_printer = detail::esc_printer<enum_type, SIZE>;


namespace text {
    static detail::esc_printer<ansii::attribute, 4> const bold{ansii::attribute::Text_Bold};
    static detail::esc_printer<ansii::attribute, 4> const underscore{ansii::attribute::Text_Underscore};
}

namespace fg {
    static detail::esc_printer<ansii::attribute, 4> const black{ansii::attribute::Foreground_Black};
    static detail::esc_printer<ansii::attribute, 4> const red{ansii::attribute::Foreground_Red};
    static detail::esc_printer<ansii::attribute, 4> const green{ansii::attribute::Foreground_Green};
    static detail::esc_printer<ansii::attribute, 4> const yellow{ansii::attribute::Foreground_Yellow};
    static detail::esc_printer<ansii::attribute, 4> const blue{ansii::attribute::Foreground_Blue};
    static detail::esc_printer<ansii::attribute, 4> const magenta{ansii::attribute::Foreground_Magenta};
    static detail::esc_printer<ansii::attribute, 4> const cyan{ansii::attribute::Foreground_Cyan};
    static detail::esc_printer<ansii::attribute, 4> const white{ansii::attribute::Foreground_White};
}

namespace bg {
    static detail::esc_printer<ansii::attribute, 4> const black{ansii::attribute::Background_Black};
    static detail::esc_printer<ansii::attribute, 4> const red{ansii::attribute::Background_Red};
    static detail::esc_printer<ansii::attribute, 4> const green{ansii::attribute::Background_Green};
    static detail::esc_printer<ansii::attribute, 4> const yellow{ansii::attribute::Background_Yellow};
    static detail::esc_printer<ansii::attribute, 4> const blue{ansii::attribute::Background_Blue};
    static detail::esc_printer<ansii::attribute, 4> const magenta{ansii::attribute::Background_Magenta};
    static detail::esc_printer<ansii::attribute, 4> const cyan{ansii::attribute::Background_Cyan};
    static detail::esc_printer<ansii::attribute, 4> const white{ansii::attribute::Background_White};
}

static detail::esc_printer<ansii::attribute, 4> const color_off{ansii::attribute::Attributes_Off};


} } // namespace eda.color


#endif /* SOURCES_COMMON_INCLUDE_EDA_COLOR_DETAIL_ANSII_COLOR_HPP_ */
