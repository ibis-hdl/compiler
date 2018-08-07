/*
 * stacktrace_gdb.cpp
 *
 *  Created on: 05.08.2018
 *      Author: olaf
 */

#include <csignal>
#include <fstream>
#include <sstream>
#include <optional>

#include <iostream>

#include <boost/process/search_path.hpp>
#include <boost/process/child.hpp>
#include <boost/process/error.hpp>
#include <boost/process/extend.hpp>
#include <boost/process/exe.hpp>
#include <boost/process/args.hpp>
#include <boost/asio.hpp>
#include <boost/filesystem/config.hpp>
#include <boost/filesystem/path.hpp>

#include <thread>
#include <atomic>
#include <system_error>

#include <eda/color/message.hpp>

/*
 * OS specific system headers
 */
#include <eda/predef.hpp>

#if (BOOST_OS_LINUX)
#include <sys/prctl.h>
#include <sys/ptrace.h>
#include <sys/types.h>
#include <unistd.h>
#include <limits.h> // PATH_MAX
#endif


namespace fs = boost::filesystem;
namespace bp = boost::process;



bool register_gdb_signal_handler();

void gdb_signal_handler(int sig, siginfo_t *, void *);
bool gdb_detected();
bool valgrind_detected();

bool token_found(std::string const& token, std::string const& procfs_path);
std::string get_executable_path();


namespace /* anonymous */
{

// or semaphore to notify a waiting thread
volatile std::sig_atomic_t sig_caught;


static const char *signame(int sig) {

    switch (sig) {
        case SIGSEGV:   return "SIGSEGV";
        case SIGABRT:   return "SIGABRT";
        case SIGILL:    return "SIGILL";
        case SIGFPE:    return "SIGFPE";
        case SIGUSR1:   return "SIGUSR1";
        case SIGBUS:    return "SIGBUS";
        default:        return "???";
    }
}

} // anonymous namespace



bool register_gdb_signal_handler()
{
    if (gdb_detected() || valgrind_detected()) {
        std::cout << "GDB signal handler already installed, skip.\n";
        return true;
    }
    else {
        std::cout << "install GDB signal handler.\n";
    }

    struct sigaction sa;
    memset(&sa, 0, sizeof(sa));

    using sigaction_fcn_t = void (*)(int, siginfo_t *, void *);
    sa.sa_sigaction = static_cast<sigaction_fcn_t>(gdb_signal_handler);

    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART | SA_SIGINFO;

    sigaction(SIGSEGV, &sa, nullptr);
    sigaction(SIGUSR1, &sa, nullptr);
    sigaction(SIGFPE,  &sa, nullptr);
    sigaction(SIGBUS,  &sa, nullptr);
    sigaction(SIGILL,  &sa, nullptr);
    sigaction(SIGABRT, &sa, nullptr);

    return true;
}


void gdb_signal_handler(int sig, siginfo_t *, void *)
{
    sig_caught = sig;

    using failure = eda::color::message::failure;

    std::cerr << failure("FAILURE")
              << " gdb stacktrace call for signal #" << sig << " (" << signame(sig) << ")\n";

    fs::path gdb_exe = bp::search_path("gdb");

    if(gdb_exe.empty()) {
        std::cerr << "ERROR: gdb not found\n";
        // XXXX
        return;
    }

    bp::child gdb_proc(
        bp::exe = gdb_exe.string(),
        bp::args = {
            "--quiet",
            "--nx",                         // ignore commands at ~/.gdbinit
            "--batch",
            "-ex", "thread apply all bt full", // execute
            get_executable_path(),            // required symbol data in the executable
            std::to_string(getpid())
        },
        bp::extend::on_setup([](auto&) {
            std::cout << "try to launch GDB process from PID = "
                      << getpid() << "\n";
        }),
        bp::extend::on_error([](auto&, std::error_code const& ec) {
            std::cerr << "error occurred while trying to launch the process: "
                      << ec.message() << "\n";
        }),
        bp::extend::on_fork_error([](auto&, std::error_code const& ec) {
            std::cerr << "error occurred during the call of fork(): "
                      << ec.message() << "\n";
        }),
        bp::extend::on_exec_error([](auto&, std::error_code const& ec) {
            std::cerr << "call of execve() failed: "
                      << ec.message() << "\n";
        }),
        bp::extend::on_success([](auto&) {
            std::cout << "GDB process successfully launched.\n";
        })
    );

    if(!gdb_proc.valid()) {
        std::cerr << "unable to fork() GDB\n";
        return;
    }

    // wait for GDB to start before ...
    std::error_code ec;
    auto time = std::chrono::milliseconds(10000);
    gdb_proc.wait_for(time, ec);

    // ... dropping into the default signal handler
    signal(sig, SIG_DFL);
}


/**
 * Several techniques to detect debuggers; no real anti-debugger detection
 * \see
 * [Leveraging OS to Detect Debugger's Presence](
 *  https://github.com/yellowbyte/reverse-engineering-reference-manual/blob/master/contents/anti-analysis/Anti-Debugging.md)
 * [jvoisin/pangu](https://github.com/jvoisin/pangu)
 */
bool gdb_detected()
{
    static std::optional<bool> result{};

    if (result) {
        return *result;
    }

#if (BOOST_OS_LINUX)

    /* Detect GDB by the mean of /proc/$PID/cmdline for "gdb" */
    {
        std::stringstream path{};
        path << "/proc/" << getppid() << "/cmdline";

        if (token_found("gdb", path.str())) {
            *result = true;
            return *result;
        }
    }

    // also detection shown: https://gist.github.com/leo-yuriev/06b60804f99d33f11cff

#if 0
    /* Doesn't work as expected, gdb can't atach:
     * warning: process <pid1> is already traced by process <pi2>
     * ptrace: Operation not permitted.
     * More investigating required,
     * [nvc](https://github.com/nickg/nvc/blob/master/src/util.c) forks
     * the binary to check it, but doesn't set the flag inside these code.  */

    /* Classic self ptrace trick: a program can only be ptraced by ONE other,
     * \see [Yama](https://www.kernel.org/doc/Documentation/security/Yama.txt} */

    // allow tracing from any process
    prctl(PR_SET_PTRACER, PR_SET_PTRACER_ANY, 0, 0, 0);

    if (ptrace(PTRACE_TRACEME, 0, 0, 0) < 0) {
        *result = true;
        return *result;
    }
    else {
        ptrace(PTRACE_DETACH, 0, 0, 0);
    }
#endif

#else
#warning "detecting GNU/GDB incomplete for OS specific build"
#endif

    *result = false;
    return *result;
}


bool valgrind_detected()
{
#if RUNNING_ON_VALGRIND
    return true;
#endif

    static std::optional<bool> result{};

    if (result) {
        return *result;
    }

    /* [How can I detect if a program is running from within valgrind?](
     * https://stackoverflow.com/questions/365458/how-can-i-detect-if-a-program-is-running-from-within-valgrind)  */
    const char* val = std::getenv("RUNNING_ON_VALGRIND");
    if (val != nullptr) {
        *result = true;
        return *result;
    }

#if (BOOST_OS_LINUX)
    /* [how to set dynamic link library path and environment variable for a process in valgrind](
     * https://stackoverflow.com/questions/24745120/how-to-set-dynamic-link-library-path-and-environment-variable-for-a-process-in-v)
     * ... not very sophisticated implemented  */
    if (token_found("vgpreload", "/proc/self/maps")) {
        *result = true;
        return *result;
    }

#else
#warning "detecting Valgrind incomplete for OS specific build"
#endif

    *result = false;
    return *result;
}

/*
 * Utilities
 */
bool token_found(std::string const& token, std::string const& procfs_path)
{
    /* [Reading files line by line in C++ using ifstream: dealing correctly with badbit, failbit, eofbit, and perror()](
     *  https://gehrcke.de/2011/06/reading-files-in-c-using-ifstream-dealing-correctly-with-badbit-failbit-eofbit-and-perror/)  */
    std::ifstream procfs{ procfs_path };

    if (!procfs.is_open()) {
        perror(("error while opening "  + procfs_path).c_str());
        return false;
    }

    for (std::string line; std::getline(procfs, line); ) {

        if (line.find(token) != std::string::npos) {
            return true;
        }
    }

    if (procfs.bad()) {
        perror(("error while reading file "  + procfs_path).c_str());
        return false;
    }

    return false;
}



/**
 * Get the name of the running executable.
 *
 * Note, this is terrible platform specific, hence the unconventional way of
 * includes to avoid pollution. Fully supported platform headers are as usually
 * on top.
 *
 * \see
 * [Finding current executable's path without /proc/self/exe](
 *  https://stackoverflow.com/questions/1023306/finding-current-executables-path-without-proc-self-exe)
 */

#if (BOOST_OS_WINDOWS)
#  include <stdlib.h>
#elif (BOOST_OS_SOLARIS)
#  include <stdlib.h>
#  include <limits.h>
#elif (BOOST_OS_MACOS)
#  include <mach-o/dyld.h>
#elif (BOOST_OS_BSD_FREE)
#  include <sys/types.h>
#  include <sys/sysctl.h>
#endif


std::string get_executable_path()
{
#if (BOOST_OS_WINDOWS)
    char *exePath;
    if (_get_pgmptr(&exePath) != 0)
    exePath = "";

#elif (BOOST_OS_SOLARIS)
    char exePath[PATH_MAX];
    if (realpath(getexecname(), exePath) == NULL)
    exePath[0] = '\0';

#elif (BOOST_OS_LINUX)
    char exePath[PATH_MAX];
    ssize_t len = ::readlink("/proc/self/exe", exePath, sizeof(exePath));
    if (len == -1 || len == sizeof(exePath)) {
        len = 0;
        perror("error reading '/proc/self/exe'");
    }
    exePath[len] = '\0';

#elif (BOOST_OS_MACOS)
    char exePath[PATH_MAX];
    uint32_t len = sizeof(exePath);
    if (_NSGetExecutablePath(exePath, &len) != 0) {
        exePath[0] = '\0'; // buffer too small (!)
    } else {
        // resolve symlinks, ., .. if possible
        char *canonicalPath = realpath(exePath, NULL);
        if (canonicalPath != NULL) {
            strncpy(exePath,canonicalPath,len);
            free(canonicalPath);
        }
    }

#elif (BOOST_OS_BSD_FREE)
    char exePath[2048];
    int mib[4]; mib[0] = CTL_KERN; mib[1] = KERN_PROC; mib[2] = KERN_PROC_PATHNAME; mib[3] = -1;
    size_t len = sizeof(exePath);
    if (sysctl(mib, 4, exePath, &len, NULL, 0) != 0)
    exePath[0] = '\0';

#endif

    return std::string(exePath);
}
