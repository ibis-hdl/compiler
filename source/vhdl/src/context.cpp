//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-or-later
//

#include <ibis/vhdl/context.hpp>

#include <ibis/vhdl/ast/util/string_span_hash.hpp>

#include <ibis/util/compiler/warnings_off.hpp>  // [-Wsign-conversion]
#include <boost/locale/format.hpp>
#include <boost/locale/message.hpp>
#include <ibis/util/compiler/warnings_on.hpp>

#include <cstddef>
#include <algorithm>
#include <string>

namespace ibis::vhdl {

context::context(std::int32_t error_limit)
    : error_count(error_limit)
{
}

std::ostream& failure_status::print_on(std::ostream& os) const
{
    using boost::locale::format;
    using boost::locale::translate;

    // render the error and warning message to console, for concept
    // see [Wandbox](https://wandbox.org/permlink/VJrqXuEFppw1htY7)

    // TRANSLATORS: singular/plural error(s)
    auto const error_message =                                       // --
        (format(translate("{1} error", "{1} errors", ctx.errors()))  // --
         % ctx.errors())
            .str();

    // TRANSLATORS: singular/plural warning(s)
    auto const warning_message =                                           // --
        (format(translate("{1} warning", "{1} warnings", ctx.warnings()))  // --
         % ctx.warnings())
            .str();

    if (ctx.has_errors() && ctx.has_warnings()) {
        // TRANSLATORS: summary error(s) and warning(s)
        os << format(translate("{1} and {2} generated."))  // --
                  % error_message % warning_message;
    }
    else if (ctx.has_errors()) {
        // TRANSLATORS: summary error(s) only
        os << format(translate("{1} generated.")) % error_message;
    }
    else if (ctx.has_warnings()) {
        // TRANSLATORS: summary warning(s) only
        os << format(translate("{1} generated.")) % warning_message;
    }
    else {
        // all went fine
    }

    return os;
}

}  // namespace ibis::vhdl
