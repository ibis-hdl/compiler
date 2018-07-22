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

#include <iostream>
#include <array>
#include <iterator>
#include <algorithm>
#include <cassert>


// http://ascii-table.com/ansi-escape-sequences.php
enum class text {
    Off, Bold, Underscore, Blink, Reverse, Concealed,
    COUNT
};

enum class color_attribute {
    Black, Red, Green, Yellow, Blue, Magenta, Cyan, White,
    COUNT
};

enum class color_target {
    foreground = 30,
    background = 40
};

/*
 * https://groups.google.com/a/isocpp.org/forum/#!topic/std-discussion/xya6RKjgbY4
 * https://ideone.com/s0ciUW
 *
 * Alternative approach from [IRC C++-basic/SlashLife](
 *  https://wandbox.org/permlink/TzgTah6w3KBaVaOj)
 */
template<typename value_type, std::size_t SIZE>
class non_aggregate_array
    : public std::array< value_type, SIZE >
{
    template<std::size_t ... N>
    non_aggregate_array(std::initializer_list<value_type> il, std::index_sequence<N ...> )
    : std::array<value_type, SIZE> {{ il.begin()[N] ... }}
    , count{ il.size() }
    { }

public:
    non_aggregate_array(std::initializer_list< value_type > il)
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

    basic_printer& operator|=(code_type code)
    {
       push_back(code);
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


int main()
{
    basic_printer reset{ 0 };

    basic_printer red_on_white{ 31 };
    red_on_white.push_back(47);
    std::cout << "Hello " << red_on_white << "World, " << "Yeah"<< reset << "\n";

    basic_printer fg_yellow{ 33 };
    basic_printer bg_red{ 41 };

    std::cout << "Hello " << (fg_yellow | bg_red) << "World, " << "Yeah"<< reset << "\n";

    basic_printer merged{ 1 };
    merged |= 37;
    merged |= 40;
    merged |= 40;

    std::cout << "Hello " << merged << "World, " << "Yeah"<< reset << "\n";
}
