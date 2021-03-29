#pragma once

#include <cstdio>    // fileno
#include <unistd.h>  // isatty

#include <iostream>

namespace eda::color::api_unix {

class isatty {
    bool is_tty(std::streambuf const* rdbuf) const noexcept
    {
        if (rdbuf == std::cout.rdbuf()) {
            return ::isatty(::fileno(stdout));
        }
        if (rdbuf == std::cerr.rdbuf() || rdbuf == std::clog.rdbuf()) {
            return ::isatty(::fileno(stderr));
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

}  // namespace eda::color::api_unix
