//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-only
//


// Note: The sources are related to Linux and tested on it.

#include <ibis/frontend/signal_handler.hpp>

#include <ibis/frontend/namespace_alias.hpp>

#include <ibis/color/message.hpp>
#include <ibis/color/facet.hpp>

#include <ibis/util/platform.hpp>
#include <ibis/util/compiler/compiler_support.hpp>

#include <boost/process/args.hpp>
#include <boost/process/child.hpp>
#include <boost/process/error.hpp>
#include <boost/process/exe.hpp>
#include <boost/process/extend.hpp>
#include <boost/process/search_path.hpp>

#include <array>
#include <atomic>
#include <chrono>
#include <csignal>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <memory>
#include <optional>
#include <sstream>
#include <string_view>
#include <string>
#include <system_error>
#include <thread>
#include <vector>

//
// OS specific system headers
//
#if defined(IBIS_BUILD_PLATFORM_LINUX)
#include <climits>  // PATH_MAX
// #include <sys/prctl.h>
// #include <sys/ptrace.h>
// #include <sys/types.h>
#include <unistd.h>
#endif

namespace bp = boost::process;

#if !defined(IBIS_BUILD_PLATFORM_LINUX)
#error("stackstrace using GDB runs on Linux only!")
#endif

#if defined(IBIS_BUILD_PLATFORM_LINUX)
void gdb_signal_handler(int signum, siginfo_t* siginfo, void* ucontext);
#endif
bool gdb_detected();
bool valgrind_detected();

bool token_found(std::string const& token, std::string const& procfs_path);
std::string get_executable_path();

namespace  // anonymous
{
// our semaphore to notify a waiting thread
volatile std::sig_atomic_t
    sig_caught;  // NOLINT(cppcoreguidelines-avoid-non-const-global-variables)
}  // namespace

using ibis::frontend::signal_name;

#if defined(IBIS_BUILD_PLATFORM_LINUX)
bool register_gdb_signal_handler()
{
    // Note: This is called in the beginning of main's init() function where
    //       no colors are configured, hence ibis::color isn't applicable.

    if (gdb_detected() || valgrind_detected()) {
        std::cerr << "[ibis/Note] GDB signal handler already installed, skip.\n";
        return true;
    }

    struct sigaction sa {};  // NOLINT(readability-identifier-length)
    memset(&sa, 0, sizeof(sa));

    // NOLINTNEXTLINE(cppcoreguidelines-pro-type-union-access)
    sa.sa_sigaction = &gdb_signal_handler;

    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART | SA_SIGINFO;

    sigaction(SIGSEGV, &sa, nullptr);
    sigaction(SIGUSR1, &sa, nullptr);
    sigaction(SIGFPE, &sa, nullptr);
    sigaction(SIGBUS, &sa, nullptr);
    sigaction(SIGILL, &sa, nullptr);
    sigaction(SIGABRT, &sa, nullptr);

    return true;
}

void gdb_signal_handler(int signum, [[maybe_unused]] siginfo_t* siginfo,
                        [[maybe_unused]] void* ucontext)
{
    sig_caught = signum;

    // Note: If something goes wrong before the color definitions are loaded and installed
    //       no colors are here, e.g. main's init() function.
    using failure = ibis::color::message::failure;

    std::cerr << failure("[ibis/Note] FAILURE") << " caught signal #" << signum << " ("
              << signal_name(signum) << ")\n";

    // FixMe: Internally, Boost::process depends on Boost::filesystem which introduces
    // linker dependencies which we will omit. This affects only stacktrace_gdb part, see
    // [Handle C++17 std::filesystem::path](
    // https://github.com/klemens-morgenstern/boost-process/issues/164)
    boost::filesystem::path gdb_exe{ bp::search_path("gdb") };

    if (gdb_exe.empty()) {  // Clang-Tidy note - even by using of cxx_expect_not()
        std::cerr << "[ibis/Note] ERROR: gdb not found\n";
        // FixMe: any other handling required if gdb not found? Think about ...
        return;
    }

    // FixMe: Clang-Tidy 11.0 gives some notes here, interpreting them is out of my scope ...
    // clang-format off
    bp::child gdb_proc(
        bp::exe = gdb_exe,
        bp::args = {
            "--quiet",
            "--nx",                 // ignore commands at ~/.gdbinit
            "--batch",
            "-ex", "thread apply all bt full", // execute
            get_executable_path(),  // required symbol data in the executable
            std::to_string(getpid())
        },
        bp::extend::on_setup([]([[maybe_unused]] auto& exec) {
            std::cout << "[ibis/Note] try to launch GDB process from PID = "
                      << getpid() << '\n';
        }),
        bp::extend::on_error([]([[maybe_unused]] auto& exec, std::error_code const& ec) {
            std::cerr << "[ibis/Note] error occurred while trying to launch the process: "
                      << ec.message() << '\n';
        }),
        bp::extend::on_success([]([[maybe_unused]] auto& exec) {
            std::cout << "[ibis/Note] GDB process successfully launched:\n\n";
        }),
        // below is posix specific
        bp::extend::on_fork_error([]([[maybe_unused]] auto& exec, std::error_code const& ec) {
            std::cerr << "[ibis/Note] error occurred during the call of fork(): "
                      << ec.message() << '\n';
        }),
        bp::extend::on_exec_error([]([[maybe_unused]] auto& exec, std::error_code const& ec) {
            std::cerr << "[ibis/Note] call of execve() failed: "
                      << ec.message() << '\n';
        })
    );
    // clang-format on

    if (!gdb_proc.valid()) {
        std::cerr << "[ibis/Note] unable to fork() GDB\n";
        return;
    }

    // wait for GDB to start before ...
    std::error_code ec;
    auto time = std::chrono::milliseconds(10000);
    gdb_proc.wait_for(time, ec);

    // ... dropping into the default signal handler
    // FixMe: Check on success, no exhausting how to/what about to care example found
    signal(signum, SIG_DFL);  // NOLINT(cert-err33-c)
}
#endif

///
/// Several techniques to detect debuggers; no real anti-debugger detection
/// \see
/// [Leveraging OS to Detect Debugger's Presence](
/// https://github.com/yellowbyte/reverse-engineering-reference-manual/blob/master/contents/anti-analysis/Anti-Debugging.md)
/// [jvoisin/pangu](https://github.com/jvoisin/pangu)
///
/// also [detection shown](https://gist.github.com/leo-yuriev/06b60804f99d33f11cff)
///
bool gdb_detected()
{
    static std::optional<bool> result{};

    // check for cached result gathered before
    if (result) {
        return *result;
    }

    // Detect GDB by the mean of /proc/$PID/cmdline for "gdb"
    if constexpr (ibis::platform == ibis::platform::Linux) {
        std::stringstream path{};
        path << "/proc/" << getppid() << "/cmdline";

        if (token_found("gdb", path.str())) {
            // cache success
            *result = true;
            return *result;
        }
    }

#if 0
    // Doesn't work as expected, gdb can't attach:
    // warning: process <pid1> is already traced by process <pi2>
    // ptrace: Operation not permitted.
    // More investigating required,
    // [nvc](https://github.com/nickg/nvc/blob/master/src/util.c) forks
    // the binary to check it, but doesn't set the flag inside these code.

    // Classic self ptrace trick: a program can only be ptraced by ONE other,
    // \see [Yama](https://www.kernel.org/doc/Documentation/security/Yama.txt}

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

    // cache failed
    *result = false;
    return *result;
}

bool valgrind_detected()
{
    static std::optional<bool> result{};

    // check for cached result gathered before
    if (result) {
        return *result;
    }

    if constexpr (ibis::platform == ibis::platform::Linux) {
        // [How can I detect if a program is running from within valgrind?](
        //  https://stackoverflow.com/questions/365458/how-can-i-detect-if-a-program-is-running-from-within-valgrind)
        //
        const char* val = std::getenv("RUNNING_ON_VALGRIND");
        if (val != nullptr) {
            // chache success
            *result = true;
            return *result;
        }

        // [how to set dynamic link library path and environment variable for a process in
        // valgrind](
        //  https://stackoverflow.com/questions/24745120/how-to-set-dynamic-link-library-path-and-environment-variable-for-a-process-in-v)
        // ... not very sophisticated implemented
        if (token_found("vgpreload", "/proc/self/maps")) {
            // cache success
            *result = true;
            return *result;
        }
    }

    // cache failed
    *result = false;
    return *result;
}

//
// Utilities
//
bool token_found(std::string const& token, std::string const& procfs_path)
{
    // [Reading files line by line in C++ using ifstream: dealing correctly with badbit, failbit,
    // eofbit, and perror()](
    //  https://gehrcke.de/2011/06/reading-files-in-c-using-ifstream-dealing-correctly-with-badbit-failbit-eofbit-and-perror/)
    //
    std::ifstream procfs{ procfs_path };

    if (!procfs.is_open()) {
        perror(("[ibis/Note] error while opening " + procfs_path).c_str());
        return false;
    }

    for (std::string line; std::getline(procfs, line);) {
        if (line.find(token) != std::string::npos) {
            return true;
        }
    }

    if (procfs.bad()) {
        perror(("[ibis/Note] error while reading file " + procfs_path).c_str());
        return false;
    }

    return false;
}

///
/// Get the name of the running executable.
///
/// Note, this is terrible platform specific, hence the unconventional way of
/// includes to avoid pollution. Fully supported platform headers are as usually
/// on top.
///
/// \see [Finding current executable path without /proc/self/exe](
/// https://stackoverflow.com/questions/1023306/finding-current-executables-path-without-proc-self-exe)
/// [How to implement readlink to find the path](
/// https://stackoverflow.com/questions/5525668/how-to-implement-readlink-to-find-the-path)
///
std::string get_executable_path()
{
    if constexpr (ibis::platform == ibis::platform::Linux) {
        std::array<char, PATH_MAX> binary_path{};  // default initialized with zeros
        ssize_t len = ::readlink("/proc/self/exe", binary_path.data(), binary_path.max_size() - 1);
        if (len == -1 || len == binary_path.max_size() - 1) {
            len = 0;
            perror("[ibis/Note] error reading '/proc/self/exe'");
        }

        assert(len > 0 && "readlink failed, but the result is unintentionally used.");

        return { binary_path.data(), static_cast<std::size_t>(len) };
    }

    return {};
}
