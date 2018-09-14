/*
 * stacktrace_boost.cpp
 *
 *  Created on: 05.08.2018
 *      Author: olaf
 */

#include <boost/stacktrace.hpp>

#include <boost/filesystem.hpp>

#include <signal.h>
#include <iostream>

#include <eda/namespace_alias.hpp>

namespace fs = boost::filesystem;

const char* signame(int sig)
{
    switch (sig) {
        case SIGSEGV:
            return "SIGSEGV";
        case SIGABRT:
            return "SIGABRT";
        case SIGILL:
            return "SIGILL";
        case SIGFPE:
            return "SIGFPE";
        default:
            return "???";
    }
}

void stacktrace_signal_handler(int signum)
{
    std::cerr << "Caught Signal '" << signame(signum) << std::endl;

    ::signal(signum, SIG_DFL);

   // write the trace to file and return number of frames written
#if 0
   std::size_t const result = boost::stacktrace::safe_dump_to("./backtrace.dump");
   std::cout << " " << result << std::endl;
#else
   std::cout << boost::stacktrace::stacktrace();
#endif

   ::raise(SIGABRT);
}


bool dump_prev_stacktrace(std::ostream& os)
{
    const char backtrace_dump[] = "./backtrace.dump";

    if (fs::exists(backtrace_dump)) {
        std::ifstream ifs{ backtrace_dump };

        boost::stacktrace::stacktrace st = boost::stacktrace::stacktrace::from_dump(ifs);
        os << "Previous run crashed:\n" << st << std::endl;

        ifs.close();
        fs::remove("./backtrace.dump");

        return true;
    }

    return false;
}

bool register_stacktrace_signal_handler()
{
    dump_prev_stacktrace(std::cerr);

    ::signal(SIGSEGV, &stacktrace_signal_handler);
    ::signal(SIGABRT, &stacktrace_signal_handler);
    ::signal(SIGILL,  &stacktrace_signal_handler);
    ::signal(SIGFPE,  &stacktrace_signal_handler);

    return true;
}

