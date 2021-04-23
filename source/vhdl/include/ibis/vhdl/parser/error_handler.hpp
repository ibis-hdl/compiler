#pragma once

#include <ibis/vhdl/parser/position_cache.hpp>

#include <ibis/namespace_alias.hpp>  // IWYU pragma: keep

// the following header are required for x3::error_handler_result
#include <boost/spirit/home/x3/support/traits/tuple_traits.hpp>  // IWYU pragma: keep
#include <boost/spirit/home/x3/support/traits/is_variant.hpp>    // IWYU pragma: keep
#include <boost/spirit/home/x3/auxiliary/guard.hpp>

#include <utility>
#include <string>
#include <iosfwd>

namespace ibis::vhdl::parser {

///
/// tag used to get our error handler from the x3::context
///
struct error_handler_tag;  // IWYU pragma: keep

///
/// Parser error handler
///
/// The error handler for parsing works on file level, means a file is read into
/// memory and parsed. Hence not all informations stored in \ref parser::position_cache
/// are required for reporting and diagnosing and a file ID specific proxy
/// object refers to the related informations for convenience.
///
/// Further, the error_handler is used to annotate the AST during parsing, means
/// ties the AST to a vector of iterator positions for the purpose of subsequent
/// semantic error handling when the program is being compiled.
///
/// The concept of tagging doesn't differ from the origin x3::error_handler.
///
/// \see parser::position_cache
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
    using result_type = x3::error_handler_result;

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
    explicit error_handler(std::ostream& os_, position_proxy_type proxy_, std::size_t tabs = 4)
        : os{ os_ }
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
    /// Annotate the AST node
    ///
    /// @param node  AST Node to tag
    /// @param first Begin of iterator position to tag.
    /// @param last  End of iterator position to tag.
    ///
    template <typename NodeT>
    void annotate(NodeT& node, iterator_type const& first, iterator_type const& last)
    {
        position_proxy.annotate(node, first, last);
    }

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
    result_type operator()(iterator_type error_pos, std::string const& error_message) const;

public:
    ///
    /// Access to the file related postion_cache informations.
    ///
    /// @return Reference to the proxy used.
    ///
    position_proxy_type const& current_file() const { return position_proxy; }

private:
    std::ostream& os;
    position_proxy_type position_proxy;
    std::size_t tab_sz;
};

}  // namespace ibis::vhdl::parser
