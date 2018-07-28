/*
 * error_handler.cpp
 *
 *  Created on: 19.07.2018
 *      Author: olaf
 */

#include <eda/util/compiler_warnings_off.hpp>
#include <boost/spirit/home/x3/support/traits/tuple_traits.hpp>
#include <boost/spirit/home/x3/support/traits/is_variant.hpp>
#include <boost/locale/encoding_utf.hpp>
#include <eda/util/compiler_warnings_on.hpp>

#include <eda/vhdl/parser/error_handler.hpp>
#include <eda/vhdl/parser/iterator_type.hpp>

#include <eda/support/boost/locale.hpp>

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

    auto const [first, last] = position_cache.range();

    // location + message
    os << format(translate(
          "In file {1}, line {2}:\n"
          "{3}\n"
          ))
          % file_name()
          % line_number(error_pos)
          % (!error_message.empty() ? error_message : translate("Unspecified Error, Sorry").str())
          ;

    // erroneous source snippet
    iterator_type start = get_line_start(error_pos);
    print_line(start, last);

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

    auto const [first, last] = position_cache.range();
    auto [error_first, error_last] = error_iterators(where_tag);

    // location + message
    os << format(translate(
          "In file {1}, line {2}:\n"
          "{3}\n"
          ))
          % file_name()
          % line_number(error_first)
          % (!error_message.empty() ? error_message : translate("Unspecified Error, Sorry").str())
          ;

    // erroneous source snippet
    iterator_type start = get_line_start(error_first);
    print_line(start, last);

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
std::size_t error_handler<Iterator>::line_number(iterator_type const& pos) const
{
    std::size_t line_no { 1 };
    typename std::iterator_traits<iterator_type>::value_type prev { 0 };

    auto const [first, last] = position_cache.range();
    boost::ignore_unused(last);

    for (iterator_type iter{ first} ; iter != pos; ++iter) {
        auto chr = *iter;
        switch (chr) {
            case '\n':
                if (prev != '\r') ++line_no;
                break;
            case '\r':
                ++line_no;
                break;
            default:
                break;
        }
        prev = chr;
    }

    return line_no;
}


template <typename Iterator>
void error_handler<Iterator>::print_line(iterator_type const& first, iterator_type const& last) const
{
    auto end = first;

    while (end != last) {

        auto const chr = *end;

        if (chr == '\r' || chr == '\n') {
            break;
        }
        else {
            ++end;
        }
    }

    std::basic_string<parser::char_type> line{ first, end };

    os << boost::locale::conv::utf_to_utf<char>(line) << "\n";
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


template <class Iterator>
Iterator error_handler<Iterator>::get_line_start(iterator_type& pos) const
{
    // make sure err_pos does not point to white space
    auto const skip_whitespace = [](iterator_type& iter, iterator_type const& last) {

        while (iter != last) {

            char const ch = *iter;
            // Note: The behavior is undefined if the value of ch is not
            // representable as unsigned char and is not equal to EOF.
            // [std::isspace](https://en.cppreference.com/w/cpp/string/byte/isspace)
            if (std::isspace(static_cast<unsigned char>(ch))) {
                ++iter;
            }
            else {
                break;
            }
        }
    };

    auto const [first, last] = position_cache.range();

    skip_whitespace(pos, last);

    iterator_type latest{ first };

    for (iterator_type i = first; i != pos; ++i) {
        if (*i == '\r' || *i == '\n') {
            latest = i;
        }
    }

    // skip over line breaks
    if (latest != pos) {
        ++latest;
    }

    cxx_assert(latest < last, "iterator range error");

    return latest;
}


}}} // namespace eda.vhdl.parser


namespace eda { namespace vhdl { namespace parser {

// Explicit template instantiation
template class error_handler<parser::iterator_type>;

}}} // namespace eda.vhdl.parser

