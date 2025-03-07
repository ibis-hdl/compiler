//
// Copyright (c) 2017-2025 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-or-later
//

#pragma once

#include <boost/range/iterator_range_core.hpp>  // alias vhdl::ast::string_span

#include <cstdint>
#include <iterator>
#include <string_view>
#include <ranges>

namespace ibis::diagnostic {

///
/// A type indicating how positions are encoded,
/// specifically what column offsets mean.
///
enum class PositionEncodingKind : std::uint8_t { ISO8859_1, UTF8, UTF16, UTF32 };

///
/// The diagnostic's severity.
///
enum class DiagnosticSeverity : std::uint8_t { Error = 1, Warning = 2, Information = 3, Hint = 4 };

struct position {
    /// Line position in a document (zero-based).
    std::uint32_t line;

    /// Character offset on a line in a document (zero-based). The meaning of this
    /// offset is determined by the negotiated `PositionEncodingKind`.
    /// If the character value is greater than the line length it defaults back
    /// to the line length.
    std::uint32_t character;
};

///
/// A range in a text document expressed as (zero-based) start and end positions. A range is
/// comparable to a selection in an editor. Therefore, the end position is exclusive. If you want to
/// specify a range that contains a line including the line ending character(s) then use an end
/// position denoting the start of the next line.
///
struct range {
    /// The range's start position.
    position start;

    /// The range's end position.
    position end;
};

/// Represents a location inside a resource, such as a line inside a text file.
struct location {
    std::string_view file_name;
    diagnostic::range range;
};

/// ToDo There must be a better way for gathering informations regards line_start, current_line etc.
/// The iterators are moved multiple times over positions, e.g.
/// @code
/// diag_ctx.set_source_snippet(
///     position.line, current_line(file_contents, get_line_start(file_contents, first)),  // --
///     first, last);
/// @endcode
namespace util {

///
/// Get the line starting with the iterator points to until end-of-line.
///
/// @param position Iterator position pointing to a line of interest.
/// @return Iterator range representing the source line.
///
/// ToDo Consider using boost::iterator_range<IteratorT> as return value
template <std::forward_iterator IteratorT>
std::string_view current_line(boost::iterator_range<IteratorT> iterator_range, IteratorT position)
{
    assert((std::begin(iterator_range) <= position && position < std::end(iterator_range))  // --
           && "Position must be within the iterator_range.");

    // Note: VHDL has no UTF8, see [VHDL file encoding](
    // https://insights.sigasi.com/tech/vhdl-file-encoding/).
    // The Spirit X3 way to cope with UTF is using `x3::to_utf8(line)`.

    // ClangTidy - don't touch, since this may be an iterator class
    // NOLINTBEGIN(readability-qualified-auto)
    auto iter = position;
    auto const end = iterator_range.end();
    // NOLINTEND(readability-qualified-auto)

    while (iter != end) {
        if (*iter == '\r' || *iter == '\n') {
            break;
        }
        ++iter;
    }

    assert(iter < end);
    return std::string_view{ position, iter };
}

// delegate API call for std::string_view
template <std::forward_iterator IteratorT>
std::string_view current_line(std::string_view document_contents, IteratorT position)
{
    // clang-format off
    return current_line(
        boost::iterator_range<IteratorT>{ 
            std::begin(document_contents), std::end(document_contents) 
        }, position);
    // clang-format on
}

///
/// Move the position iterator forward, ensure iter does not point to white space
///
/// @param position iterator to be adjust
/// @param last end iterator
///
/// @see
/// - [X3: error_handler should not skip whitespaces #670](
///    https://github.com/boostorg/spirit/pull/670)
/// - [X3 3.0.10 error_handler where() is wrong #712](
///    https://github.com/boostorg/spirit/issues/712)
///
template <std::forward_iterator IteratorT>
void skip_whitespace(IteratorT& position, IteratorT last)
{
    // make sure position does not point to white space
    while (position != last) {
        // see [isspace](https://en.cppreference.com/w/cpp/string/byte/isspace)
        int const chr = static_cast<unsigned char>(*position);
        if (std::isspace(chr) != 0) {
            ++position;
        }
        else {
            break;
        }
    }
}

///
/// Return an iterator to the begin of the line.
/// The line is determined by the position iterator.
///
/// @param iterator_range Iterator pair of begin/end for the range to find position.
/// @param position Iterator position pointing to a line of interest.
/// @return Iterator position pointing to the begin of line.
///
template <std::forward_iterator IteratorT>
IteratorT get_line_start(boost::iterator_range<IteratorT> iterator_range, IteratorT position)
{
    auto [begin, end] = std::ranges::subrange(iterator_range);

    assert((begin <= position && position < end) && "Position must be within the iterator_range.");

    auto last_iter = begin;

    // warning: 'iter' is an unsafe pointer used for buffer access [-Wunsafe-buffer-usage]
    for (auto iter = begin; iter != position;) {
        // Windows ('\r\n')
        if (*iter == '\r' || *iter == '\n') {
            last_iter = ++iter;
        }
        else {
            ++iter;
        }
    }

    return last_iter;
}

// delegate API call for std::string_view
template <std::forward_iterator IteratorT>
IteratorT get_line_start(std::string_view document_contents, IteratorT position)
{
    // clang-format off
    return get_line_start(
        boost::iterator_range<IteratorT>{ 
            std::begin(document_contents), std::end(document_contents) 
        }, position);
    // clang-format on
}

///
/// @brief Calculate line and column number of a given iterator position, considering different
/// newline characters and tab sizes.
///
/// The @arg position must be within the iterator position cache range @arg iterator_range. The
/// tabulator size is used to calculate the correct column number.
///
/// @tparam IteratorT Forward iterator type.
/// @param iterator_range Iterator pair of begin/end for the document range to find position.
/// @param position Iterator position to determine line/column number.
/// @param tab_sz Tabulator size for column calculation.
/// @return position
///
/// @note This implementation works only for ISO 8859-1 encoded files.
///
template <std::forward_iterator IteratorT>
position line_column_number(boost::iterator_range<IteratorT> iterator_range, IteratorT position,
                            std::uint32_t tab_sz)
{
    using iterator_type = IteratorT;

    assert((std::begin(iterator_range) <= position && position < std::end(iterator_range))  // --
           && "Position must be within the iterator_range.");

    // Further reading at [What is the unit of a text column number?](
    // https://www.foonathan.net/2021/02/column/#content).

    using char_type = std::iter_value_t<iterator_type>;

    auto const reset = [](std::uint32_t& variable) { variable = 0; };

    std::uint32_t line_no = 0;
    std::uint32_t column_no = 0;
    char_type chr_prev = 0;

    for (iterator_type iter = std::begin(iterator_range); iter != position; ++iter) {
        auto const chr = *iter;
        switch (chr) {
            case '\n':                   // Line Feed (Linux, Mac OS X)
                if (chr_prev != '\r') {  // EOL - End of Line (Windows: '\r\n')
                    ++line_no;
                    reset(column_no);
                }
                break;
            case '\r':  // Carriage Return (Mac pre-OS X)
                ++line_no;
                reset(column_no);
                break;
            case '\t':
                column_no += tab_sz;
                break;
            default:
                // On UTF-{8,16,32} skip code points, VHDL is fortunately ISO 8859-1/ASCII.
                ++column_no;
                break;
        }
        chr_prev = chr;
    }

    return { .line = line_no, .character = column_no };
}

// delegate API call for std::string_view
template <std::forward_iterator IteratorT>
position line_column_number(std::string_view document_contents, IteratorT position,
                            std::uint32_t tab_sz)
{
    // clang-format off
    return line_column_number(
        boost::iterator_range<IteratorT>{ 
            std::begin(document_contents), std::end(document_contents) 
        }, position, tab_sz);
    // clang-format on
}

}  // namespace util

}  // namespace ibis::diagnostic
