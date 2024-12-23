//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-or-later
//

#pragma once

#include <ibis/vhdl/parser/position_cache.hpp>
#include <ibis/vhdl/parser/iterator_type.hpp>
#include <ibis/vhdl/diagnostic_context.hpp>

#include <ibis/namespace_alias.hpp>  // IWYU pragma: keep

#include <utility>
#include <string>
#include <optional>
#include <tuple>
#include <iosfwd>

namespace ibis::vhdl {

// forward vhdl::context
class context;
// forward vhdl::source_location
class source_location;

namespace ast {

// forward ast::position_tagged for parser::position_cache
struct position_tagged;

}  // namespace ast

namespace parser {

// forward parser::position_cache
template <typename IteratorT>
class position_cache;

}  // namespace parser

}  // namespace ibis::vhdl

namespace ibis::vhdl {

///
/// Render Parser/Syntax/Semantic error messages
///
/// @tparam IteratorT Type of iterator used by `parser::position_cache`'s `proxy`. Generally
/// equals to `vhdl::parser::iterator_type`.
///
template <typename Iterator>
class diagnostic_handler {
public:
    using iterator_type = Iterator;

    using position_cache_proxy_type = typename parser::position_cache<iterator_type>::proxy;

    using error_type = diagnostic_context::provider;

public:
    ///
    /// Construct a diagnostic handler.
    ///
    /// @param os_    Stream to write error and diagnostic messages.
    /// @param context_ The VHDL context, e.g. with error counter.
    /// @param proxy_ A \ref parser::position_cache::proxy object of \ref parser::position_cache.
    /// @param tabs   Tabulator size, required for correct rendering of source
    /// code snippet.
    ///
    /// @todo affected by [X3 3.0.10 error_handler where() is wrong #712](
    ///   https://github.com/boostorg/spirit/issues/712),
    /// also [X3: error_handler should not skip whitespaces #670](
    ///   https://github.com/boostorg/spirit/pull/670)
    ///
    explicit diagnostic_handler(std::ostream& os_, vhdl::context& context_,
                                position_cache_proxy_type proxy_, std::size_t tabs = 4)
        : os{ os_ }
        , context{ context_ }
        , position_cache_proxy{ std::move(proxy_) }
        , tab_sz{ tabs }
    {
    }

    ~diagnostic_handler() = default;

    diagnostic_handler(diagnostic_handler const&) = delete;
    diagnostic_handler& operator=(diagnostic_handler const&) = delete;

    diagnostic_handler(diagnostic_handler&&) = delete;
    diagnostic_handler& operator=(diagnostic_handler&&) = delete;

public:
    ///
    /// Render the diagnostic error_message.
    ///
    /// @param error_pos     Iterator position where the error occurred.
    /// @param error_message The information error message.
    ///
    void parser_error(iterator_type error_pos, std::string_view error_message) const;

    ///
    /// Render the diagnostic error_message.
    ///
    /// @param error_first   Iterator position where the error occurred.
    /// @param error_last    optional Iterator position to end where the error occurred.
    /// @param error_message The information error message.
    ///
    void parser_error(iterator_type error_first, std::optional<iterator_type> error_last,
                      std::string_view error_message) const;

    ///
    /// Render the diagnostic error_message.
    ///
    /// @param error_pos     Iterator position where the error occurred.
    /// @param error_message The information error message.
    ///
    void unsupported(iterator_type error_pos, std::string_view error_message) const;

    ///
    /// Render the diagnostic error_message.
    ///
    /// @param error_first   Iterator position where the error occurred.
    /// @param error_last    optional Iterator position to end where the error occurred.
    /// @param error_message The information error message.
    ///
    void unsupported(iterator_type error_first, std::optional<iterator_type> error_last,
                     std::string_view error_message) const;

    ///
    /// Render the diagnostic error_message.
    ///
    /// @param error_pos     Iterator position where the error occurred.
    /// @param error_message The information error message.
    ///
    void numeric_error(iterator_type error_pos, std::string_view error_message) const;

    ///
    /// Render the diagnostic error_message.
    ///
    /// @param error_first   Iterator position where the error occurred.
    /// @param error_last    optional Iterator position to end where the error occurred.
    /// @param error_message The information error message.
    ///
    void numeric_error(iterator_type error_first, std::optional<iterator_type> error_last,
                       std::string_view error_message) const;

public:
    ///
    /// Render the diagnostic error_message.
    ///
    /// @param where_tag     The ast::position_tagged node, which triggers the error
    /// @param error_message The information error message.
    ///
    void syntax_error(ast::position_tagged const& where_tag, std::string_view error_message) const;

    ///
    /// Render the diagnostic error_message.
    ///
    /// @param where_tag     The node, which triggers the error.
    /// @param start_label   The start label of the where_tag node.
    /// @param end_label     The complementary end label of the where_tag node.
    /// @param error_message The information error message.
    ///
    /// @todo Change argument order to be conform to other overload.
    ///
    void syntax_error(ast::position_tagged const& where_tag,
                      ast::position_tagged const& start_label,
                      ast::position_tagged const& end_label, std::string_view error_message) const;

public:
    ///
    /// Render the diagnostic error_message and increments the error count at context.
    ///
    /// @param error_first Iterator position where the error occurred.
    /// @param error_last Optional Iterator of end position where the error occurred.
    /// @param error_message The information error message, stores a copy inside
    ///        @ref diagnostic_context
    /// @param err_type The type of error message.
    ///
    void error(iterator_type error_first, std::optional<iterator_type> error_last,
               std::string_view error_message, error_type err_type) const;

public:
    ///
    /// Set the tabulator size
    ///
    /// @param sz new tabulator size to set
    ///
    void set_tabulator_size(std::size_t sz) { tab_sz = sz; }

    ///
    /// Get the current the tabulator size
    ///
    /// @return std::size_t tabulator size
    ///
    std::size_t tabulator_size() const { return tab_sz; }

private:
    ///
    /// Access to the file related postion_cache informations.
    ///
    /// @return Reference to the proxy used.
    ///
    position_cache_proxy_type const& current_file() const { return position_cache_proxy; }

    ///
    /// Return the annotated iterator range from AST tagged node.
    ///
    /// Wraps the call of @ref position_cache::position_of() to get begin/end iterators for
    /// convenience..
    ///
    /// @param tagged_node The AST node to lookup for iterators
    /// @return std::tuple<iterator_type, iterator_type, bool> The iterators tagged before by @ref
    /// annotate. If the node is not tagged empty iterators (begin/end) are returned - for
    /// convenience false to mark these as invalid; otherwise true.
    ///
    std::tuple<iterator_type, iterator_type> iterators_of(
        ast::position_tagged const& tagged_node) const
    {
        auto const iterator_range = current_file().position_of(tagged_node);

        auto first = iterator_range.begin();
        auto const last = iterator_range.end();
        skip_whitespace(first, last);

        return std::tuple{ first, last };
    }

private:
    ///
    /// Get the source location object initialized with origin of issue
    ///
    /// @param error_pos Iterator pointing the error position
    /// @return source_location
    ///
    source_location get_source_location(iterator_type error_pos) const;

    ///
    /// Return the line number of a given iterator position. The position must
    /// be within the position cache range.
    ///
    /// @param pos Iterator position where to gather the line number.
    /// @param tab_sz The tab size, required to calculate the column number.
    /// @return The line and column number.
    ///
    std::tuple<std::size_t, std::size_t> line_column_number(iterator_type pos) const;

    ///
    /// Return an iterator to the begin of the line. White spaces are skipped.
    /// The position must be within the position cache range.
    /// @note For this, the position iterator is modified.
    ///
    /// @param pos Iterator position pointing to a line of interest.
    /// @return Iterator position pointing to the begin of line.
    ///
    iterator_type get_line_start(iterator_type pos_iter) const;

    ///
    /// Print the line where the iterator points to until end-of-line.
    ///
    /// @param first Iterator position pointing to a line of interest.
    /// @return String representing the source line.
    ///
    std::string_view current_line(iterator_type start) const;

    ///
    /// gather location information with file name etc.
    ///
    /// @tparam IteratorT Error iterator type
    /// @param diag_ctx VHDL diagnostic context to be filled with informations
    /// @param first  iterator pointing to point of failure
    ///
    void set_source_location(vhdl::diagnostic_context& diag_ctx, iterator_type first) const
    {
        diag_ctx.set_source_location(get_source_location(first));
    };

    ///
    /// gather location information with file name etc.
    ///
    /// @param diag_ctx VHDL diagnostic context to be filled with informations
    /// @param position_tagged AST tagged node with error/warning informations
    ///
    void set_source_location(vhdl::diagnostic_context& diag_ctx,
                             ast::position_tagged const& position_tagged) const
    {
        auto const [first, last] = iterators_of(position_tagged);
        diag_ctx.set_source_location(get_source_location(first));
    }

    ///
    /// gather erroneous part as source snippet, e.g. start label
    ///
    /// @param diag_ctx VHDL diagnostic context to be filled with informations
    /// @param position_tagged AST tagged node with error/warning informations
    ///
    void set_source_snippet(vhdl::diagnostic_context& diag_ctx,
                            ast::position_tagged const& position_tagged) const
    {
        auto const [first, last] = iterators_of(position_tagged);
        auto const line_no = std::get<0>(line_column_number(first));
        diag_ctx.set_source_snippet(line_no, current_line(get_line_start(first)),  // --
                                    first, last);
    }

    ///
    /// gather erroneous part as source snippet, e.g. on parser error
    ///
    /// @param diag_ctx VHDL diagnostic context to be filled with informations
    /// @param first Iterator to point of failure
    /// @param last optional Iterator to end point of failure
    ///
    void set_source_snippet(vhdl::diagnostic_context& diag_ctx, iterator_type first,
                            std::optional<iterator_type> last) const
    {
        if (last.has_value()) {
            skip_whitespace(first, last.value());
        }
        auto const line_no = std::get<0>(line_column_number(first));
        diag_ctx.set_source_snippet(line_no, current_line(get_line_start(first)), first, last);
    }

    ///
    /// Move the first iterator forward, ensure iter does not point to white space
    ///
    /// @param first iterator to be adjust
    /// @param last end iterator
    ///
    /// @see
    /// - [X3: error_handler should not skip whitespaces #670](
    ///    https://github.com/boostorg/spirit/pull/670)
    /// - [ X3 3.0.10 error_handler where() is wrong #712 ](
    ///    https://github.com/boostorg/spirit/issues/712)
    ///
    static void skip_whitespace(iterator_type& first, iterator_type last)
    {
        // make sure first does not point to white space
        while (first != last) {
            // see [isspace](https://en.cppreference.com/w/cpp/string/byte/isspace)
            auto const chr = static_cast<unsigned char>(*first);
            if (std::isspace(chr)) {
                ++first;
            }
            else {
                break;
            }
        }
    }

private:
    std::ostream& os;
    vhdl::context& context;
    position_cache_proxy_type position_cache_proxy;
    std::size_t tab_sz = 4;
};

}  // namespace ibis::vhdl

namespace ibis::vhdl {

/// Explicit template instantiation declaration
extern template class diagnostic_handler<parser::iterator_type>;

}  // namespace ibis::vhdl
