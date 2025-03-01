//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-or-later
//

#include <ibis/vhdl/context.hpp>

#include <boost/locale/format.hpp>
#include <boost/locale/message.hpp>

#include <format>
#include <ostream>
#include <string>

template <>
struct std::formatter<ibis::vhdl::failure_status> : std::formatter<std::string> {
    // NOLINTNEXTLINE(readability-convert-member-functions-to-static)
    template <class FmtContext>
    auto format(ibis::vhdl::failure_status status, FmtContext& ctx) const
    {
        using boost::locale::format;
        using boost::locale::translate;

        // render the error and warning message to console, for concept
        // see [Wandbox](https://wandbox.org/permlink/VJrqXuEFppw1htY7)

        // clang-format off
        auto const error_message = 
            // TRANSLATORS: singular/plural error(s)
            (format(translate("{1} error", "{1} errors",
                              status.errors())) % status.errors()).str();
        // clang-format on

        // clang-format off
        auto const warning_message =
            // TRANSLATORS: singular/plural warning(s)
            (format(translate("{1} warning", "{1} warnings",
                              status.warnings())) % status.warnings()).str();
        // clang-format on

        if (status.has_errors() && status.has_warnings()) {
            // clang-format off
            return std::formatter<std::string>::format(
                // TRANSLATORS: summary error(s) and warning(s)
                (format(translate("{1} and {2} generated.")) % error_message % warning_message).str(),
                ctx);
            // clang-format on
        }
        if (status.has_errors()) {
            return std::formatter<std::string>::format(
                // TRANSLATORS: summary error(s) only
                (format(translate("{1} generated.")) % error_message).str(), ctx);
        }
        if (status.has_warnings()) {
            return std::formatter<std::string>::format(
                // TRANSLATORS: summary warning(s) only
                (format(translate("{1} generated.")) % warning_message).str(), ctx);
        }
        // NOLINTNEXTLINE(readability-else-after-return)
        else {
            // all went fine
        }

        return ctx.out();
    }
};

namespace ibis::vhdl {

std::ostream& operator<<(std::ostream& os, vhdl::failure_status const& status)
{
    os << std::format("{}", status);
    return os;
}

}  // namespace ibis::vhdl
