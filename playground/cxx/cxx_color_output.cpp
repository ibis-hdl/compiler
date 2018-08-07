/*
 * cxx_color_output.cpp
 *
 *  Created on: 22.07.2018
 *      Author: olaf
 *
 * Feature Request: https://wandbox.org/permlink/0JD2DwnighGp7zYF
 *
 * concept       https://wandbox.org/permlink/lQs7qFfkSPZgbS6x [works]
 * esc_printer   https://wandbox.org/permlink/0demYYShXIlH0De9
 *
 */

#if defined(NDEBUG)
#undef NDEBUG
#endif

#if 0

- [iostream maniputor via xalloc/iword or via derived class?](https://stackoverflow.com/questions/23933655/iostream-maniputor-via-xalloc-iword-or-via-derived-class)
- [Dr. Dobbs: The Standard Librarian: Defining a Facet](http://www.drdobbs.com/the-standard-librarian-defining-a-facet/184403785#4=)
- [Colorize special words in a string](https://stackoverflow.com/questions/14453543/colorize-special-words-in-a-string)
- [Color console in ANSI C?](https://stackoverflow.com/questions/3274824/color-console-in-ansi-c)
- [Baltasarq/cscrutil](https://github.com/Baltasarq/cscrutil)
- [ikalnytskyi/termcolor](https://github.com/ikalnytskyi/termcolor)
- [done][jpcanepa/ansiterm](https://github.com/jpcanepa/ansiterm)
- [adoxa/ansicon](https://github.com/adoxa/ansicon)
- [Poco](https://pocoproject.org/docs/Poco.ColorConsoleChannel.html)
#endif

/*
 * https://groups.google.com/a/isocpp.org/forum/#!topic/std-discussion/xya6RKjgbY4
 * https://ideone.com/s0ciUW
 *
 * Alternative approach from [IRC C++-basic/SlashLife](
 *  https://wandbox.org/permlink/TzgTah6w3KBaVaOj)
 */


// https://wandbox.org/permlink/jrervHCM4JmExBJW
#include <iostream>
#include <array>
#include <iterator>
#include <algorithm>
#include <optional>
#include <cassert>

#include <unistd.h> // isatty
#include <cstdio>   // fileno


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



template<typename enum_type, std::size_t SIZE>
class esc_printer
    : public std::array<typename std::underlying_type<enum_type>::type, SIZE>
{
public:
    typedef typename
        std::underlying_type<enum_type>::type       value_type;

private:
    template<std::size_t ... N>
    esc_printer(std::initializer_list<enum_type> il, std::index_sequence<N ...> )
    : std::array<value_type, SIZE>{ { static_cast<value_type>(il.begin()[N]) ...} }
    , count{ il.size() }
    {
        assert(il.size() <= SIZE && "range error of initializer_list");
    }

public:
    esc_printer(std::initializer_list<enum_type> il)
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

namespace text {
    static esc_printer<ansii::attribute, 4> const Bold{ansii::attribute::Text_Bold};
}

namespace fg {
    static esc_printer<ansii::attribute, 4> const Red{ansii::attribute::Foreground_Red};
}

namespace bg {
    static esc_printer<ansii::attribute, 4> const Yellow{ansii::attribute::Background_Yellow};
}

namespace ansii {
    static esc_printer<ansii::attribute, 4> const Off{ansii::attribute::Attributes_Off};
}

namespace attr {
    static esc_printer<ansii::attribute, 4> const Error{ansii::attribute::Text_Bold, ansii::attribute::Foreground_Red};
}



int main()
{
    // target test
    std::cout << fg::Red << "Hello" << bg::Yellow << "World!" << ansii::Off << "\n";
    std::cerr << attr::Error << "Error Test Message" << ansii::Off << "\n";

    esc_printer<ansii::attribute, 4> attr;
    attr = fg::Red | text::Bold | bg::Yellow;

    std::cout << attr << "Welcome at C++" << ansii::Off << "\n";

    esc_printer<ansii::attribute, 4> other = attr;
    std::cout << other << "Welcome at C++" << ansii::Off << "\n";
}

