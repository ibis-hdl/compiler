//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-only
//

#include <ibis/vhdl/diagnostic_printer.hpp>

#include <ibis/util/position_indicator.hpp>
#include <ibis/util/make_iomanip.hpp>

#include <ibis/util/cxx_bug_fatal.hpp>

#include <iostream>

#include <ibis/compiler/warnings_off.hpp>  // [-Wsign-conversion]
#include <boost/locale/format.hpp>
#include <boost/locale/message.hpp>
#include <ibis/compiler/warnings_on.hpp>

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

    os << format("{1}:{2}:{3}")                 // --
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
            os << color::message::error(translate("parse error"));
            break;
        case error_type::syntax:
            os << color::message::error(translate("syntax error"));
            break;
        case error_type::semantic:
            os << color::message::error(translate("semantic error"));
            break;
        case error_type::numeric:
            os << color::message::error(translate("numeric error"));
            break;
        case error_type::not_supported:
            os << color::message::error(translate("unsupported"));
            break;
        case error_type::unspecific:
            os << color::message::error(translate("unspecific"));
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
            if (opt_last) {
                os << position_indicator(start, opt_last.value(), tab_size, marker_symbol);
            }
            else {
                os << location_symbol;
            }
        });
    };

    auto const count = context.source_snippets().size();

    for (std::size_t i = 0; i != count; i++) {
        auto const& source_snippet = context.source_snippets()[i];
        auto line_start = source_snippet.source_line().begin();

        // clang-format off
        os << source_snippet.source_line() << '\n'
           << indicator(line_start, source_snippet.first(), source_snippet.last())
           << " <<-- " << (i == 0 ? translate("here") : translate("and here")) 
           << (i == 0 ? "\n" : "")
           << (i + 1 < count ? "...\n" : "");
        // clang-format on
    }

    return os;
}

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
    os << location() << ": " << error_type() << ": " << error_message() << '\n'
       << snippets()
       ;
    // clang-format on

    return os;
}

}  // namespace ibis::vhdl
