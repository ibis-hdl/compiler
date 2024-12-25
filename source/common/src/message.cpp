//
// Copyright (c) 2017-2024 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-or-later
//

#include <ibis/message.hpp>

#include <boost/locale/message.hpp>

#include <fmt/printf.h>
#include <fmt/color.h>

#include <string_view>
#include <iostream>
#include <cstdio>

// ------------------------------------------------------------------------------------------------
// ToDo: The code in this file is bullshit and shall be replaced by a better solution.
// It's the result of the retirement  of the ibis::color code base and essentially a
// quick & dirty solution to replace it.
// ------------------------------------------------------------------------------------------------

namespace /* anonymous */ {

[[noreturn]] inline void unreachable()  // @todo [C++23] std::unreachable()
{
#if defined(_MSC_VER) && !defined(__clang__)  // MSVC
    __assume(false);
#else  // GCC, Clang
    __builtin_unreachable();
#endif
}

std::ostream& write(std::ostream& os, std::string_view msg, bool auto_nl)
{
    os << msg << (auto_nl ? "\n" : "");
    return os;
}

std::ostream& write(std::ostream& os, boost::locale::basic_message<char> msg, bool auto_nl)
{
    msg.write(os);
    os << (auto_nl ? "\n" : "");
    return os;
}

}  // namespace

namespace ibis {

std::ostream& message(std::string_view msg, ibis::severity severity, bool auto_nl)
{
    using enum ibis::severity;

    switch (severity) {
        case note: {
            fmt::print(stdout, fg(fmt::color::green), "[{}] ", "Note");
            return write(std::cout, msg, auto_nl);
        }
        case warning: {
            fmt::print(stdout, fg(fmt::color::yellow), "[{}] ", "Warning");
            return write(std::cout, msg, auto_nl);
        }
        case error: {
            fmt::print(stderr, fg(fmt::color::red), "[{}] ", "Error");
            return write(std::cerr, msg, auto_nl);
        }
        case failure: {
            fmt::print(stderr, fg(fmt::color::red), "[{}] ", "Failure");
            return write(std::cerr, msg, auto_nl);
        }
        default:
            unreachable();
    }

    unreachable();
}

std::ostream& message(boost::locale::basic_message<char> msg, ibis::severity severity, bool auto_nl)
{
    using enum ibis::severity;

    switch (severity) {
        case note: {
            fmt::print(stdout, fg(fmt::color::green), "[{}] ", "Note");
            return write(std::cout, msg, auto_nl);
        }
        case warning: {
            fmt::print(stdout, fg(fmt::color::yellow), "[{}] ", "Warning");
            return write(std::cout, msg, auto_nl);
        }
        case error: {
            fmt::print(stderr, fg(fmt::color::red), "[{}] ", "Error");
            return write(std::cerr, msg, auto_nl);
        }
        case failure: {
            fmt::print(stderr, fg(fmt::color::red), "[{}] ", "Failure");
            return write(std::cerr, msg, auto_nl);
        }
        default:
            unreachable();
    }

    unreachable();
}

}  // namespace ibis