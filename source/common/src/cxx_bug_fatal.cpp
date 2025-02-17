//
// Copyright (c) 2017-2025 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-or-later
//

#include <ibis/util/cxx_bug_fatal.hpp>

#include <cstdlib>
#include <format>
#include <iostream>
#include <source_location>
#include <string>
#include <string_view>

namespace /* anonymous */ {

struct message_header {
    std::string_view title;
};

struct message_footer {
    std::string_view title;
};

}  // namespace

template <>
struct std::formatter<message_header> {
    template <class ParseContext>
    static constexpr auto parse(ParseContext& ctx)
    {
        if (auto const begin = ctx.begin(); begin == ctx.end() || *begin == '}') {
            return begin;
        }

        throw std::format_error("non-empty format specification for <message_header>");
    }

    // NOLINTNEXTLINE(readability-convert-member-functions-to-static)
    template <class FmtContext>
    auto format(message_header header, FmtContext& ctx) const
    {
        return std::format_to(ctx.out(), "{:*^80}\n{:*^80}\n{:*^80}", "", header.title, "");
    }
};

template <>
struct std::formatter<message_footer> {
    template <class ParseContext>
    static constexpr auto parse(ParseContext& ctx)
    {
        if (auto const begin = ctx.begin(); begin == ctx.end() || *begin == '}') {
            return begin;
        }

        throw std::format_error("non-empty format specification for <message_footer>");
    }

    // NOLINTNEXTLINE(readability-convert-member-functions-to-static)
    template <class FmtContext>
    auto format(message_footer footer, FmtContext& ctx) const
    {
        return std::format_to(ctx.out(), "{:-^80}", footer.title);
    }
};

namespace ibis::util::detail {

void assertion_failed_msg(const char* expr, std::string_view message,
                          std::source_location const& location)
{
    std::cerr << std::format(
        "\n{0}\n"
        "in file:     {1}:{2}\n"
        "in function: {3}\n"
        "assertion:   {4}\n"
        "message:     {5}\n"
        "{6}\n\n",
        message_header{ " Fatal Program Error " },  // {0}
        location.file_name(),                       // {1}
        location.line(),                            // {2}
        location.function_name(),                   // {3}
        expr,                                       // {4}
        message,                                    // {5}
        message_footer{}                            // {6}
    );

    std::cerr.flush();
    std::quick_exit(EXIT_FAILURE);
}

void cxx_bug_fatal(std::string_view message, std::source_location const& location)
{
    std::cerr << std::format(
        "\n{0}\n"
        "in file:     {1}:{2}\n"
        "in function: {3}\n"
        "message:     {4}\n"
        "{5}\n\n",
        message_header{ " Serious Program Bug (Fatal Error) " },  // {0}
        location.file_name(),                                     // {1}
        location.line(),                                          // {2}
        location.function_name(),                                 // {3}
        message,                                                  // {4}
        message_footer{}                                          // {5}
    );

    std::cerr.flush();
    std::quick_exit(EXIT_FAILURE);
}

}  // namespace ibis::util::detail
