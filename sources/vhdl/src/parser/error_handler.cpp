/*
 * error_handler.cpp
 *
 *  Created on: 19.07.2018
 *      Author: olaf
 */

#include <eda/compiler/warnings_off.hpp>
#include <boost/spirit/home/x3/support/traits/tuple_traits.hpp>
#include <boost/spirit/home/x3/support/traits/is_variant.hpp>
#include <boost/locale/encoding_utf.hpp>
#include <eda/compiler/warnings_on.hpp>

#include <eda/vhdl/parser/error_handler.hpp>
#include <eda/vhdl/parser/position_cache_def.hpp>
#include <eda/vhdl/parser/iterator_type.hpp>

#include <eda/support/boost/locale.hpp>

#include <eda/color/message.hpp>

#include <iostream>

#include <eda/util/cxx_bug_fatal.hpp>


namespace eda { namespace vhdl { namespace parser {


// AST/parse related error handler (original signature)
template <typename Iterator>
typename error_handler<Iterator>::result_type error_handler<Iterator>::operator()(
    iterator_type error_pos, std::string const& error_message) const
{
    using boost::locale::format;
    using boost::locale::translate;

    os << color::message::error(translate("ERROR")) << " ";

    // location + message
    os << format(translate(
          "in file {1}, line {2}:\n"
          "{3}\n"
          ))
          % file_name()
          % line_number(error_pos)
          % (!error_message.empty() ? error_message : translate("Unspecified Error, Sorry").str())
          ;

    // erroneous source snippet
    iterator_type start = get_line_start(error_pos);
    //print_line(start, last);
    auto const line = current_line(start);
    os << line << "\n";

    // error indicator
    print_indicator(start, error_pos, '_');
    os << "^_" << std::endl;

    return x3::error_handler_result::fail;
}

// error handler for tagged nodes
template <typename Iterator>
typename error_handler<Iterator>::result_type error_handler<Iterator>::operator()(
    ast::position_tagged const& where_tag, std::string const& error_message) const
{
    using boost::locale::format;
    using boost::locale::translate;

    auto const error_iterators = [this](ast::position_tagged const& tagged_node) {
        if (tagged_node.pos_id == ast::position_tagged::MAX_ID) {
            std::cerr << "### WARNING: Node not tagged\n";
        }
        auto range = position_cache.position_of(tagged_node);
        return std::tuple<iterator_type, iterator_type const&>(
            { range.begin(), range.end() }
        );
    };

    auto [error_first, error_last] = error_iterators(where_tag);

    os << color::message::error(translate("ERROR")) << " ";

    // location + message
    os << format(translate(
          "in file {1}, line {2}:\n"
          "{3}\n"
          ))
          % file_name()
          % line_number(error_first)
          % (!error_message.empty() ? error_message : translate("Unspecified Error, Sorry").str())
          ;

    // erroneous source snippet
    iterator_type start = get_line_start(error_first);
    auto const line = current_line(start);
    os << line << "\n";

    // error indicator
    print_indicator(start, error_first, ' ');
    print_indicator(start, error_last,  '~');
    os << translate(" <<-- Here") << std::endl;

    return x3::error_handler_result::fail;
}


template <typename Iterator>
std::string error_handler<Iterator>::file_name() const
{
    if (!filename.empty()) return filename;

    return boost::locale::translate("Unknown File Name", "<unknown>");
}


template <typename Iterator>
void error_handler<Iterator>::print_indicator(iterator_type& first, iterator_type const& last, char symbol) const
{
    for ( ; first != last; ++first) {

        auto const chr = *first;

        if (chr == '\r' || chr == '\n') {
            break;
        }
        else if (chr == '\t') {
            for (std::size_t i = 0; i != tab_sz; ++i)
                os << symbol;
        }
        else {
            os << symbol;
        }
    }
}


}}} // namespace eda.vhdl.parser


namespace eda { namespace vhdl { namespace parser {


// Explicit template instantiation
template class error_handler<parser::iterator_type>;


}}} // namespace eda.vhdl.parser

