#include <ibis/vhdl/error_handler.hpp>
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
class error_handler<Iterator>::source_location {
public:
    source_location(std::string_view file_name, std::size_t line);

    /// The line number of the error
    std::size_t line() const { return line_; }

    /// The file name
    std::string_view file_name() const { return file_name_; }

private:
    std::string_view file_name_;
    std::size_t line_;
};

template <typename Iterator>
error_handler<Iterator>::source_location::source_location(  // --
    std::string_view file_name, std::size_t line)
    : file_name_{ file_name }
    , line_{ line }
{
}

template <typename Iterator>
inline typename error_handler<Iterator>::source_location
error_handler<Iterator>::get_source_location(iterator_type error_pos) const
{
    return source_location(  // --
        position_proxy.file_name(), position_proxy.line_number(error_pos));
}

template <typename Iterator>
class error_handler<Iterator>::formatter {
public:
    using error_type = enum { parser, syntax, semantic, numeric };

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
    formatter(std::ostream& os_, source_location const& source_location_)
        : os{ os_ }
        , source_location{ source_location_ }
    {
    }

    std::ostream& print_source_location()
    {
        using boost::locale::format;
        using boost::locale::translate;

        os << format(translate("in file {1}, line {2}:"))  // --
                  % source_location.file_name()         // {1}
                  % source_location.line()              // {2}
           << '\n';
        return os;
    }

    std::ostream& print_error_type(error_type type)
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
            default:  // unreachable_bug_triggered
                cxx_unreachable_bug_triggered();
        }
        os << ": ";
        return os;
    }

    std::ostream& print_error_message(std::string const& error_message)
    {
        using boost::locale::format;
        using boost::locale::translate;

        os << (!error_message.empty() ? error_message : translate("Unspecified error")) << '\n';
        return os;
    }

private:
    std::ostream& os;
    bool color_output = true;  /// FixMe: ignored, not active
    error_handler::source_location source_location;
};

}  // namespace ibis::vhdl

namespace ibis::vhdl {

// ----------------------------------------------------------------------------
// AST/parse related, expectation error handler
// ----------------------------------------------------------------------------
template <typename Iterator>
typename error_handler<Iterator>::x3_result_type error_handler<Iterator>::operator()(
    iterator_type error_pos, std::string const& error_message) const
{
    using boost::locale::format;
    using boost::locale::translate;

    ++context.errors();

    formatter report(os, get_source_location(error_pos));

    report.print_source_location();
    report.print_error_type(formatter::error_type::parser);
    report.print_error_message(error_message);

    // erroneous source snippet
    iterator_type start = position_proxy.get_line_start(error_pos);
    os << position_proxy.current_line(start);
    os << '\n';

    // error indicator
    using ibis::util::position_indicator;
    os << position_indicator(start, error_pos, tab_sz, ' ') << "^"
       << "\n";

    return x3::error_handler_result::fail;
}

///  ----------------------------------------------------------------------------
/// Syntax and semantic related error handler
/// ----------------------------------------------------------------------------
template <typename Iterator>
void error_handler<Iterator>::operator()(ast::position_tagged const& where_tag,
                                         std::string const& error_message) const
{
    using boost::locale::format;
    using boost::locale::translate;

    cxx_assert(where_tag.is_tagged(), "Node not tagged");

    ++context.errors();

    position_proxy.set_id(where_tag.file_id);

    auto const iterators_of = [&](ast::position_tagged const& tagged_node) {
        auto range = position_proxy.position_of(tagged_node);
        return std::tuple{ (*range).begin(), (*range).end() };
    };

    auto const indicator = [&](auto& start, auto& first, auto& last) {
        return util::make_iomanip([&](std::ostream& os) {
            using ibis::util::position_indicator;
            os << position_indicator(start, first, tab_sz, ' ')
               << position_indicator(start, last, tab_sz, '~');
        });
    };

    auto [error_first, error_last] = iterators_of(where_tag);

    formatter report(os, get_source_location(error_first));

    report.print_source_location();
    report.print_error_type(formatter::error_type::syntax);
    report.print_error_message(error_message);

    // erroneous source snippet
    iterator_type line_start = position_proxy.get_line_start(error_first);
    os << position_proxy.current_line(line_start) << '\n';

    // error indicator
    using ibis::util::position_indicator;
    os << indicator(line_start, error_first, error_last) << translate(" <<-- here\n");
}

template <typename Iterator>
void error_handler<Iterator>::operator()(ast::position_tagged const& where_tag,
                                         ast::position_tagged const& start_label,
                                         ast::position_tagged const& end_label,
                                         std::string const& error_message) const
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
    report.print_error_type(formatter::error_type::syntax);
    report.print_error_message(error_message);

    os << source_snippet(start_label, translate(" <<-- here")) << '\n'
       << "...\n"
       << source_snippet(end_label, translate(" <<-- and here"));

    os << std::endl;
}

template <typename Iterator>
void error_handler<Iterator>::message(std::string const& error_message) const
{
    using boost::locale::format;
    using boost::locale::translate;

    ++context.errors();

    formatter report(os, source_location(position_proxy.file_name(), 1));
    report.print_source_location();
    report.print_error_type(formatter::error_type::syntax);
    report.print_error_message(error_message);
}

}  // namespace ibis::vhdl

// ----------------------------------------------------------------------------
// Explicit template instantiation
// ----------------------------------------------------------------------------
namespace ibis::vhdl {

template class error_handler<parser::iterator_type>;

}  // namespace ibis::vhdl
