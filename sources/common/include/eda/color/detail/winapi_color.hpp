/*
 * winapi_color.hpp
 *
 *  Created on: 09.08.2018
 *      Author: olpetzol
 */

#ifndef SOURCES_COMMON_INCLUDE_EDA_COLOR_DETAIL_WINAPI_COLOR_HPP_
#define SOURCES_COMMON_INCLUDE_EDA_COLOR_DETAIL_WINAPI_COLOR_HPP_

#include <eda/color/attribute.hpp>
#include <eda/color/detail/api.hpp>

#include <iostream>

namespace eda {
namespace color {

namespace detail {

class win_printer {
public:
    win_printer(color::attribute attr_)
        : attr{ native(attr_) }
    {
    }

    win_printer() = default;

    win_printer(win_printer const&) = default;
    win_printer& operator=(win_printer const&) = default;

    std::ostream& print(std::ostream& os) const
    {
        auto const iword_fsm = [&](std::ostream& os_, auto handle_, WORD attr_) {

            typedef enum : WORD { init, active, passiv } state_t;

            union {
                struct {
                    WORD state;
                    WORD default_attribute;
                } data;
                long value;
            } iword;

            iword.value = os_.iword(win_printer::xindex);
            state_t next_state{ init };

            // clang-format off
            switch (iword.data.state) {
                case init:
                    iword.data.default_attribute = text_attributes(handle_);
                    [[fallthrough]];
                case active: {
                        // check on unsupported text-only attribute
                        if ((attr_ & 0xFF) == 0) {
                            // attr = 0 means no visibility
                            attr_ = iword.data.default_attribute;
                        }
                        // set only color relevant (lower) byte
                        WORD const upper = (iword.data.default_attribute >> 8) & 0xFF;
                        attr_ = (upper << 8) | (attr_ & 0xFF);
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
            // clang-format on

            iword.data.state = next_state;
            os_.iword(win_printer::xindex) = iword.value;
        };

        HANDLE const handle = detail::stream_handle{ os };

        // redirected - no way to write colors this (windows) way
        if (handle == INVALID_HANDLE_VALUE) {
            return os;
        }

        iword_fsm(os, handle, attr);

        return os;
    }

    win_printer& operator|=(win_printer const& other)
    {
        attr |= other.attr;
        return *this;
    }

    win_printer& operator|=(color::attribute other_attr)
    {
        attr |= native(other_attr);

        return *this;
    }

private:
    WORD native(color::attribute attr) {

        switch (attr) {
        case attribute::Attributes_Off:
            return 0x000;
        case attribute::Text_Bold:
            return 0x100;
        case attribute::Text_Underscore:
            return 0x200;
        case attribute::Text_Blink:
            return 0x400;
        case attribute::Text_Reverse:
            return 0x800;
        case attribute::Foreground_Black:
            return 0;
        case attribute::Foreground_Red:
            return FOREGROUND_RED;
        case attribute::Foreground_Green:
            return FOREGROUND_GREEN;
        case attribute::Foreground_Yellow:
            return FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY;
        case attribute::Foreground_Blue:
            return FOREGROUND_BLUE;
        case attribute::Foreground_Magenta:
            return FOREGROUND_BLUE | FOREGROUND_RED;
        case attribute::Foreground_Cyan:
            return FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
        case attribute::Foreground_White:
            return FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED;
        case attribute::Background_Black:
            return 0;
        case attribute::Background_Red:
            return BACKGROUND_RED;
        case attribute::Background_Green:
            return BACKGROUND_GREEN;
        case attribute::Background_Yellow:
            return BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY;
        case attribute::Background_Blue:
            return BACKGROUND_BLUE;
        case attribute::Background_Magenta:
            return BACKGROUND_BLUE | BACKGROUND_RED;
        case attribute::Background_Cyan:
            return BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_INTENSITY;
        case attribute::Background_White:
            return BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED;
        default:
            return 0;
        }
    }

    WORD text_attributes(HANDLE handle) const
    {

        if (handle == INVALID_HANDLE_VALUE) {
            return 0;
        }

        CONSOLE_SCREEN_BUFFER_INFO csbi{};
        if (!GetConsoleScreenBufferInfo(handle, &csbi))
            return 0;
        return csbi.wAttributes;
    }

private:
    // clang-format off
    WORD                                            attr = 0;
    static const int                                xindex;
    // clang-format on
};

// const int win_printer::xindex = std::ios_base::xalloc();

static inline std::ostream& operator<<(std::ostream& os, win_printer const& printer)
{
    return printer.print(os);
}

static inline win_printer operator|(win_printer lhs, win_printer const& rhs)
{
    lhs |= rhs;
    return lhs;
}

} // namespace detail

using printer = detail::win_printer;

namespace text {
color::printer const bold{ attribute::Text_Bold };
color::printer const underscore{ attribute::Text_Underscore };
} // namespace text

namespace fg {
color::printer const black{ attribute::Foreground_Black };
color::printer const red{ attribute::Foreground_Red };
color::printer const green{ attribute::Foreground_Green };
color::printer const yellow{ attribute::Foreground_Yellow };
color::printer const blue{ attribute::Foreground_Blue };
color::printer const magenta{ attribute::Foreground_Magenta };
color::printer const cyan{ attribute::Foreground_Cyan };
color::printer const white{ attribute::Foreground_White };
} // namespace fg

namespace bg {
color::printer const black{ attribute::Background_Black };
color::printer const red{ attribute::Background_Red };
color::printer const green{ attribute::Background_Green };
color::printer const yellow{ attribute::Background_Yellow };
color::printer const blue{ attribute::Background_Blue };
color::printer const magenta{ attribute::Background_Magenta };
color::printer const cyan{ attribute::Background_Cyan };
color::printer const white{ attribute::Background_White };
} // namespace bg

color::printer const color_off(attribute::Attributes_Off);

} // namespace color
} // namespace eda

#endif /* SOURCES_COMMON_INCLUDE_EDA_COLOR_DETAIL_WINAPI_COLOR_HPP_ */
