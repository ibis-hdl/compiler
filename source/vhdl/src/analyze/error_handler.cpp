#include <eda/vhdl/analyze/error_handler.hpp>
#include <eda/vhdl/ast/position_cache.hpp>
#include <eda/vhdl/ast/util/position_tagged.hpp>

#include <eda/vhdl/parser/iterator_type.hpp>  // for explicit template instantiation

#include <eda/util/string/position_indicator.hpp>

#include <eda/color/message.hpp>
#include <eda/color/facet.hpp>

#include <eda/util/make_iomanip.hpp>
#include <eda/util/cxx_bug_fatal.hpp>

#include <boost/range/iterator_range_core.hpp>
#include <boost/core/ignore_unused.hpp>

#include <boost/locale/format.hpp>
#include <boost/locale/message.hpp>

#include <algorithm>
#include <optional>
#include <ostream>
#include <tuple>

namespace eda::vhdl::analyze {

/**
 * Display the `error_message` with diagnostics, where only the tagged error
 * position `where_tag` is given.
 */
template <typename Iterator>
void error_handler<Iterator>::operator()(ast::position_tagged const& where_tag,
                                         std::string const& error_message) const
{
    using boost::locale::format;
    using boost::locale::translate;

    cxx_assert(where_tag.is_tagged(), "Node not tagged");

    auto current_file = position_cache.handle(where_tag.file_id);

    auto const iterators_of = [&current_file](ast::position_tagged const& tagged_node) {
        auto range = current_file.position_of(tagged_node);
        return std::tuple{ (*range).begin(), (*range).end() };
    };

    auto const indicator = [&](auto& start, auto& first, auto& last) {
        return util::make_iomanip([&](std::ostream& os) {
            using eda::util::position_indicator;
            os << position_indicator(start, first, tab_sz, ' ')
               << position_indicator(start, last, tab_sz, '~');
        });
    };

    auto [error_first, error_last] = iterators_of(where_tag);

    os << format(translate("in file {1}, line {2}:"))  // --
              % current_file.file_name()               // {1}
              % current_file.line_number(error_first)  // {2}
       << '\n';

    os << color::message::error(translate("Syntax ERROR")) << ": "  // --
       << (!error_message.empty() ? error_message : translate("Unspecified Error, Sorry")) << '\n';

    // erroneous source snippet
    iterator_type line_start = current_file.get_line_start(error_first);
    os << current_file.current_line(line_start);
    os << std::endl;

    // error indicator
    using eda::util::position_indicator;
    os << indicator(line_start, error_first, error_last) << translate(" <<-- here\n");
}

/**
 * Display the `error_message` with diagnostics, where the tagged error
 * position `where_tag` and the associated `start_label` and `stop label` are
 * given.
 */
template <typename Iterator>
void error_handler<Iterator>::operator()(ast::position_tagged const& where_tag,
                                         ast::position_tagged const& start_label,
                                         ast::position_tagged const& end_label,
                                         std::string const& error_message) const
{
    using boost::locale::format;
    using boost::locale::translate;

    cxx_assert(where_tag.is_tagged(), "Node not tagged");
    cxx_assert(start_label.is_tagged(), "Node/StartLabel not tagged");
    cxx_assert(end_label.is_tagged(), "Node/EndLabel not tagged");

    auto current_file = position_cache.handle(where_tag.file_id);

    /* at ill-formed label pairs (e.g. end, but no start label given) nodes
     * aren't tagged appropriate. */
    auto const iterators_of = [&current_file](ast::position_tagged const& tagged_node) {
        auto range = current_file.position_of(tagged_node);
        if (range) {
            return std::tuple{ (*range).begin(), (*range).end(), true /* valid */ };
        }
        return std::tuple{ iterator_type{}, iterator_type{}, false /* not-valid */ };
    };

    auto const indicator = [&](auto& start, auto& first, auto& last) {
        return util::make_iomanip([&](std::ostream& os) {
            using eda::util::position_indicator;
            os << position_indicator(start, first, tab_sz, ' ')
               << position_indicator(start, last, tab_sz, '~');
        });
    };

    auto const source_snippet = [&](ast::position_tagged const& tagged_node,
                                    auto const& annotation) {
        return util::make_iomanip([&](std::ostream& os) {
            auto [first, last, valid] = iterators_of(tagged_node);
            if (valid) {
                iterator_type line_start = current_file.get_line_start(first);
                os << current_file.current_line(line_start) << '\n'
                   << indicator(line_start, first, last) << annotation;
            }
        });
    };

    auto [error_first, error_last, valid] = iterators_of(where_tag);

    boost::ignore_unused(error_last);
    boost::ignore_unused(valid);

    os << format(translate("in file {1}, line {2}:"))  // --
              % current_file.file_name()               // {1}
              % current_file.line_number(error_first)  // {2}
       << '\n';

    os << color::message::error(translate("Syntax ERROR")) << ": "
       << (!error_message.empty() ? error_message : translate("Unspecified Error, Sorry")) << '\n';

    os << source_snippet(start_label, translate(" <<-- here")) << '\n'
       << "...\n"
       << source_snippet(end_label, translate(" <<-- and here"));

    os << std::endl;
}

}  // namespace eda::vhdl::analyze

namespace eda::vhdl::analyze {

// Explicit template instantiation
template class error_handler<parser::iterator_type>;

}  // namespace eda::vhdl::analyze