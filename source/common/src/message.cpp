//
// Copyright (c) 2017-2024 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-or-later
//

#include <ibis/message.hpp>

#include <boost/locale/message.hpp>
#include <boost/locale/format.hpp>

#include <fmt/base.h>
// #include <fmt/printf.h>
#include <fmt/color.h>

#include <iostream>
#include <string_view>
#include <cstdio>

// ------------------------------------------------------------------------------------------------
// ToDo: The code in this file is bullshit and shall be replaced by a better solution.
// It's the result of the retirement  of the ibis::color code base and essentially a
// quick & dirty solution to replace it.
// ------------------------------------------------------------------------------------------------

namespace /* anonymous */ {

std::ostream& write(std::ostream& os, std::string_view msg, bool newline)
{
    os << msg << (newline ? "\n" : "");
    return os;
}

std::ostream& write(std::ostream& os, boost::locale::basic_message<char> msg, bool newline)
{
    msg.write(os);
    os << (newline ? "\n" : "");
    return os;
}

std::ostream& write(std::ostream& os, boost::locale::basic_format<char> const& fmt, bool newline)
{
    fmt.write(os);
    os << (newline ? "\n" : "");
    return os;
}

}  // namespace

namespace ibis {

#if defined(_MSC_VER)
#pragma warning(push)
#pragma warning(disable : 4702)  // unreachable
#endif                           // _MSC_VER

std::ostream& message(std::string_view msg, ibis::severity severity, bool newline)
{
    using enum ibis::severity;

    // clang-format off
    switch (severity) {
        case note:
            fmt::print(stdout, fg(fmt::color::green), "[{}] ", "Note");
            return write(std::cout, msg, newline);
        case warning:
            fmt::print(stdout, fg(fmt::color::yellow), "[{}] ", "Warning");
            return write(std::cout, msg, newline);
        case error:
            fmt::print(stderr, fg(fmt::color::red), "[{}] ", "Error");
            return write(std::cerr, msg, newline);
        case failure:
            fmt::print(stderr, fg(fmt::color::red), "[{}] ", "Failure");
            return write(std::cerr, msg, newline);
        //
        // *No* default branch: let the compiler generate warning about enumeration
        // value not handled in switch
        //
    }
    // clang-format on

    std::unreachable();
}

std::ostream& message(boost::locale::basic_message<char> msg, ibis::severity severity, bool newline)
{
    using enum ibis::severity;

    // clang-format off
    switch (severity) {
        case note:
            fmt::print(stdout, fg(fmt::color::green), "[{}] ", "Note");
            return write(std::cout, msg, newline);
        case warning:
            fmt::print(stdout, fg(fmt::color::yellow), "[{}] ", "Warning");
            return write(std::cout, msg, newline);
        case error:
            fmt::print(stderr, fg(fmt::color::red), "[{}] ", "Error");
            return write(std::cerr, msg, newline);
        case failure:
            fmt::print(stderr, fg(fmt::color::red), "[{}] ", "Failure");
            return write(std::cerr, msg, newline);
        //
        // *No* default branch: let the compiler generate warning about enumeration
        // value not handled in switch
        //
    }
    // clang-format on

    std::unreachable();
}

std::ostream& message(boost::locale::basic_format<char> const& fmt, ibis::severity severity,
                      bool newline)
{
    using enum ibis::severity;

    // clang-format off
    switch (severity) {
        case note:
            fmt::print(stdout, fg(fmt::color::green), "[{}] ", "Note");
            return write(std::cout, fmt, newline);
        case warning:
            fmt::print(stdout, fg(fmt::color::yellow), "[{}] ", "Warning");
            return write(std::cout, fmt, newline);
        case error:
            fmt::print(stderr, fg(fmt::color::red), "[{}] ", "Error");
            return write(std::cerr, fmt, newline);
        case failure:
            fmt::print(stderr, fg(fmt::color::red), "[{}] ", "Failure");
            return write(std::cerr, fmt, newline);
        //
        // *No* default branch: let the compiler generate warning about enumeration
        // value not handled in switch
        //
    }
    // clang-format on

    std::unreachable();
}

#if defined(_MSC_VER)
#pragma warning(pop)
#endif

}  // namespace ibis
