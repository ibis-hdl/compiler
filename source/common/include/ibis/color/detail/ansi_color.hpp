#pragma once

#include <ibis/color/attribute.hpp>
#include <ibis/color/detail/api.hpp>

#include <iosfwd>
#include <array>
#include <iterator>
#include <algorithm>
#include <cassert>

namespace ibis::color {

namespace detail {

template <typename enum_type, std::size_t SIZE>
class esc_printer : public std::array<typename std::underlying_type<enum_type>::type, SIZE> {
public:
    using value_type = typename std::underlying_type<enum_type>::type;

private:
    // clang-format off
    // FixMe: Clang AddressSanitizer complains here:
    // https://wandbox.org/permlink/GfF0VgNLDRWOgkd1
    // stack-buffer-overflow .../ansi_color.hpp:33 in
    // esc_printer<ibis::color::attribute, 4ul>::esc_printer<0ul, 1ul, 2ul, 3ul>(std::initializer_list<ibis::color::attribute>, std::integer_sequence<unsigned long, 0ul, 1ul, 2ul, 3ul>)
    // clang-format on
    template <std::size_t... N>
    explicit esc_printer(std::initializer_list<enum_type> il, std::index_sequence<N...>)
        : std::array<value_type, SIZE>{ { static_cast<value_type>(il.begin()[N])... } }
        , count{ il.size() }
    {
        assert(il.size() <= SIZE && "range error of initializer_list");
    }

public:
    explicit esc_printer(std::initializer_list<enum_type> il)
        : esc_printer(il, std::make_index_sequence<SIZE>{})
    {
    }

    esc_printer() = default;
    ~esc_printer() = default;

    esc_printer(esc_printer const&) = default;
    esc_printer& operator=(esc_printer const&) = default;

    esc_printer(esc_printer&&) = default;
    esc_printer& operator=(esc_printer&&) = default;

public:
    std::ostream& print(std::ostream& os) const
    {
        if (count == 0u) {
            return os;
        }

        char const* delimiter = "";

        os << CSI;
        for (std::size_t i = 0; i != count; ++i) {
            // don't interpret as char_type
            os << delimiter << static_cast<short>((*this)[i]);
            delimiter = ";";
        }
        os << "m";

        return os;
    }

    void push_back(color::attribute code)
    {
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

    esc_printer& operator|=(color::attribute code)
    {
        push_back(code);
        return *this;
    }

    void reset()
    {
        (*this).fill(0);
        count = 0;
    }

    std::size_t count = 0;
    static constexpr std::size_t size = SIZE;
    // ANSI Control Sequence Introducer/Initiator
    static constexpr char CSI[] = "\x1B[";
};

template <typename enum_type, std::size_t SIZE>
static inline std::ostream& operator<<(std::ostream& os,
                                       esc_printer<enum_type, SIZE> const& printer)
{
    return printer.print(os);
}

template <typename enum_type, std::size_t SIZE>
static inline esc_printer<enum_type, SIZE> operator|(esc_printer<enum_type, SIZE> lhs,
                                                     esc_printer<enum_type, SIZE> const& rhs)
{
    lhs |= rhs;
    return lhs;
}

}  // namespace detail

using printer = detail::esc_printer<color::attribute, 4>;

namespace text {
color::printer const bold{ attribute::Text_Bold };
color::printer const underscore{ attribute::Text_Underscore };
}  // namespace text

namespace fg {
color::printer const black{ attribute::Foreground_Black };
color::printer const red{ attribute::Foreground_Red };
color::printer const green{ attribute::Foreground_Green };
color::printer const yellow{ attribute::Foreground_Yellow };
color::printer const blue{ attribute::Foreground_Blue };
color::printer const magenta{ attribute::Foreground_Magenta };
color::printer const cyan{ attribute::Foreground_Cyan };
color::printer const white{ attribute::Foreground_White };
}  // namespace fg

namespace bg {
color::printer const black{ attribute::Background_Black };
color::printer const red{ attribute::Background_Red };
color::printer const green{ attribute::Background_Green };
color::printer const yellow{ attribute::Background_Yellow };
color::printer const blue{ attribute::Background_Blue };
color::printer const magenta{ attribute::Background_Magenta };
color::printer const cyan{ attribute::Background_Cyan };
color::printer const white{ attribute::Background_White };
}  // namespace bg

color::printer const color_off{ attribute::Attributes_Off };

}  // namespace ibis::color
