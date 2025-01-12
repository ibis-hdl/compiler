//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-or-later
//

#include <ibis/vhdl/diagnostic_printer.hpp>
#include <ibis/vhdl/source_location.hpp>
#include <ibis/vhdl/diagnostic_context.hpp>
#include <ibis/vhdl/diagnostic_formatter.hpp>

#include <ibis/util/position_indicator.hpp>
#include <ibis/util/make_iomanip.hpp>
#include <ibis/message.hpp>

#include <ibis/util/cxx_bug_fatal.hpp>

#include <iostream>
#include <iomanip>
#include <format>
#include <string>
#include <string_view>
#include <array>
#include <utility>

#include <ibis/util/compiler/warnings_off.hpp>  // [-Wsign-conversion]
#include <boost/locale/format.hpp>
#include <boost/locale/message.hpp>
#include <ibis/util/compiler/warnings_on.hpp>

namespace ibis::vhdl {

diagnostic_printer::diagnostic_printer(diagnostic_context const& ctx)
    : context{ ctx }
{
}

// ToDO [C++20] port this code using std::formatter, this is a complex use case
std::ostream& diagnostic_printer::print_snippets(std::ostream& os) const
{
    using boost::locale::format;
    using boost::locale::translate;

    if constexpr ((false)) {
        /*
         * original implementation*
         */
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
            // by reference) using this lambda results in a dangling reference after the outer one
            // has finished execution! Affected only GCC-11 (and maybe later) (failed test case) and
            // a warning from GCC: ‘num’ may be used uninitialized [-Wmaybe-uninitialized]
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
    }
    else {  // new implementation width std::format()
        auto const snippet_count = context.source_snippets().size();

        for (auto snippet_idx{ 0ul }; auto const& source_snippet : context.source_snippets()) {
            auto line_start = source_snippet.source_line().begin();

            constexpr bool debug = true;

            os << std::format(
                "{}|{}\n"   // <gutter>|<source_snippet>
                "{}|{}{}",  // <gutter>|<issue_marker>
                number_gutter{ source_snippet.line_number() }, source_snippet.source_line(),
                number_gutter{},
                issue_marker{ line_start, source_snippet.first(), source_snippet.last() },
                debug ? "$print-snippet-end" : ""  // end marker
            );

            if (snippet_idx + 1 < snippet_count) {
                os << std::format("\n{} ...\n", number_gutter{});
            }
            else {
                // nothing
            }
            ++snippet_idx;
        }
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

        // ToDo The diagnostic context has to ensure that there is a message, shouldn't it?
        // With this we get rid off this cumbersome fix
        if (!context.message().empty()) [[likely]] {
            return context.message();
        }
        return std::string_view{ unspecified_error_str };
    };

    // ToDo print the failure message in color
    os << std::format("{} {} {}: {}\n",       //
                      translate("In").str(),  // TRANSLATOR "In <'file':line:column> <failure>..."
                      context.location(),     //
                      failure_type{},         // FixMe always 'unspecified'- what was the intend?
                      context_message())
       << snippets();

    return os;
}

}  // namespace ibis::vhdl
