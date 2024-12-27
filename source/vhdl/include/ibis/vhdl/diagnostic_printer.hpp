//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-or-later
//

#pragma once

#include <ibis/vhdl/diagnostic_handler.hpp>
#include <ibis/vhdl/diagnostic_context.hpp>

#include <iosfwd>
#include <string>

namespace ibis::vhdl {

///
/// Class to display the formatted message.
///
class diagnostic_printer {
public:
    using error_type = diagnostic_context::provider;

public:
    ///
    /// @brief Construct a new printer object
    ///
    /// @param source_location_ The location of the error to print.
    ///
    /// @todo The error_type specifier must be accessible by the header to allow specific error
    /// messages. Best would be to make it an own non-nested class.
    ///
    /// @todo: This class does the formatting only for some peaces of the final error/warning
    /// message. These are combined into the final one inside
    /// `diagnostic_handler<IteratorT>::operator()(ast::position_tagged, ast::position_tagged, ...)`
    /// hence it isn't configurable/derivable as intended. Maybe introduce an `error_context` for
    /// all the informations carried?
    ///
    diagnostic_printer(diagnostic_context const& context);

    std::ostream& print_source_location(std::ostream& os) const;
    std::ostream& print_error_type(std::ostream& os) const;
    std::ostream& print_error_message(std::ostream& os) const;
    std::ostream& print_snippets(std::ostream& os) const;

    std::ostream& print_on(std::ostream& os) const;

public:
    void set_tab_size(std::size_t sz) { tab_size = sz; }
    void set_marker_symbol(char symbol) { marker_symbol = symbol; }
    void set_location_symbol(char symbol) { location_symbol = symbol; }

private:
    diagnostic_context const& context;

    std::size_t tab_size = 4;
    char marker_symbol = '~';
    char location_symbol = '^';
};

inline std::ostream& operator<<(std::ostream& os, diagnostic_printer const& formatter)
{
    return formatter.print_on(os);
}

}  // namespace ibis::vhdl
