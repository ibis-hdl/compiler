//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-or-later
//

#include <ibis/vhdl/diagnostic_printer.hpp>
#include <ibis/vhdl/source_location.hpp>
#include <ibis/vhdl/diagnostic_context.hpp>

#include <ibis/util/position_indicator.hpp>
#include <ibis/util/make_iomanip.hpp>
#include <ibis/message.hpp>

#include <ibis/util/cxx_bug_fatal.hpp>

#include <iostream>
#include <iomanip>
#include <format>
#include <string>
#include <string_view>

#include <ibis/util/compiler/warnings_off.hpp>  // [-Wsign-conversion]
#include <boost/locale/format.hpp>
#include <boost/locale/message.hpp>
#include <ibis/util/compiler/warnings_on.hpp>

template <>
struct std::formatter<ibis::vhdl::source_location> {
    // NOLINTNEXTLINE(readability-convert-member-functions-to-static)
    constexpr auto parse(std::format_parse_context& ctx) { return ctx.begin(); }

    // NOLINTNEXTLINE(readability-convert-member-functions-to-static)
    auto format(ibis::vhdl::source_location const& location, std::format_context& ctx) const
    {
        // Based on GNU standard of [Formatting Error Messages](
        // https://www.gnu.org/prep/standards/html_node/Errors.html)
        return std::format_to(ctx.out(), "'{}':{}:{}",  // --
                              location.file_name(),     // {0}
                              location.line(),          // {1}
                              location.column()         // {2}
        );
    }
};

template <>
struct std::formatter<ibis::vhdl::diagnostic_context::failure_type> {
    // NOLINTNEXTLINE(readability-convert-member-functions-to-static)
    constexpr auto parse(std::format_parse_context& ctx) { return ctx.begin(); }

    // NOLINTNEXTLINE(readability-convert-member-functions-to-static)
    auto format(ibis::vhdl::diagnostic_context::failure_type failure,
                std::format_context& ctx) const
    {
        using namespace ibis::vhdl;
        using failure_type = ibis::vhdl::diagnostic_context::failure_type;
        using boost::locale::translate;

        auto const string_of = [](failure_type failure) {
            // clang-format off
            switch (failure) {
                case failure_type::unspecific:
                    return translate("unspecific").str();
                case failure_type::parser:
                    return translate("parse error").str();
                case failure_type::syntax:
                    return translate("syntax error").str();
                case failure_type::semantic:
                    return translate("semantic error").str();
                case failure_type::numeric:
                    return translate("numeric error").str();
                case failure_type::not_supported:
                    return translate("unsupported").str();
                // *No* default branch: let the compiler generate warning about enumeration
                // value not handled in switch
                // *Note* on changes, also check `to_base_specifier()!`
            }
            // clang-format on

            std::unreachable();
        };

        return std::format_to(ctx.out(), "{}", string_of(failure));
    }
};

namespace ibis::vhdl {

diagnostic_printer::diagnostic_printer(diagnostic_context const& ctx)
    : context{ ctx }
{
}

// ToDO [C++20] port this code using std:.formatter, this is a complex use case
std::ostream& diagnostic_printer::print_snippets(std::ostream& os) const
{
    using boost::locale::format;
    using boost::locale::translate;

    auto const indicator = [&](auto& start, auto const& first, auto const& opt_last) {
        using util::position_indicator;
        return util::make_iomanip([&](std::ostream& os) {
            os << position_indicator(start, first, tab_size, ' ');
            if (opt_last.has_value()) {
                os << position_indicator(start, opt_last.value(), tab_size, marker_symbol);
            }
            else {
                os << location_symbol;
            }
        });
    };

    std::size_t const num_width = 4;  // up to 9999 line numbers w/o problems

    auto const left_border = [](std::size_t num = 0) {
        static std::string const space(num_width, ' ');
        static std::string const vline("| ");
        // Note: Explicitly capturing 'num' by copying in the inner lambda; otherwise (capturing
        // by reference) using this lambda results in a dangling reference after the outer one has
        // finished execution! Affected only GCC-11 (and maybe later) (failed test case) and a
        // warning from GCC: ‘num’ may be used uninitialized [-Wmaybe-uninitialized]
        return util::make_iomanip([&, num](std::ostream& os) {
            if (num != 0) {
                os << std::setw(static_cast<int>(num_width)) << std::right << num;
            }
            else {
                os << space;
            }
            os << vline;
        });
    };

    auto const count = context.source_snippets().size();

    for (std::size_t i = 0; i != count; i++) {
        auto const& source_snippet = context.source_snippets()[i];
        auto line_start = source_snippet.source_line().begin();

        // clang-format off
        os << left_border(source_snippet.line_number()) << source_snippet.source_line() << '\n'
           << left_border()
           << indicator(line_start, source_snippet.first(), source_snippet.last())
           << " <<-- " << (i == 0 ? translate("here") : translate("and here"));
        if(i + 1 < count) {
            os << '\n' << left_border() << "...\n";
        }
        else {
            // nothing
        }
        // clang-format on
    }

    return os;
}

std::ostream& diagnostic_printer::print_on(std::ostream& os) const
{
    auto const snippets = [&]() {
        return util::make_iomanip([&](std::ostream& os) { print_snippets(os); });
    };

    using boost::locale::format;
    using boost::locale::translate;

    auto const context_message = [&]() {
        using boost::locale::translate;

        static std::string const unspecified_error_str{ translate("Unspecified error").str() };

        // @todo The diagnostic context has to ensure that there is a message, shouldn't it?
        // With this we get rid off this cumbersome fix
        if (!context.message().empty()) [[likely]] {
            return context.message();
        }
        return std::string_view{ unspecified_error_str };
    };

    // @todo print the failure message in color
    os << std::format("{} {} {}: {}\n",       //
                      translate("In").str(),  // TRANSLATOR "In <'file':line:column> <failure>..."
                      context.location(),     //
                      failure_type{},         // @todo always 'unspecified'- what was the intend?
                      context_message())
       << snippets();

    return os;
}

}  // namespace ibis::vhdl
