/*
 * api_unix.hpp
 *
 *  Created on: 07.09.2018
 *      Author: olaf
 */

#ifndef SOURCES_COMMON_INCLUDE_EDA_COLOR_DETAIL_API_UNIX_HPP_
#define SOURCES_COMMON_INCLUDE_EDA_COLOR_DETAIL_API_UNIX_HPP_

#include <cstdio> // fileno
#include <unistd.h> // isatty

#include <iostream>

namespace eda {
namespace color {
namespace api_unix {

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
    // clang-format off
    bool const                                      tty;
    // clang-format on
};

} // namespace api_unix
} // namespace color
} // namespace eda

#endif /* SOURCES_COMMON_INCLUDE_EDA_COLOR_DETAIL_API_UNIX_HPP_ */
