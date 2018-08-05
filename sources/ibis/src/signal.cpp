/*
 * signal.cpp
 *
 *  Created on: 04.08.2018
 *      Author: olaf
 */

#include <iostream>

#include <csignal>


extern bool register_gdb_signal_handler();


void testing_signal_handler()
{
#if 0 // doesn't work ????
    int sig = SIGFPE;
    std::cout << "SIGNAL " << signame(sig) << "\n";
    signal(sig, SIG_DFL);
#endif
    int n = 1;
    int r = 0;
    while(true) {
        std::cout << n << " -> " << r << "\n";
        r = 100 / n--;
    }
}


bool register_signal_handlers()
{
#if defined(EDA_WITH_GDB_STACKTRACE)
    return register_gdb_signal_handler();
#else
    return true;
#endif
}

