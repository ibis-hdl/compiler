#pragma once

#include <ibis/vhdl/parser/iterator_type.hpp>

#include <iosfwd>
#include <string>

namespace ibis::vhdl::ast {
struct position_tagged;
}
namespace ibis::vhdl::parser {
template <typename IteratorT>
class position_cache;
}

namespace ibis::vhdl::analyze {

///
/// Syntax/Semantic error handler.
///
/// Opposite to the parser::error_handler, this error handler works on AST/Tree
/// level. All informations tagged at parse time are required for diagnostics.
/// Therefore the parser::position_cache is required. Also the API is slightly
/// different.
///
/// @todo Get "access" to information of node/rule map at parser::on_error_base
///
/// FixMe: Check on use of string_view!
///
/// @todo: Write a formatter class for conrete error reporting, so that users can
///  override the default implementation, e.g.
/// [Controlling output of Boost.Test source location format](
///  https://stackoverflow.com/questions/64618840/controlling-output-of-boost-test-source-location-format)
///
/// @todo Unify parser::error_handler and analyze::error_handler, e.g. on construction
/// time one is using position_cache<iterator_type>::proxy, other without proxy object
/// using reference `position_cache<iterator_type>&`. Maybe use `std::reference_wrapper<proxy>`?
///
template <typename Iterator>
class error_handler {
public:
    using iterator_type = Iterator;
    using position_cache_type = parser::position_cache<iterator_type>;

public:
    ///
    /// Construct a Syntax/Semantic error handler.
    ///
    /// @param os_             Stream to write error and diagnostic messages.
    /// @param position_cache_ Reference to the parser::position_cache.
    /// @param tabs            Tabulator size, required for correct rendering of
    ///                       source code snippet.
    ///
    explicit error_handler(std::ostream& os_, position_cache_type& position_cache_,
                           std::size_t tabs = 4)
        : os{ os_ }
        , position_cache{ position_cache_ }
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
    /// Handle a syntax/semantic error at node and render the diagnostic message
    /// error_message.
    ///
    /// @param where_tag     The node, which triggers the error
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

private:
    std::ostream& os;
    position_cache_type& position_cache;
    std::size_t tab_sz;
};

using error_handler_type = error_handler<parser::iterator_type>;

}  // namespace ibis::vhdl::analyze
