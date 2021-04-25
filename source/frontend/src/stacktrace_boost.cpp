#include <ibis/frontend/signal_handler.hpp>

#include <boost/stacktrace.hpp>

#include <csignal>
#include <atomic>
#include <iostream>
#include <filesystem>

#include <ibis/color/message.hpp>

#include <ibis/namespace_alias.hpp>

namespace  // anonymous
{

// or semaphore to notify a waiting thread
volatile ::sig_atomic_t sig_caught;  // Note, at MSVC not in NS std!

}  // anonymous namespace

using ibis::fs::path;

void stacktrace_signal_handler(int signum)
{
    sig_caught = signum;

    using failure = ibis::color::message::failure;

    std::cerr << failure("FAILURE") << " caught signal #" << signum << " (" << signal_name(signum)
              << ")\n";

    // dropping into the default signal handler
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

    if (ibis::fs::exists(backtrace_dump)) {
        std::ifstream ifs{ backtrace_dump };

        boost::stacktrace::stacktrace st = boost::stacktrace::stacktrace::from_dump(ifs);
        os << "Previous run crashed:\n" << st << std::endl;

        ifs.close();
        ibis::fs::remove("./backtrace.dump");

        return true;
    }

    return false;
}

bool register_stacktrace_signal_handler()
{
    dump_prev_stacktrace(std::cerr);

    ::signal(SIGSEGV, &stacktrace_signal_handler);
    ::signal(SIGABRT, &stacktrace_signal_handler);
    ::signal(SIGILL, &stacktrace_signal_handler);
    ::signal(SIGFPE, &stacktrace_signal_handler);

    return true;
}
