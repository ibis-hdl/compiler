//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-or-later
//

#pragma once

#include <ibis/vhdl/source_location.hpp>

#include <ibis/vhdl/ast/util/string_span.hpp>

#include <cstdint>
#include <string>
#include <string_view>
#include <optional>
#include <vector>

namespace ibis::vhdl {

namespace detail {

class source_snippet {
public:
    using iterator_type = parser::iterator_type;

public:
    source_snippet() = delete;

    explicit source_snippet(std::size_t line_no_, std::string_view src_line_, iterator_type first_,
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
    iterator_type /* const */ iter_first;

    /// optional iterator position pointing to error/warning ending part inside code snippet
    std::optional<iterator_type> /* const */ iter_last;
};

}  // namespace detail

///
/// error and warning messages data
///
/// ToDo Make it unformatted comparable for use in test, no need to compare diagnostic
/// printer's output!
///
class diagnostic_context {
public:
    enum class failure_kind : std::uint8_t {
        unspecific,
        parser,
        syntax,
        semantic,
        numeric,
        not_supported
    };

    using source_snippet = detail::source_snippet;

private:
    failure_kind failure_type;
    std::string failure_message;
    source_location src_location;
    std::vector<source_snippet> src_snippets;

public:
    diagnostic_context() = delete;

    ///
    /// @brief Construct a new diagnostic context object
    ///
    /// @param failure The kind/origin of failure issue
    /// @param error_message Store a copy of error _message
    ///
    diagnostic_context(failure_kind failure, std::string_view error_message)
        : failure_type{ failure }
        , failure_message{ error_message }
    {
    }

public:
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
    /// Get the message failure_kind enum
    ///
    /// @return failure_kind
    ///
    failure_kind message_provider() const { return failure_type; }

    ///
    /// Get the error/warning message
    ///
    /// @return std::string_view
    ///
    std::string_view message() const { return failure_message; }

    std::vector<source_snippet> const& source_snippets() const { return src_snippets; }
};

}  // namespace ibis::vhdl
