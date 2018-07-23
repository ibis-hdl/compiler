/*
 * cxx_color_output.cpp
 *
 *  Created on: 22.07.2018
 *      Author: olaf
 *
 */

#if defined(NDEBUG)
#undef NDEBUG
#endif

#if 0

- [iostream maniputor via xalloc/iword or via derived class?](https://stackoverflow.com/questions/23933655/iostream-maniputor-via-xalloc-iword-or-via-derived-class)
- [Dr. Dobbs: The Standard Librarian: Defining a Facet](http://www.drdobbs.com/the-standard-librarian-defining-a-facet/184403785#4=)
- [Why the RedirectStandardOutput does not have the necessary ANSI codes?](https://stackoverflow.com/questions/1963954/why-the-redirectstandardoutput-does-not-have-the-necessary-ansi-codes)
- [Colorize special words in a string](https://stackoverflow.com/questions/14453543/colorize-special-words-in-a-string)
- [Color console in ANSI C?](https://stackoverflow.com/questions/3274824/color-console-in-ansi-c)
- [Baltasarq/cscrutil](http://github.com/Baltasarq/cscrutil/)
- [ikalnytskyi/termcolor](https://github.com/ikalnytskyi/termcolor)
- [jpcanepa/ansiterm](https://github.com/jpcanepa/ansiterm)
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

#include <iostream>
#include <array>
#include <iterator>
#include <algorithm>
#include <cassert>

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

/*
 * https://groups.google.com/a/isocpp.org/forum/#!topic/std-discussion/xya6RKjgbY4
 */
template<typename value_type, std::size_t SIZE>
class non_aggregate_array
    : public std::array<value_type, SIZE>
{
    template<std::size_t ... N>
    non_aggregate_array(std::initializer_list<value_type> il, std::index_sequence<N ...> )
    : std::array<value_type, SIZE> {{ il.begin()[N] ... }}
    , count{ il.size() }
    { }

public:
    non_aggregate_array(std::initializer_list<value_type> il)
    : non_aggregate_array(il, std::make_index_sequence<SIZE>{})
    { }

    non_aggregate_array() = default;

    std::size_t                                     count;
};

struct basic_printer
{
    typedef uint8_t                                 code_type;

    basic_printer(std::initializer_list<code_type> codes_)
    : codes( codes_ )
    , n{ codes.count }
    { }

    basic_printer() = default;

    std::ostream& print(std::ostream& os) const {

        if (!n) { return os; }

        os << CSI;
        //os << "CSI(" << n << ")[";

        for (size_t i = 0; i != n; ++i) {
            os << static_cast<short>(codes[i]);
            if (i < (n -1)) { os << ";"; }
        }
        os << "m";

        return os;
    }

    void push_back(code_type code)
    {
        assert(n < codes.size() && "Code array is full");
        codes[n++] = code;
    }

    basic_printer& operator|(basic_printer& other)
    {
       assert((this->n + other.n) < codes.size() && "Merged size to big");

       std::copy_n(other.codes.begin(), other.n, &this->codes[n]);
       n = this->n + other.n;

       // prevent other from writing moved ANSII codes
       other.clear();

       return *this;
    }

    basic_printer& operator|(ansii::attribute code)
    {
       push_back(static_cast<code_type>(code));
       return *this;
    }

    void clear()
    {
        codes.fill(0);
        n = 0;
    }

    /* ANSI Control Sequence Introducer/Initiator */
    static constexpr char                           CSI[] = "\x1B[";

    non_aggregate_array<code_type, 4>               codes;
    std::size_t                                     n = 0;
};


std::ostream& operator<<(std::ostream& os, basic_printer const& printer) {
    return printer.print(os);
}


template<ansii::attribute attribute> // ToDO: variadic with push_back()
struct
basic_target
{
    basic_target()
    : printer{ static_cast<basic_printer::code_type>(attribute) }
    { }

    std::ostream& print(std::ostream& os) const {
       return printer.print(os);
    }

    basic_printer                                   printer;
};

template<ansii::attribute attribute>
std::ostream& operator<<(std::ostream& os, basic_target<attribute> const& printer) {
    return printer.print(os);
}


namespace text {
    static auto const Bold = basic_target<ansii::attribute::Text_Bold> {};
}

namespace fg {
    static auto const Red = basic_target<ansii::attribute::Foreground_Red> {};
}

namespace bg {
    static auto const Yellow = basic_target<ansii::attribute::Background_Yellow> {};
}

namespace ansii {
    static auto const Off = basic_target<ansii::attribute::Attributes_Off> {};
}


int main()
{
    // target test
    std::cout << fg::Red << "Hello" << bg::Yellow << "World!" << ansii::Off << "\n";

    // How To ???
    //auto const emphase = basic_target<ansii::attribute::Attributes_Off> { ansii::attribute::Text_Bold, ansii::attribute::Foreground_Red };
    //std::cout << emphase << "Hello World!\n" << ansii::Off;

    // How To ???
    //auto const emphasize  = basic_target { ansii::attribute::Text_Bold, ansii::attribute::Foreground_Red };
    //std::cout << emphasize  << "Hello World!\n" << ansii::Off;

    // How To ???
    //auto const highlight = basic_target<ansii::attribute::Text_Bold, ansii::attribute::Foreground_Red> { };
    //std::cout << highlight << "Hello World!\n" << ansii::Off;

}
