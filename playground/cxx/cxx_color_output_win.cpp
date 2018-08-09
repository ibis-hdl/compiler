/*
 * cxx_color_output_win.cpp
 *
 *  Created on: 26.07.2018
 *      Author: olaf
 *
 *  [Add color to your std::cout](https://www.codeproject.com/Articles/16431/Add-color-to-your-std-cout)
 *  [colors in console for beginners](http://www.cplusplus.com/forum/beginner/5830/)
 *  [Konsolen Farbe �ndern](https://www.c-plusplus.net/forum/topic/259410/konsolen-farbe-%C3%A4ndern)
 */


#include <iostream>
#include <array>
#include <iterator>
#include <algorithm>
#include <cassert>

#define WIN32_LEAN_AND_MEAN // https://stackoverflow.com/questions/11040133/what-does-defining-win32-lean-and-mean-exclude-exactly
#include <windows.h>


namespace windows {

/* [Using the High-Level Input and Output Functions](
 * https://docs.microsoft.com/en-us/windows/console/using-the-high-level-input-and-output-functions)
 * Note: fore-, background and intensity using 8 bits. */
enum class attribute : WORD {
    // FixMe: support Text attribute
    Attributes_Off      = 0x000,
    Text_Bold           = 0x100,
    Text_Underscore     = 0x200,
    Text_Blink          = 0x400,
    Text_Reverse        = 0x800,
    //Text_Concealed    = ????,
    // Foreground colors
    Foreground_Black    = 0,
    Foreground_Red      = FOREGROUND_RED,
    Foreground_Green    = FOREGROUND_GREEN,
    Foreground_Yellow   = FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY,
    Foreground_Blue     = FOREGROUND_BLUE,
    Foreground_Magenta  = FOREGROUND_BLUE | FOREGROUND_RED,
    Foreground_Cyan     = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY,
    Foreground_White    = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED,
    // Background colors
    Background_Black    = 0,
    Background_Red      = BACKGROUND_RED,
    Background_Green    = BACKGROUND_GREEN,
    Background_Yellow   = BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY,
    Background_Blue     = BACKGROUND_BLUE,
    Background_Magenta  = BACKGROUND_BLUE | BACKGROUND_RED,
    Background_Cyan     = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_INTENSITY,
    Background_White    = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED,
};

} // namespace windows


/* [How to store formatting settings with an IOStream?](
 *  https://stackoverflow.com/questions/20792101/how-to-store-formatting-settings-with-an-iostream/20792102#20792102)
 * [Custom manipulator for class](
 *  https://stackoverflow.com/questions/29336267/custom-manipulator-for-class/29351947#29351947)
 * [Stream Manipulation for outputting object data in different formats](
 *  https://stackoverflow.com/questions/35328329/stream-manipulation-for-outputting-object-data-in-different-formats/35328664#35328664)
 */
// https://github.com/ikalnytskyi/termcolor/blob/master/include/termcolor/termcolor.hpp
// https://github.com/Baltasarq/cscrutil/blob/master/src/scrutil.c
struct win_printer
{
    win_printer(windows::attribute attr_)
    : attr{ static_cast<WORD>(attr_) }
    { }

    win_printer() = default;

    win_printer(win_printer const&) = default;
    win_printer& operator=(win_printer const&) = default;

    std::ostream& print(std::ostream& os) const
    {
        // no POSIX way to extract stream handler from the a given
        // `std::ostream` object
        auto stream = [](std::ostream& os) {
            HANDLE handle = INVALID_HANDLE_VALUE;
            if (&os == &std::cout)                      {
                handle = GetStdHandle(STD_OUTPUT_HANDLE);
            }
            if (&os == &std::cerr || &os == &std::clog) {
                handle = GetStdHandle(STD_ERROR_HANDLE);
            }
            return handle;
        };

        auto const iword_fsm = [&](std::ostream& os_, auto handle_, WORD attr_) {

            typedef enum : WORD { init, active, passiv } state_t;

            union {
                struct {
                    WORD 	state;
                    WORD   	default_attribute;
                } data;
                // std::ios_base::iword, see https://en.cppreference.com/w/cpp/io/ios_base/iword
                long        value;
            } iword;

            iword.value = os_.iword(win_printer::xindex);
            state_t next_state{ init };

            switch (iword.data.state) {
                case init:
                    iword.data.default_attribute = text_attributes(handle_);
                    [[falltrough]]
                case active: {
                        // check on unsupported text-only attribute
                        if ((attr_ & 0xFF) == 0) {
                            // attr = 0 means no visibility
                            attr_ = iword.data.default_attribute;
                        }
                         // set only color relevant (lower) byte
                        WORD const upper = (iword.data.default_attribute >> 8) & 0xFF;
                        attr_ = (upper << 8 ) | (attr_ & 0xFF);
                        SetConsoleTextAttribute(handle_, attr_);
                        next_state = passiv;
                    }
                    break;
                case passiv: {
                        SetConsoleTextAttribute(handle_, iword.data.default_attribute);
                        next_state = active;
                    }
                    break;
                default:
                    std::cerr << __func__ << ": INVALID STATE\n";
                    next_state = init;
            }

            iword.data.state = next_state;
            os_.iword(win_printer::xindex) = iword.value;
        };

        HANDLE const handle = stream(os);

        // redirected - no way to write colors this (windows) way
        if (handle == INVALID_HANDLE_VALUE) {
            return os;
        }

        //os << "[" << std::hex << attr << "]";
        iword_fsm(os, handle, attr);

        return os;
    }

    win_printer& operator|=(win_printer const& other)
    {
    	return *this |= static_cast<windows::attribute>(other.attr);
    }

    win_printer& operator|=(windows::attribute other_attr)
    {
        attr |= static_cast<WORD>(other_attr);

        return *this;
    }

    WORD text_attributes(HANDLE handle) const {

        if (handle == INVALID_HANDLE_VALUE) {
            return 0;
        }

        CONSOLE_SCREEN_BUFFER_INFO csbi{};
        if (!GetConsoleScreenBufferInfo(handle, &csbi))
            return 0;
        return csbi.wAttributes;
    }

    WORD                                            attr = 0;
    static const int                                xindex;
};


const int win_printer::xindex = std::ios_base::xalloc();



std::ostream& operator<<(std::ostream& os, win_printer const& printer) {
    return printer.print(os);
}


namespace text {
    win_printer const Bold = win_printer(windows::attribute::Text_Bold);
}

namespace fg {
    win_printer const Red = win_printer(windows::attribute::Foreground_Red);
}

namespace bg {
    win_printer const Blue = win_printer(windows::attribute::Background_Blue);
    win_printer const Red = win_printer(windows::attribute::Background_Red);
    win_printer const Yellow = win_printer(windows::attribute::Background_Yellow);
}

win_printer const OFF = win_printer(windows::attribute::Attributes_Off);


#if 1
int main()
{
    win_printer attr = win_printer(windows::attribute::Background_Red);
    attr |= text::Bold;

    // syntax looks strange ....
    std::cout << fg::Red << "(cout (Hello World))"  << OFF << ", works" << "\n";
    std::cout << text::Bold << "(bold (Hello World))"  <<OFF << ", works" << "\n";
    std::cout << bg::Red << "(cout (Hello World))"  << OFF << ", works" << "\n";
    std::cout << attr << "(cout (Hello World))" << OFF << ", works" << "\n";

    std::cout << "Juhu\n";
}
#else
/*
 * Windows Console Bullshit: "Hello" get's as usually, setting the background
 * also changes the text color to it's inverse.
 */
int main()
{
    std::cout << "Hello ";

    // save attributes
    CONSOLE_SCREEN_BUFFER_INFO attr_orig{};
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &attr_orig);

    // set background only
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED);
    std::cout << "World\n";

    // restore attributes
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), attr_orig.wAttributes);

    return 0;
}

#endif
