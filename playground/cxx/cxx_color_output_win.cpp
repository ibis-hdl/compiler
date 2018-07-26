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


// https://github.com/Baltasarq/cscrutil/blob/master/src/scrutil.c
typedef enum _Color {
    scrBlack, scrBlue, scrRed, scrMagenta,
    scrGreen, scrCyan, scrYellow, scrWhite,
    scrUndefinedColor
} Color;

static short int winInkColors[ scrUndefinedColor + 1];
static short int winPaperColors[ scrUndefinedColor + 1 ];

static void initWindowsColors()
{
	// wincon.h, all defines!
    winInkColors[ scrBlack ]     = 0;
    winInkColors[ scrBlue ]      = FOREGROUND_BLUE;
    winInkColors[ scrRed ]       = FOREGROUND_RED;
    winInkColors[ scrMagenta ]   = FOREGROUND_BLUE | FOREGROUND_RED;
    winInkColors[ scrGreen ]     = FOREGROUND_GREEN;
    winInkColors[ scrCyan ]      = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
    winInkColors[ scrYellow ]    = FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY;
    winInkColors[ scrWhite ]     = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED;
    winInkColors[ scrUndefinedColor ]  = 0;

    winPaperColors[ scrBlack ]   = 0;
    winPaperColors[ scrBlue ]    = BACKGROUND_BLUE;
    winPaperColors[ scrRed ]     = BACKGROUND_RED;
    winPaperColors[ scrMagenta ] = BACKGROUND_BLUE | BACKGROUND_RED;
    winPaperColors[ scrGreen ]   = BACKGROUND_GREEN;
    winPaperColors[ scrCyan ]    = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_INTENSITY;
    winPaperColors[ scrYellow ]  = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_INTENSITY;
    winPaperColors[ scrWhite ]   = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED;
    winPaperColors[ scrUndefinedColor ] = 0;
}

int main()
{
	initWindowsColors();

}
