//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-or-later
//

#include <ibis/vhdl/diagnostic_handler.hpp>

#include <ibis/diagnostic/util.hpp>
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

///  ----------------------------------------------------------------------------
/// Syntax and semantic related error handler
/// ----------------------------------------------------------------------------
template <typename IteratorT>
void diagnostic_handler<IteratorT>::syntax_error(ast::position_tagged const& where_tag,
                                                 std::string_view error_message) const
{
    // the node must be tagged before
    cxx_assert(where_tag.is_tagged(), "Node not correct tagged");

    // The parser's position cache proxy is configured to have the same file id tagged as the node
    // holds. Probably somewhere forgotten position_proxy.set_id(where_tag.file_id) ??
    cxx_assert(ref_ast_context.get().file_id() == where_tag.file_id,
               "cache proxy file id different");

    auto const where_range = ref_ast_context.get().position_of(where_tag);

    constexpr auto syntax_error = diagnostic_context::failure_kind::syntax;

    error(where_range.begin(), where_range.end(), error_message, syntax_error);
}

template <typename IteratorT>
void diagnostic_handler<IteratorT>::syntax_error(ast::position_tagged const& where_tag,
                                                 ast::position_tagged const& start_label,
                                                 ast::position_tagged const& end_label,
                                                 std::string_view error_message) const
{
    // check on applied tagging, related to position_cache
    cxx_assert(where_tag.is_tagged(), "Node not tagged");
    cxx_assert(start_label.is_tagged(), "Node/StartLabel not tagged");
    cxx_assert(end_label.is_tagged(), "Node/EndLabel not tagged");
    cxx_assert(ref_ast_context.get().file_id() == where_tag.file_id,
               "cache proxy file id different");

    ++ref_vhdl_context.get().errors();

    constexpr auto syntax_error = diagnostic_context::failure_kind::syntax;

    diagnostic_context diag_ctx{ syntax_error, error_message };

    set_source_location(diag_ctx, where_tag);
    set_source_snippet(diag_ctx, start_label);
    set_source_snippet(diag_ctx, end_label);  // FixMe [XXX] same function signature, how to diff?

    diagnostic_printer const diagnostic{ diag_ctx };
    os << diagnostic << '\n';
}

template <typename IteratorT>
void diagnostic_handler<IteratorT>::error(iterator_type error_first,
                                          std::optional<iterator_type> error_last,
                                          std::string_view error_message, error_type err_type) const
{
    using boost::locale::format;
    using boost::locale::translate;

    ++ref_vhdl_context.get().errors();

    diagnostic_context diag_ctx{ err_type, error_message };

    set_source_location(diag_ctx, error_first);
    set_source_snippet(diag_ctx, error_first, error_last);

    diagnostic_printer const diagnostic{ diag_ctx };
    os << diagnostic << '\n';
}

// ----------------------------------------------------------------------------
// Private helper
// ----------------------------------------------------------------------------
template <typename IteratorT>
source_location diagnostic_handler<IteratorT>::get_source_location(iterator_type error_pos) const
{
    using ibis::diagnostic::util::line_column_number;

    auto const position =
        line_column_number(ref_ast_context.get().file_contents(), error_pos, tabulator_size());

    return source_location(ref_ast_context.get().file_name(), position.line, position.character);
}

}  // namespace ibis::vhdl

// ----------------------------------------------------------------------------
// Explicit template instantiation
// ----------------------------------------------------------------------------
namespace ibis::vhdl {

template class diagnostic_handler<parser::iterator_type>;

}  // namespace ibis::vhdl
