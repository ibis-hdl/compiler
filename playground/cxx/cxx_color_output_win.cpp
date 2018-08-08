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


// https://github.com/Baltasarq/cscrutil/blob/master/src/scrutil.c


int main()
{
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

	if(hStdout == INVALID_HANDLE_VALUE) {
		std::cout << "no valid handle\n";
	}

	// Remember how things were when we started
	CONSOLE_SCREEN_BUFFER_INFO csbi{};
	GetConsoleScreenBufferInfo( hStdout, &csbi );

	using windows::attribute;

	SetConsoleTextAttribute(hStdout,
	    		(WORD)attribute::Foreground_Red | (WORD)attribute::Background_Yellow);

	std::cout << "Hello World\n";

	SetConsoleTextAttribute( hStdout, csbi.wAttributes );

	std::cout << "Hello\n";
}
