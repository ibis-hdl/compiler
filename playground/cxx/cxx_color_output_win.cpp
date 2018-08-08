/*
 * cxx_color_output_win.cpp
 *
 *  Created on: 26.07.2018
 *      Author: olaf
 *
 *  [Add color to your std::cout](https://www.codeproject.com/Articles/16431/Add-color-to-your-std-cout)
 *  [colors in console for beginners](http://www.cplusplus.com/forum/beginner/5830/)
 *  [Konsolen Farbe ändern](https://www.c-plusplus.net/forum/topic/259410/konsolen-farbe-%C3%A4ndern)
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
 * https://docs.microsoft.com/en-us/windows/console/using-the-high-level-input-and-output-functions) */
enum class attribute : uint16_t {
    // FixMe: Text attribute - unsupported, how to ???
    Attributes_Off 		= 0x100,
    Text_Bold 			= 0x101,
    Text_Underscore 	= 0x102,
    Text_Blink 			= 0x103,
    Text_Reverse 		= 0x104,
    Text_Concealed 		= 0x105,
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
	typedef enum { unspecified, active, passiv } state_t;

	win_printer()
	{
		using windows::attribute;
		attr = (WORD)attribute::Foreground_Red | (WORD)attribute::Background_Yellow;
	}

	win_printer(int)
	{
		using windows::attribute;
		attr = (WORD)attribute::Foreground_Green | (WORD)attribute::Background_White;
	}

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

    	auto const storage_fsm = [&](std::ostream& os_, auto handle_, WORD attr_) {

            union {
            	struct {
            		WORD	state;
            		WORD	default_attribute;
            		WORD	padding[2];
            	} my;
            	long		stream_storage;
            } data;

            data.stream_storage = os_.iword(win_printer::xindex);
            state_t next_state = unspecified;

            switch (data.my.state) {
    			case unspecified:
    				// store default attributes
    				data.my.default_attribute = text_attributes(handle_);
    				[[falltrough]]
    			case active:
    				SetConsoleTextAttribute(handle_, attr_);
    				next_state = passiv;
    				break;
    			case passiv:
    				SetConsoleTextAttribute(handle_, data.my.default_attribute);
    				next_state = active;
    				break;
    			default:
    				std::cerr << "INVALID STATE\n";
    				next_state = unspecified;
            }

            data.my.state = next_state;
            os_.iword(win_printer::xindex) = data.stream_storage;
    	};

        HANDLE const handle = stream(os);

        // redirected - no way to write colors this (windows) way
        if (handle == INVALID_HANDLE_VALUE) {
        	return os;
        }

        storage_fsm(os, handle, attr);

        return os;
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

	WORD											attr = -1;

	static const int 								xindex;
};


const int win_printer::xindex = std::ios_base::xalloc();



std::ostream& operator<<(std::ostream& os, win_printer const& printer) {
	return printer.print(os);
}


int main()
{
	win_printer p;
	win_printer o(42);

	std::cerr << p << "(cerr (Hello World))"   << p << ", works" << "\n";
	std::cout << o << "(stdout (Hello World))" << o << ", works also." << "\n";
	std::cout << "Juhu\n";
}
