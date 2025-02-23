//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-or-later
//

#include <ibis/vhdl/diagnostic_handler.hpp>

#include <ibis/util/get_iterator_pair.hpp>
#include <ibis/vhdl/ast/util/position_tagged.hpp>
#include <ibis/vhdl/context.hpp>
#include <ibis/vhdl/diagnostic_context.hpp>
#include <ibis/vhdl/diagnostic_printer.hpp>
#include <ibis/vhdl/parser/iterator_type.hpp>  // for explicit template instantiation
#include <ibis/vhdl/parser/position_cache.hpp>
#include <ibis/vhdl/source_location.hpp>

#include <ibis/util/cxx_bug_fatal.hpp>

#include <boost/locale/format.hpp>
#include <boost/locale/message.hpp>

#include <cstddef>
#include <functional>
#include <iterator>
#include <optional>
#include <ostream>
#include <string_view>
#include <tuple>

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
void diagnostic_handler<Iterator>::unsupported(iterator_type error_pos,
                                               std::optional<iterator_type> error_last,
                                               std::string_view error_message) const
{
    error(error_pos, error_last, error_message, error_type::not_supported);
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

#if 0  // NOLINT(readability-avoid-unconditional-preprocessor-if)
    // ToDo [XXX] fix position_cache::proxy::set_id(), current_file().id()
    // on branch code-review-2024 removed 
    // The parser's position cache proxy is configured to have the same file id tagged as the node
    // holds. Probably somewhere forgotten position_proxy.set_id(where_tag.file_id) ??
    cxx_assert(current_file().id() == where_tag.file_id, "cache proxy file id different");
#endif

    auto const where_range = position_cache.get().position_of(where_tag);

    constexpr auto syntax_error = diagnostic_context::failure_type::syntax;

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

    ++context.get().errors();

#if 0  // NOLINT(readability-avoid-unconditional-preprocessor-if)
    // ToDo [XXX] fix position_cache::proxy::set_id(), current_file().id()
    // on branch code-review-2024 removed 
    cxx_assert(current_file().id() == where_tag.file_id, "cache proxy file id different");
#endif

    constexpr auto syntax_error = diagnostic_context::failure_type::syntax;

    diagnostic_context diag_ctx{ syntax_error, error_message };

    set_source_location(diag_ctx, where_tag);
    set_source_snippet(diag_ctx, start_label);
    set_source_snippet(diag_ctx, end_label);  // FixMe [XXX] same function signature, how to diff?

    diagnostic_printer const diagnostic{ diag_ctx };
    os << diagnostic << '\n';
}

template <typename Iterator>
void diagnostic_handler<Iterator>::error(iterator_type error_first,
                                         std::optional<iterator_type> error_last,
                                         std::string_view error_message, error_type err_type) const
{
    using boost::locale::format;
    using boost::locale::translate;

    ++context.get().errors();

    diagnostic_context diag_ctx{ err_type, error_message };

    set_source_location(diag_ctx, error_first);
    set_source_snippet(diag_ctx, error_first, error_last);

    diagnostic_printer const diagnostic{ diag_ctx };
    os << diagnostic << '\n';
}

// ----------------------------------------------------------------------------
// Private helper
// ----------------------------------------------------------------------------
template <typename Iterator>
source_location diagnostic_handler<Iterator>::get_source_location(iterator_type error_pos) const
{
    auto const [line, column] = line_column_number(error_pos);
    return source_location(current_file.file_name(), line, column);
}

template <typename IteratorT>
std::tuple<std::size_t, std::size_t> diagnostic_handler<IteratorT>::line_column_number(
    iterator_type pos) const
{
    // based on [.../x3/support/utility/error_reporting.hpp:position(...)](
    // https://github.com/boostorg/spirit/blob/master/include/boost/spirit/home/x3/support/utility/error_reporting.hpp)
    // Further reading at [What is the unit of a text column number?](
    // https://www.foonathan.net/2021/02/column/#content).

    using char_type = std::iter_value_t<iterator_type>;

    std::size_t line_no = 1;
    std::size_t col_no = 1;
    char_type chr_prev = 0;

    // ToDo Clang -Weverything Warning: ++iter unsafe pointer arithmetic [-Wunsafe-buffer-usage]
    for (iterator_type iter = current_file.file_contents().begin(); iter != pos; ++iter) {
        auto const chr = *iter;
        switch (chr) {
            case '\n':                   // Line Feed (Linux, Mac OS X)
                if (chr_prev != '\r') {  // EOL - End of Line (Windows)
                    ++line_no;
                    col_no = 1;
                }
                break;
            case '\r':  // Carriage Return (Mac pre-OS X)
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
    using ibis::util::get_iterator_pair;

    // FixMe This should be rewritten with range based loops
    auto [begin, end] = get_iterator_pair(current_file.file_contents());

    // based on [.../x3/support/utility/error_reporting.hpp:get_line_start(...)](
    // https://github.com/boostorg/spirit/blob/master/include/boost/spirit/home/x3/support/utility/error_reporting.hpp)
    auto last_iter = begin;

    for (auto iter = begin; iter != pos;) {
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

template <typename IteratorT>
std::string_view diagnostic_handler<IteratorT>::current_line(iterator_type first) const
{
    // based on [.../x3/support/utility/error_reporting.hpp:print_line(...)](
    // https://github.com/boostorg/spirit/blob/master/include/boost/spirit/home/x3/support/utility/error_reporting.hpp)
    // Note: VHDL has no UTF8, see [VHDL file encoding](
    // https://insights.sigasi.com/tech/vhdl-file-encoding/). The X3 way is using
    // `x3::to_utf8(line)` above.

    auto line_end = first;
    // ClangTidy - don't touch, since this may be an iterator classes
    // NOLINTNEXTLINE(readability-qualified-auto,readability-qualified-auto)
    auto const end = current_file.file_contents().end();

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
