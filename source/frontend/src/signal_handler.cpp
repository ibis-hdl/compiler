//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-or-later
//

#include <ibis/frontend/signal_handler.hpp>

#include <ibis/color/message.hpp>
#include <ibis/util/platform.hpp>

#include <csignal>
#include <functional>
#include <iostream>

extern bool register_gdb_signal_handler();
extern bool register_stacktrace_signal_handler();

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
    using failure = ibis::color::message::failure;

#if defined(IBIS_WITH_GDB_STACKTRACE)
    std::function<bool(void)> signal_handler{ &register_gdb_signal_handler };
#elif defined(IBIS_WITH_BOOST_STACKTRACE)
    std::function<bool(void)> signal_handler{ &register_stacktrace_signal_handler };
#else
    auto const signal_handler = []() {
        using warning = ibis::color::message::warning;
        std::cout << warning("[ibis/Note] No signal handler attached") << '\n';
        return true;
    };
#endif

    if (!signal_handler()) {
        std::cerr << failure("[ibis/Note] Failed to install signal handlers") << '\n';
        std::exit(EXIT_FAILURE);
    }
}

}  // namespace ibis::frontend
