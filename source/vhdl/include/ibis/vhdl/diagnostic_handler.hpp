#pragma once

#include <ibis/vhdl/parser/position_cache.hpp>
#include <ibis/vhdl/parser/iterator_type.hpp>

#include <ibis/namespace_alias.hpp>  // IWYU pragma: keep

#include <utility>
#include <string>
#include <optional>
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
/// Render Parser/Syntax/Semantic error messages
///
template <typename Iterator>
class diagnostic_handler {
public:
    using iterator_type = Iterator;

    using position_proxy_type = typename parser::position_cache<iterator_type>::proxy;

public:
    using error_type = enum { unspecific, parser, syntax, semantic, numeric };

public:
    ///
    /// Construct a diagnostic handler.
    ///
    /// @param os_    Stream to write error and diagnostic messages.
    /// @param proxy_ A \ref parser::position_cache::proxy object of \ref parser::position_cache.
    /// @param tabs   Tabulator size, required for correct rendering of source
    /// code snippet.
    ///
    explicit diagnostic_handler(std::ostream& os_, vhdl::context& context_,
                                position_proxy_type proxy_, std::size_t tabs = 4)
        : os{ os_ }
        , context{ context_ }
        , position_proxy{ std::move(proxy_) }
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
    /// Render the diagnostic error_message. Error source is in most cases the parser to handle
    /// expectation errors.
    ///
    /// @param error_pos     Iterator position where the error occurred.
    /// @param error_message The information error message.
    /// @param err_type      The type of error message.
    ///
    void operator()(iterator_type error_pos, std::string const& error_message,
                    error_type err_type = error_type::parser) const;

public:
    ///
    /// Render the diagnostic error_message. Error source is in most cases the parser.
    ///
    /// @param where_tag     The ast::position_tagged node, which triggers the error
    /// @param error_message The information error message.
    /// @param err_type      The type of error message.
    ///
    void operator()(ast::position_tagged const& where_tag, std::string const& error_message,
                    error_type err_type = error_type::parser) const;

    ///
    /// Render the diagnostic error_message. Error source is in most cases the syntax check.
    ///
    /// @param where_tag     The node, which triggers the error.
    /// @param start_label   The start label of the where_tag node.
    /// @param end_label     The complementary end label of the where_tag node.
    /// @param error_message The information error message.
    /// @param err_type      The type of error message.
    ///
    /// @todo Change argument order to be conform to other overload.
    ///
    void operator()(ast::position_tagged const& where_tag, ast::position_tagged const& start_label,
                    ast::position_tagged const& end_label, std::string const& error_message,
                    error_type err_type = error_type::syntax) const;

public:
    ///
    /// Render the diagnostic error_message and increments the error count at context.
    ///
    /// @param error_first Iterator position where the error occurred.
    /// @param error_last Optional Iterator of end position where the error occurred.
    /// @param error_message The information error message.
    /// @param err_type      The type of error message.
    ///
    void operator()(iterator_type error_first, std::optional<iterator_type> error_last,
                    std::string const& error_message,
                    error_type err_type = error_type::syntax) const;

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

// ----------------------------------------------------------------------------
// diagnostic_handler::source_location
// ----------------------------------------------------------------------------
template <typename Iterator>
class diagnostic_handler<Iterator>::source_location {
public:
    source_location(std::string_view file_name, std::size_t line, std::size_t column);

    /// The line number of the error
    std::size_t line() const { return line_; }

    /// The column number of the error.
    std::size_t column() const { return column_; }

    /// The file name
    std::string_view file_name() const { return file_name_; }

private:
    std::string_view file_name_;
    std::size_t line_;
    std::size_t column_;
};

// ----------------------------------------------------------------------------
// diagnostic_handler::formatter
// ----------------------------------------------------------------------------
template <typename Iterator>
class diagnostic_handler<Iterator>::formatter {
public:
    using error_type = diagnostic_handler<Iterator>::error_type;

public:
    ///
    /// @brief Construct a new formatter object
    ///
    /// @param os_ The destination of error message.
    /// @param source_location_ The location of the error to print.
    ///
    /// @todo The error_type specifier must be accessible by the header to allow specific error
    /// messages. Best would be to make it an own non-nested class.
    ///
    /// ToDo: Check for usefull error format, like [GCC's Formatting Error Messages](
    /// https://www.gnu.org/prep/standards/html_node/Errors.html)
    formatter(std::ostream& os_, source_location const& source_location_);

    std::ostream& print_source_location();
    std::ostream& print_error_type(error_type type);
    std::ostream& print_error_message(std::string const& error_message);

private:
    std::ostream& os;
    bool color_output = true;  /// FixMe: ignored, not active
    diagnostic_handler<Iterator>::source_location source_location;
};

}  // namespace ibis::vhdl

namespace ibis::vhdl {

/// Explicit template instantiation declaration
extern template class diagnostic_handler<parser::iterator_type>;

}  // namespace ibis::vhdl
