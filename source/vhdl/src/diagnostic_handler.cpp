#include <ibis/vhdl/diagnostic_handler.hpp>
#include <ibis/vhdl/context.hpp>

#include <ibis/vhdl/parser/iterator_type.hpp>  // for explicit template instantiation

#include <ibis/util/string/position_indicator.hpp>

#include <ibis/color/message.hpp>
#include <ibis/color/facet.hpp>

#include <ibis/util/make_iomanip.hpp>
#include <ibis/util/cxx_bug_fatal.hpp>

#include <boost/locale/format.hpp>
#include <boost/locale/message.hpp>

#include <boost/range/iterator_range_core.hpp>

#include <algorithm>
#include <iostream>

namespace ibis::vhdl {

template <typename Iterator>
diagnostic_handler<Iterator>::source_location::source_location(  // --
    std::string_view file_name, std::size_t line, std::size_t column)
    : file_name_{ file_name }
    , line_{ line }
    , column_{ column }
{
}

template <typename Iterator>
inline typename diagnostic_handler<Iterator>::source_location
diagnostic_handler<Iterator>::get_source_location(iterator_type error_pos) const
{
    auto const [line, column] = position_proxy.line_column_number(error_pos, tab_sz);
    return source_location(  // --
        position_proxy.file_name(), line, column);
}

// ----------------------------------------------------------------------------
// diagnostic_handler::formatter
// ----------------------------------------------------------------------------
template <typename Iterator>
diagnostic_handler<Iterator>::formatter::formatter(
    std::ostream& os_, diagnostic_handler<Iterator>::source_location const& source_location_)
    : os{ os_ }
    , source_location{ source_location_ }
{
}

template <typename Iterator>
std::ostream& diagnostic_handler<Iterator>::formatter::print_source_location()
{
    using boost::locale::format;
    using boost::locale::translate;

    // See GNU standard of [Formatting Error Messages](
    // https://www.gnu.org/prep/standards/html_node/Errors.html)

    os << format("{1}:{2}:{3}: ")            // --
              % source_location.file_name()  // {1}
              % source_location.line()       // {2}
              % source_location.column()     // {3}
        ;
    return os;
}

template <typename Iterator>
std::ostream& diagnostic_handler<Iterator>::formatter::print_error_type(error_type type)
{
    using boost::locale::format;
    using boost::locale::translate;

    switch (type) {
        case error_type::parser:
            os << color::message::error(translate("parse error"));
            break;
        case error_type::syntax:
            os << color::message::error(translate("syntax error"));
            break;
        case error_type::semantic:
            os << color::message::error(translate("semantic error"));
            break;
        case error_type::numeric:
            os << color::message::error(translate("numeric error"));
            break;
        case error_type::unspecific:
            os << color::message::error(translate("error"));
            break;
        default:  // unreachable_bug_triggered
            cxx_unreachable_bug_triggered();
    }
    os << ": ";
    return os;
}

template <typename Iterator>
std::ostream& diagnostic_handler<Iterator>::formatter::print_error_message(
    std::string const& error_message)
{
    using boost::locale::format;
    using boost::locale::translate;

    os << (!error_message.empty() ? error_message : translate("Unspecified error")) << '\n';
    return os;
}

}  // namespace ibis::vhdl

namespace ibis::vhdl {

// ----------------------------------------------------------------------------
// diagnostic_handler - AST/parse related, expectation error handler
// ----------------------------------------------------------------------------
template <typename Iterator>
void diagnostic_handler<Iterator>::operator()(iterator_type error_pos,
                                              std::string const& error_message,
                                              error_type err_type) const
{
    using boost::locale::format;
    using boost::locale::translate;

    operator()(error_pos, std::nullopt, error_message, err_type);
}

///  ----------------------------------------------------------------------------
/// Syntax and semantic related error handler
/// ----------------------------------------------------------------------------
template <typename Iterator>
void diagnostic_handler<Iterator>::operator()(ast::position_tagged const& where_tag,
                                              std::string const& error_message,
                                              error_type err_type) const
{
    using boost::locale::format;
    using boost::locale::translate;

    // the node must be tagged before
    cxx_assert(where_tag.is_tagged(), "Node not tagged");

    // It's assumed, that the parser's position cache proxy is configured to have the same file id
    // tagged as the node holds. I'm not sure about implications if not; otherwise adjust the file
    // id of the proxy by:
    // position_proxy.set_id(where_tag.file_id);
    // FixMe: cxx_assert(where_tag.file_id == position_proxy.id(), "unexpected file ID");

    auto const where_opt = position_proxy.position_of(where_tag);

    // It's assumed, that only tagged nodes deliver error messages.
    // FixMe: remove optional return from position_cache::position_of()
    cxx_assert(where_opt.has_value(), "erroneous node has no ast::position_tagged base.");

    operator()((*where_opt).begin(), (*where_opt).end(), error_message, err_type);
}

template <typename Iterator>
void diagnostic_handler<Iterator>::operator()(ast::position_tagged const& where_tag,
                                              ast::position_tagged const& start_label,
                                              ast::position_tagged const& end_label,
                                              std::string const& error_message,
                                              error_type err_type) const
{
    using boost::locale::format;
    using boost::locale::translate;

    // check on applied tagging, related to position_cache
    cxx_assert(where_tag.is_tagged(), "Node not tagged");
    cxx_assert(start_label.is_tagged(), "Node/StartLabel not tagged");
    cxx_assert(end_label.is_tagged(), "Node/EndLabel not tagged");

    ++context.errors();

    position_proxy.set_id(where_tag.file_id);

    // at ill-formed label pairs (e.g. end, but no start label given) nodes
    // aren't tagged appropriate.
    auto const iterators_of = [&](ast::position_tagged const& tagged_node) {
        auto range = position_proxy.position_of(tagged_node);
        if (range) {
            return std::tuple{ (*range).begin(), (*range).end(), true /* valid */ };
        }
        return std::tuple{ iterator_type{}, iterator_type{}, false /* invalid */ };
    };

    auto const indicator = [&](auto& start, auto& first, auto& last) {
        return util::make_iomanip([&](std::ostream& os) {
            using ibis::util::position_indicator;
            os << position_indicator(start, first, tab_sz, ' ')
               << position_indicator(start, last, tab_sz, '~');
        });
    };

    auto const source_snippet = [&](ast::position_tagged const& tagged_node,
                                    auto const& annotation) {
        return util::make_iomanip([&](std::ostream& os) {
            auto [first, last, valid] = iterators_of(tagged_node);
            if (valid) {
                iterator_type line_start = position_proxy.get_line_start(first);
                os << position_proxy.current_line(line_start) << '\n'
                   << indicator(line_start, first, last) << annotation;
            }
        });
    };

    auto [error_first, error_last, valid] = iterators_of(where_tag);

    // FixMe: validity of error_{first,last} iterators aren't checked! Neverstheless, it's always
    // valid since this function signature allows only ast::position_tagged node, see implementation
    // of iterators_of()

    formatter report(os, get_source_location(error_first));

    report.print_source_location();
    report.print_error_type(err_type);
    report.print_error_message(error_message);

    os << source_snippet(start_label, translate(" <<-- here")) << '\n'
       << "...\n"
       << source_snippet(end_label, translate(" <<-- and here"));

    os << std::endl;
}

template <typename Iterator>
void diagnostic_handler<Iterator>::operator()(iterator_type error_first,
                                              std::optional<iterator_type> error_last,
                                              std::string const& error_message,
                                              error_type err_type) const
{
    using boost::locale::format;
    using boost::locale::translate;

    ++context.errors();

    formatter report(os, get_source_location(error_first));

    report.print_source_location();
    report.print_error_type(err_type);
    report.print_error_message(error_message);

    // erroneous source snippet
    iterator_type line_start = position_proxy.get_line_start(error_first);
    os << position_proxy.current_line(line_start) << '\n';

    // error indicator
    using ibis::util::position_indicator;
    if (error_last.has_value()) {
        os << position_indicator(line_start, error_first, tab_sz, ' ')
           << position_indicator(line_start, error_last.value(), tab_sz, '~')  // --
           << " <<-- Here" << std::endl;
    }
    else {
        os << position_indicator(line_start, error_first, tab_sz, ' ')  // --
           << "^" << std::endl;
    }
}

}  // namespace ibis::vhdl

// ----------------------------------------------------------------------------
// Explicit template instantiation
// ----------------------------------------------------------------------------
namespace ibis::vhdl {

template class diagnostic_handler<parser::iterator_type>;

}  // namespace ibis::vhdl
