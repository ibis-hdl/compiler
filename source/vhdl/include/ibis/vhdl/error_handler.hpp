#pragma once

#include <ibis/vhdl/parser/position_cache.hpp>
#include <ibis/vhdl/parser/iterator_type.hpp>

#include <ibis/namespace_alias.hpp>  // IWYU pragma: keep

// the following header are required for x3::error_handler_result
#include <boost/spirit/home/x3/support/traits/tuple_traits.hpp>  // IWYU pragma: keep
#include <boost/spirit/home/x3/support/traits/is_variant.hpp>    // IWYU pragma: keep
#include <boost/spirit/home/x3/auxiliary/guard.hpp>

#include <utility>
#include <string>
#include <iosfwd>

namespace ibis::vhdl {

// forward vhdl::context
class context;

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
/// Parser/Syntax/Semantic error handler
///
/// The responsibility of the error handler is two folded. It worked on parser level to
/// handle parse errors. Otherwise it has to handle syntax and semantic errors.
///
/// The error handler for parsing works on file level, means a file is read into
/// memory and parsed. Hence not all informations stored in @ref parser::position_cache
/// are required for reporting and diagnosing and a file ID specific proxy
/// object refers to the related informations for convenience.
///
/// Opposite to the parser's error_handler task, the error handler has to work on AST/Tree
/// level. All informations tagged at parse time are required for diagnostics.
///
/// Further, the error_handler is used to annotate the AST during parsing, means
/// ties the AST to a vector of iterator positions for the purpose of subsequent
/// semantic error handling when the program is being compiled.
///
/// @todo: Write a formatter class for conrete error reporting, so that users can
///  override the default implementation, e.g.
/// [Controlling output of Boost.Test source location format](
///  https://stackoverflow.com/questions/64618840/controlling-output-of-boost-test-source-location-format)
///
/// @todo Check [Custom error on rule level? #657](https://github.com/boostorg/spirit/issues/657)
///
/// @todo Get "access" to information of node/rule map at parser::on_error_base; or even
/// move the rule name lookup to to the private part of error_handler self.
///
/// @see parser::position_cache
///

template <typename Iterator>
class error_handler {
public:
    using iterator_type = Iterator;
    using x3_result_type = x3::error_handler_result;

    using position_proxy_type = typename parser::position_cache<iterator_type>::proxy;

public:
    ///
    /// Construct a parser error handler.
    ///
    /// @param os_     Stream to write error and diagnostic messages.
    /// @param proxy_ A \ref parser::position_cache::proxy object of \ref parser::position_cache.
    /// @param tabs     Tabulator size, required for correct rendering of source
    ///              code snippet.
    ///
    explicit error_handler(std::ostream& os_, vhdl::context& context_, position_proxy_type proxy_,
                           std::size_t tabs = 4)
        : os{ os_ }
        , context{ context_ }
        , position_proxy{ std::move(proxy_) }
        , tab_sz{ tabs }
    {
    }

    ~error_handler() = default;

    error_handler(error_handler const&) = delete;
    error_handler& operator=(error_handler const&) = delete;

    error_handler(error_handler&&) = delete;
    error_handler& operator=(error_handler&&) = delete;

public:
    ///
    /// Handle a parser error at error_pos and render the diagnostic message
    /// error_message.
    ///
    /// @param error_pos     Iterator position where the error occurred.
    /// @param error_message The information error message.
    /// @return x3::result_type, which allows to recover from parser error or
    ///        even give up.
    ///
    x3_result_type operator()(iterator_type error_pos, std::string const& error_message) const;

public:
    ///
    /// Handle a syntax/semantic error at node and render the diagnostic message
    /// error_message, where only the tagged error position `where_tag` is given.
    ///
    /// @param where_tag     The ast::position_tagged node, which triggers the error
    /// @param error_message The information error message.
    ///
    void operator()(ast::position_tagged const& where_tag, std::string const& error_message) const;

    ///
    /// Handle a syntax/semantic error at node and render the diagnostic message
    /// error_message. This is a special overload for label pairs.
    ///
    /// @param where_tag     The node, which triggers the error.
    /// @param start_label   The start label of the where_tag node.
    /// @param end_label     The complementary end label of the where_tag node.
    /// @param error_message The information error message.
    ///
    /// @todo Change argument order to be conform to other overload.
    ///
    void operator()(ast::position_tagged const& where_tag, ast::position_tagged const& start_label,
                    ast::position_tagged const& end_label, std::string const& error_message) const;

public:
    ///
    /// Print a simple error message
    ///
    /// @param error_message The error message to print.
    ///
    void message(std::string const& error_message) const;

public:
    ///
    /// Access to the file related postion_cache informations.
    ///
    /// @return Reference to the proxy used.
    ///
    position_proxy_type const& current_file() const { return position_proxy; }

private:
    class source_location;
    class formatter;

    source_location get_source_location(iterator_type error_pos) const;

private:
    std::ostream& os;
    vhdl::context& context;
    position_proxy_type position_proxy;
    std::size_t tab_sz;
};

}  // namespace ibis::vhdl

namespace ibis::vhdl {

/// Explicit template instantiation declaration
extern template class error_handler<parser::iterator_type>;

}  // namespace ibis::vhdl
