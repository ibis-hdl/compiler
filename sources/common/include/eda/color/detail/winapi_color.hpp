/*
 * winapi_color.hpp
 *
 *  Created on: 09.08.2018
 *      Author: olpetzol
 */

#ifndef SOURCES_COMMON_INCLUDE_EDA_COLOR_DETAIL_WINAPI_COLOR_HPP_
#define SOURCES_COMMON_INCLUDE_EDA_COLOR_DETAIL_WINAPI_COLOR_HPP_

#include <iostream>

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#undef WIN32_LEAN_AND_MEAN


namespace eda { namespace color {


namespace winapi {


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



namespace detail {


class win_printer
{
public:
    win_printer(winapi::attribute attr_)
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

        iword_fsm(os, handle, attr);

        return os;
    }

    win_printer& operator|=(win_printer const& other)
    {
    	return *this |= static_cast<winapi::attribute>(other.attr);
    }

    win_printer& operator|=(winapi::attribute other_attr)
    {
        attr |= static_cast<WORD>(other_attr);

        return *this;
    }

private:
    WORD text_attributes(HANDLE handle) const {

        if (handle == INVALID_HANDLE_VALUE) {
            return 0;
        }

        CONSOLE_SCREEN_BUFFER_INFO csbi{};
        if (!GetConsoleScreenBufferInfo(handle, &csbi))
            return 0;
        return csbi.wAttributes;
    }

private:
    WORD                                            attr = 0;
    static const int                                xindex;
};


//const int win_printer::xindex = std::ios_base::xalloc();


static inline
std::ostream& operator<<(std::ostream& os, win_printer const& printer) {
    return printer.print(os);
}


static inline
win_printer operator|(win_printer lhs, win_printer const& rhs) {
     lhs |= rhs;
    return lhs;
}


} // namespace detail


using printer = detail::win_printer;
using attribute = winapi::attribute;


namespace text {
    color::printer const bold{ attribute::Text_Bold };
    color::printer const underscore{ attribute::Text_Underscore };
}

namespace fg {
	color::printer const black{ attribute::Foreground_Black };
	color::printer const red{ attribute::Foreground_Red };
	color::printer const green{ attribute::Foreground_Green };
	color::printer const yellow{ attribute::Foreground_Yellow };
	color::printer const blue{ attribute::Foreground_Blue };
	color::printer const magenta{ attribute::Foreground_Magenta };
	color::printer const cyan{ attribute::Foreground_Cyan };
	color::printer const white{ attribute::Foreground_White };
}

namespace bg {
	color::printer const black{ attribute::Background_Black };
	color::printer const red{ attribute::Background_Red };
	color::printer const green{ attribute::Background_Green };
	color::printer const yellow{ attribute::Background_Yellow };
	color::printer const blue{ attribute::Background_Blue };
	color::printer const magenta{ attribute::Background_Magenta };
	color::printer const cyan{ attribute::Background_Cyan };
	color::printer const white{ attribute::Background_White };
}

color::printer const color_off(attribute::Attributes_Off);


} } // namespace eda.color


#endif /* SOURCES_COMMON_INCLUDE_EDA_COLOR_DETAIL_WINAPI_COLOR_HPP_ */
