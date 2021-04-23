#pragma once

#include <windows.h>
#include <io.h>  // _isatty, _fileno

#include <iostream>

namespace ibis::color::api_windows {

class isatty {
    bool is_tty(std::streambuf const* rdbuf) const noexcept
    {
        if (rdbuf == std::cout.rdbuf()) {
            return _isatty(_fileno(stdout));
        }
        if (rdbuf == std::cerr.rdbuf() || rdbuf == std::clog.rdbuf()) {
            return _isatty(_fileno(stderr));
        }
        return false;
    }

public:
    isatty(std::ostream const& os)
        : tty{ is_tty(os.rdbuf()) }
    {
    }

    constexpr operator bool() const { return tty; }

private:
    bool const tty;
};

class stream_handle {
    HANDLE get_handle(std::streambuf const* rdbuf) const noexcept
    {
        if (rdbuf == std::cout.rdbuf()) {
            return GetStdHandle(STD_OUTPUT_HANDLE);
        }
        if (rdbuf == std::cerr.rdbuf() || rdbuf == std::clog.rdbuf()) {
            return GetStdHandle(STD_ERROR_HANDLE);
        }
        return INVALID_HANDLE_VALUE;
    }

public:
    stream_handle(std::ostream const& os)
        : handle{ get_handle(os.rdbuf()) }
    {
    }

    constexpr operator HANDLE() const { return handle; }

private:
    HANDLE const handle;
};

}  // namespace ibis::color::api_windows
