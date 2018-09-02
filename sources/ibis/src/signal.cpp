/*
 * signal.cpp
 *
 *  Created on: 04.08.2018
 *      Author: olaf
 */

#include <iostream>

#include <csignal>


void testing_signal_handler()
{
#if 0 // doesn't work ????
    int sig = SIGFPE;
    std::cout << "SIGNAL " << signame(sig) << '\n';
    signal(sig, SIG_DFL);
#endif
    int n = 3;
    int r = 0;
    std::cout << "testing signal handler with SIGFPE\n";
#ifndef __clang_analyzer__
    while(true) {
        r = 100 / n;
        std::cout << "100 / " << n-- << " = " << r << '\n';
    }
#endif // __clang_analyzer__
}

