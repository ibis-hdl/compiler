//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-or-later
//

#include <ibis/vhdl/diagnostic_printer.hpp>

#include <ibis/util/position_indicator.hpp>
#include <ibis/util/make_iomanip.hpp>
#include <ibis/message.hpp>

#include <ibis/util/cxx_bug_fatal.hpp>

#include <iostream>
#include <iomanip>

#include <ibis/util/compiler/warnings_off.hpp>  // [-Wsign-conversion]
#include <boost/locale/format.hpp>
#include <boost/locale/message.hpp>
#include <ibis/util/compiler/warnings_on.hpp>

namespace ibis::vhdl {

diagnostic_printer::diagnostic_printer(diagnostic_context const& ctx)
    : context{ ctx }
{
}

std::ostream& diagnostic_printer::print_source_location(std::ostream& os) const
{
    using boost::locale::format;

    // See GNU standard of [Formatting Error Messages](
    // https://www.gnu.org/prep/standards/html_node/Errors.html)

    os << format("'{1}':{2}:{3}")               // --
              % context.location().file_name()  // {1}
              % context.location().line()       // {2}
              % context.location().column()     // {3}
        ;
    return os;
}

std::ostream& diagnostic_printer::print_error_type(std::ostream& os) const
{
    using boost::locale::format;
    using boost::locale::translate;

    switch (context.message_provider()) {
        case error_type::parser:
            ibis::error(translate("parse error"), false);
            break;
        case error_type::syntax:
            ibis::error(translate("syntax error"), false);
            break;
        case error_type::semantic:
            ibis::error(translate("semantic error"), false);
            break;
        case error_type::numeric:
            ibis::error(translate("numeric error"), false);
            break;
        case error_type::not_supported:
            ibis::error(translate("unsupported"), false);
            break;
        case error_type::unspecific:
            ibis::error(translate("unspecific"), false);
            break;
        default:  // unreachable_bug_triggered
            cxx_unreachable_bug_triggered();
    }

    return os;
}

std::ostream& diagnostic_printer::print_error_message(std::ostream& os) const
{
    using boost::locale::format;
    using boost::locale::translate;

    if (!context.message().empty()) {
        os << context.message();
    }
    else {
        os << translate("Unspecified error");
    };

    return os;
}

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

    // @todo [C++20] this is a use case for std::format
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

// ToDo: With retirement of the ibis::color code base, the diagnostic_printer API must be renewed
// - it is no longer intuitive.
std::ostream& diagnostic_printer::print_on(std::ostream& os) const
{
    auto const location = [&]() {
        return util::make_iomanip([&](std::ostream& os) { print_source_location(os); });
    };
    auto const error_type = [&]() {
        return util::make_iomanip([&](std::ostream& os) { print_error_type(os); });
    };
    auto const error_message = [&]() {
        return util::make_iomanip([&](std::ostream& os) { print_error_message(os); });
    };
    auto const snippets = [&]() {
        return util::make_iomanip([&](std::ostream& os) { print_snippets(os); });
    };

    using boost::locale::format;
    using boost::locale::translate;

    // clang-format off
    os << translate("In")  << " "
       << location() << ": " << error_type() << ": " << error_message() << '\n'
       << snippets()
       ;
    // clang-format on

    return os;
}

}  // namespace ibis::vhdl
