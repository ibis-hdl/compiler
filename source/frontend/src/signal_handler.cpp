//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-or-later
//

#include <ibis/frontend/signal_handler.hpp>
#include <ibis/message.hpp>

#include <csignal>
#include <functional>
#include <iostream>

namespace ibis::frontend {

#if 0  // avoid LINT errors
void testing_signal_handler()
{
#if 0  // doesn't work ????
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
#endif

std::string_view signal_name(int sig_num)
{
    using namespace std::literals;

    switch (sig_num) {
        case SIGSEGV:
            return "SIGSEGV"sv;
        case SIGABRT:
            return "SIGABRT"sv;
        case SIGILL:
            return "SIGILL"sv;
        case SIGFPE:
            return "SIGFPE"sv;
#if (IBIS_BUILD_PLATFORM_LINUX)
        case SIGUSR1:
            return "SIGUSR1"sv;
        case SIGBUS:
            return "SIGBUS"sv;
#endif
        default:
            return "unknown"sv;
    }
}

void register_signal_handlers()
{
    auto const signal_handler = []() {
        ibis::warning("No signal handler attached");
        return true;
    };

    if (!signal_handler()) {
        ibis::failure("Failed to install signal handlers");
        std::exit(EXIT_FAILURE);
    }
}

}  // namespace ibis::frontend
