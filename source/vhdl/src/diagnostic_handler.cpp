//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-or-later
//

#include <ibis/vhdl/diagnostic_handler.hpp>
#include <ibis/vhdl/diagnostic_context.hpp>
#include <ibis/vhdl/diagnostic_printer.hpp>
#include <ibis/vhdl/source_location.hpp>
#include <ibis/vhdl/context.hpp>

#include <ibis/vhdl/parser/iterator_type.hpp>  // for explicit template instantiation

#include <ibis/util/position_indicator.hpp>

#include <ibis/util/make_iomanip.hpp>
#include <ibis/util/cxx_bug_fatal.hpp>

#include <ibis/util/compiler/warnings_off.hpp>  // [-Wsign-conversion]
#include <boost/locale/format.hpp>
#include <boost/locale/message.hpp>
#include <boost/range/iterator_range_core.hpp>
#include <ibis/util/compiler/warnings_on.hpp>

#include <algorithm>
#include <iostream>

namespace ibis::vhdl {

// ----------------------------------------------------------------------------
// diagnostic_handler - AST/parse related, expectation error handler
// ----------------------------------------------------------------------------
template <typename Iterator>
void diagnostic_handler<Iterator>::parser_error(iterator_type error_pos,
                                                std::string_view error_message) const
{
    error(error_pos, std::nullopt, error_message, error_type::parser);
}

template <typename Iterator>
void diagnostic_handler<Iterator>::parser_error(iterator_type error_pos,
                                                std::optional<iterator_type> error_last,
                                                std::string_view error_message) const
{
    error(error_pos, error_last, error_message, error_type::parser);
}

template <typename Iterator>
void diagnostic_handler<Iterator>::unsupported(iterator_type error_pos,
                                               std::string_view error_message) const
{
    error(error_pos, std::nullopt, error_message, error_type::not_supported);
}

template <typename Iterator>
void diagnostic_handler<Iterator>::unsupported(iterator_type error_first,
                                               std::optional<iterator_type> error_last,
                                               std::string_view error_message) const
{
    error(error_first, error_last, error_message, error_type::not_supported);
}

template <typename Iterator>
void diagnostic_handler<Iterator>::numeric_error(iterator_type error_pos,
                                                 std::string_view error_message) const
{
    error(error_pos, std::nullopt, error_message, error_type::numeric);
}

template <typename Iterator>
void diagnostic_handler<Iterator>::numeric_error(iterator_type error_pos,
                                                 std::optional<iterator_type> error_last,
                                                 std::string_view error_message) const
{
    error(error_pos, error_last, error_message, error_type::numeric);
}

///  ----------------------------------------------------------------------------
/// Syntax and semantic related error handler
/// ----------------------------------------------------------------------------
template <typename Iterator>
void diagnostic_handler<Iterator>::syntax_error(ast::position_tagged const& where_tag,
                                                std::string_view error_message) const
{
    // the node must be tagged before
    cxx_assert(where_tag.is_tagged(), "Node not correct tagged");

    // The parser's position cache proxy is configured to have the same file id tagged as the node
    // holds. Probably somewhere forgotten position_proxy.set_id(where_tag.file_id) ??
    cxx_assert(where_tag.file_id == current_file().id(), "unexpected file ID");

    auto const where_range = current_file().position_of(where_tag);

    constexpr auto syntax_error = diagnostic_context::provider::syntax;

    error(where_range.begin(), where_range.end(), error_message, syntax_error);
}

template <typename Iterator>
void diagnostic_handler<Iterator>::syntax_error(ast::position_tagged const& where_tag,
                                                ast::position_tagged const& start_label,
                                                ast::position_tagged const& end_label,
                                                std::string_view error_message) const
{
    // check on applied tagging, related to position_cache
    cxx_assert(where_tag.is_tagged(), "Node not tagged");
    cxx_assert(start_label.is_tagged(), "Node/StartLabel not tagged");
    cxx_assert(end_label.is_tagged(), "Node/EndLabel not tagged");

    ++context.errors();

    // set the correct file name and contents by id from position cache proxy
    current_file().set_id(where_tag.file_id);

    constexpr auto syntax_error = diagnostic_context::provider::syntax;

    diagnostic_context diag_ctx{ syntax_error, error_message };

    set_source_location(diag_ctx, where_tag);
    set_source_snippet(diag_ctx, start_label);
    set_source_snippet(diag_ctx, end_label);

    diagnostic_printer diagnostic{ diag_ctx };
    os << diagnostic << '\n';
}

template <typename Iterator>
void diagnostic_handler<Iterator>::error(iterator_type error_first,
                                         std::optional<iterator_type> error_last,
                                         std::string_view error_message, error_type err_type) const
{
    using boost::locale::format;
    using boost::locale::translate;

    ++context.errors();

    diagnostic_context diag_ctx{ err_type, error_message };

    set_source_location(diag_ctx, error_first);
    set_source_snippet(diag_ctx, error_first, error_last);

    diagnostic_printer diagnostic{ diag_ctx };
    os << diagnostic << '\n';
}

// ----------------------------------------------------------------------------
// Private helper
// ----------------------------------------------------------------------------
template <typename Iterator>
source_location diagnostic_handler<Iterator>::get_source_location(iterator_type error_pos) const
{
    auto const [line, column] = line_column_number(error_pos);
    return source_location(  // --
        current_file().file_name(), line, column);
}

template <typename IteratorT>
std::tuple<std::size_t, std::size_t> diagnostic_handler<IteratorT>::line_column_number(
    iterator_type pos) const
{
    // based on [.../x3/support/utility/error_reporting.hpp:position(...)](
    // https://github.com/boostorg/spirit/blob/master/include/boost/spirit/home/x3/support/utility/error_reporting.hpp)
    // Further reading at [What is the unit of a text column number?](
    // https://www.foonathan.net/2021/02/column/#content).

    using char_type = typename std::iterator_traits<iterator_type>::value_type;

    std::size_t line_no = 1;
    std::size_t col_no = 1;
    char_type chr_prev = 0;

    for (iterator_type iter = current_file().file_contents().begin(); iter != pos; ++iter) {
        auto const chr = *iter;
        switch (chr) {
            case '\n':
                if (chr_prev != '\r') {
                    ++line_no;
                    col_no = 1;
                }
                break;
            case '\r':
                ++line_no;
                col_no = 1;
                break;
            case '\t':
                // https://github.com/boostorg/spirit/blob/master/include/boost/spirit/home/support/iterators/line_pos_iterator.hpp
                col_no += tab_sz;  //  - (col_no - 1) % tab_sz;
                break;
            default:
                // On UTF8, skip code points, VHDL is fortunately ASCII.
                ++col_no;
                break;
        }
        chr_prev = chr;
    }

    return { line_no, col_no };
}

template <typename IteratorT>
IteratorT diagnostic_handler<IteratorT>::get_line_start(iterator_type pos) const
{
    auto [begin, end] = current_file().file_contents_range();

    // based on [.../x3/support/utility/error_reporting.hpp:get_line_start(...)](
    // https://github.com/boostorg/spirit/blob/master/include/boost/spirit/home/x3/support/utility/error_reporting.hpp)
    auto last_iter = begin;

    for (auto iter = begin; iter != pos;) {
        if (*iter == '\r' || *iter == '\n') {
            last_iter = ++iter;
        }
        else {
            ++iter;
        }
    }

    return last_iter;
}

template <typename IteratorT>
std::string_view diagnostic_handler<IteratorT>::current_line(iterator_type first) const
{
    // based on [.../x3/support/utility/error_reporting.hpp:print_line(...)](
    // https://github.com/boostorg/spirit/blob/master/include/boost/spirit/home/x3/support/utility/error_reporting.hpp)
    // Note: VHDL has no UTF8, see [VHDL file encoding](
    // https://insights.sigasi.com/tech/vhdl-file-encoding/). The X3 way is using
    // `x3::to_utf8(line)` above.

    auto line_end = first;
    auto const end = current_file().file_contents().end();

    while (line_end != end) {
        if (*line_end == '\r' || *line_end == '\n') {
            break;
        }

        ++line_end;
    }

    return std::string_view(first, line_end);
}

}  // namespace ibis::vhdl

// ----------------------------------------------------------------------------
// Explicit template instantiation
// ----------------------------------------------------------------------------
namespace ibis::vhdl {

template class diagnostic_handler<parser::iterator_type>;

}  // namespace ibis::vhdl
