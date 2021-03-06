//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-or-later
//

#pragma once

#include <ibis/vhdl/source_location.hpp>

#include <ibis/vhdl/ast/util/string_span.hpp>

#include <string>
#include <string_view>
#include <optional>
#include <vector>

#include <iostream>

namespace ibis::vhdl {

///
/// error/warning messages data
///
/// @todo Find a more appropiate name for this - too much .._context in class names anywhere.
///
class diagnostic_context {
public:
    /// @todo find a better name for this
    enum class provider { unspecific, parser, syntax, semantic, numeric, not_supported };

public:
    class source_snippet {
    public:
        using iterator_type = parser::iterator_type;

    public:
        source_snippet(std::size_t line_no_, std::string_view src_line_, iterator_type first_,
                       std::optional<iterator_type> last_)
            : line_no{ line_no_ }
            , src_line{ src_line_ }
            , iter_first{ first_ }
            , iter_last{ last_ }
        {
        }

    public:
        /// The line number of source snippet
        std::size_t line_number() const { return line_no; }

        /// code snippet of erroneous part as text line
        std::string_view source_line() const { return src_line; }

        /// iterator position pointing to error/warning part inside code snippet
        iterator_type first() const { return iter_first; }

        /// iterator position pointing to error/warning part inside code snippet
        std::optional<iterator_type> last() const { return iter_last; }

    private:
        /// The line number of source snippet
        std::size_t line_no;

        /// code snippet of erroneous part as text line
        std::string_view src_line;

        /// iterator position pointing to error/warning beginning part inside code snippet
        iterator_type const iter_first;

        /// optional iterator position pointing to error/warning ending part inside code snippet
        std::optional<iterator_type> const iter_last;
    };

public:
    ///
    /// @brief Construct a new diagnostic context object
    ///
    /// @param provider_ The origin of issue
    /// @param err_message_ Store a copy of error _message
    ///
    diagnostic_context(provider provider_, std::string_view err_message_)
        : msg_provider{ provider_ }
        , err_message{ err_message_ }
    {
    }

    ///
    /// Set the source location object
    ///
    /// @param location The location info
    ///
    void set_source_location(source_location const& location) { src_location = location; }

    ///
    /// Set the source snippet object
    ///
    /// @param line_no line number of source
    /// @param src_line full line of source where the issue appears
    /// @param first Begin of erroneous part to be marked
    /// @param last optional end of erroneous part to be marked
    ///
    void set_source_snippet(std::size_t line_no, std::string_view src_line,
                            source_snippet::iterator_type const& first,
                            std::optional<source_snippet::iterator_type> const& last)
    {
        src_snippets.emplace_back(line_no, src_line, first, last);
    }

    ///
    /// Get the source location
    ///
    /// @return source_location const&
    ///
    source_location const& location() const { return src_location; }

    ///
    /// Get the message provider enum
    ///
    /// @return provider
    ///
    provider message_provider() const { return msg_provider; }

    ///
    /// Get the error/warning message
    ///
    /// @return std::string_view
    ///
    std::string_view message() const { return err_message; }

    std::vector<source_snippet> const& source_snippets() const { return src_snippets; }

private:
    provider msg_provider;
    std::string err_message;
    source_location src_location;
    std::vector<source_snippet> src_snippets;
};

}  // namespace ibis::vhdl
