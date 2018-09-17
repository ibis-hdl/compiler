/*
 * signal_handler.cpp
 *
 *  Created on: 04.08.2018
 *      Author: olaf
 */

#include <ibis/signal_handler.hpp>

#include <eda/color/message.hpp>
#include <eda/predef.hpp>

#include <csignal>
#include <functional>
#include <iostream>

extern bool register_gdb_signal_handler();
extern bool register_stacktrace_signal_handler();

namespace ibis {

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
    while (true) {
        r = 100 / n;
        std::cout << "100 / " << n-- << " = " << r << '\n';
    }
}


const char* signal_name(int sig_num)
{
    switch (sig_num) {
        case SIGSEGV:
            return "SIGSEGV";
        case SIGABRT:
            return "SIGABRT";
        case SIGILL:
            return "SIGILL";
        case SIGFPE:
            return "SIGFPE";
#if (BOOST_OS_LINUX)
        case SIGUSR1:
            return "SIGUSR1";
        case SIGBUS:
            return "SIGBUS";
#endif
        default:
            return "???";
    }
}

void register_signal_handlers()
{
    using failure = eda::color::message::failure;

#if defined(EDA_WITH_GDB_STACKTRACE) && (BOOST_OS_LINUX)
    std::function<bool(void)> signal_handler { &register_gdb_signal_handler };
#elif defined(EDA_WITH_BOOST_STACKTRACE)
    std::function<bool(void)> signal_handler { &register_stacktrace_signal_handler };
#else
    auto const signal_handler = []() {
        using warning = eda::color::message::warning;
        std::cout << warning("No signal handler attached") << '\n';
        return true;
    };
#endif

    if (!signal_handler()) {
        std::cerr << failure("Failed to install signal handlers") << '\n';
        std::exit(EXIT_FAILURE);
    }
}


} // namespace ibis