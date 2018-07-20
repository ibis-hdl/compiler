/*
 * error_handler.cpp
 *
 *  Created on: 19.07.2018
 *      Author: olaf
 */

#include <eda/utils/compiler_warnings_off.hpp>
#include <boost/spirit/home/x3/support/traits/tuple_traits.hpp>
#include <boost/spirit/home/x3/support/traits/is_variant.hpp>
#include <boost/locale/encoding_utf.hpp>
#include <eda/utils/compiler_warnings_on.hpp>

#include <eda/vhdl/parser/error_handler.hpp>
#include <eda/vhdl/parser/common_types.hpp>

#include <eda/support/boost/locale.hpp>

#include <iostream>


namespace eda { namespace vhdl { namespace parser {


#pragma GCC diagnostic push // -------------------------------------------------
#pragma GCC diagnostic ignored "-Wunused-parameter"

#if 0
template <typename Iterator>
typename error_handler<Iterator>::result_type error_handler<Iterator>::operator()(
    ast::position_tagged const& where_tag, std::string const& message) const
{
    auto const where = position_cache.position_of(where_tag);
    return (*this)(where, message);
}


template <typename Iterator>
typename error_handler<Iterator>::result_type error_handler<Iterator>::operator()(
    ast::position_tagged const& where_tag, std::string const& which_rule,
    std::string const& message) const
{
    auto const where = position_cache.position_of(where_tag);
    return (*this)(where, which_rule, message);
}


template <typename Iterator>
typename error_handler<Iterator>::result_type error_handler<Iterator>::operator()(
    range_type const& where, std::string const& which_rule,
    std::string const& error_message) const
{
    auto [first, last] = position_cache.iterator_range();
    auto err_first = std::begin(where);


    return x3::error_handler_result::fail;
}


template <typename Iterator>
typename error_handler<Iterator>::result_type error_handler<Iterator>::operator()(
    range_type const& where, std::string const& error_message) const
{
//    auto [first, last] = position_cache.iterator_pair();
//    auto err_first = std::begin(where);

    return x3::error_handler_result::fail;
}
#else
// AST/parse related error handler (original signature)
template <typename Iterator>
typename error_handler<Iterator>::result_type error_handler<Iterator>::operator()(
    iterator_type error_pos, std::string const& error_message) const
{
    using boost::locale::translate;

    auto [first, last] = position_cache.iterator_range();

    // make sure err_pos does not point to white space
    skip_whitespace(error_pos, last);
    print_file_line(error_pos);

    if (!error_message.empty()) {
        os << error_message << std::endl;
    }
    else {
        os << translate("Sorry, no concrete error description") << std::endl;
    }

    iterator_type start = get_line_start(first, error_pos);

    if (start != first)
        ++start;

    print_line(start, last);

    print_indicator(start, error_pos, '_');
    os << "^_" << std::endl;

    return x3::error_handler_result::fail;
}

template <typename Iterator>
typename error_handler<Iterator>::result_type error_handler<Iterator>::operator()(
    ast::position_tagged const& where_tag, std::string const& error_message) const
{
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
    auto [first, last] = position_cache.iterator_range();


    // make sure error_pos does not point to white space
    skip_whitespace(error_first, last);
    print_file_line(error_first);

    if (!error_message.empty()) {
        os << error_message << std::endl;
    }
    else {
        os << translate("Sorry, no concrete error description") << std::endl;
    }

    iterator_type start = get_line_start(first, error_first);

    if (start != first)
        ++start;

    print_line(start, last);

    print_indicator(start, error_first, ' ');
    print_indicator(start, error_last,  '~');
    os << translate(" <<-- Here") << std::endl;

    return x3::error_handler_result::fail;
}
#endif

#pragma GCC diagnostic pop  // -------------------------------------------------


template <typename Iterator>
void error_handler<Iterator>::print_file_line(iterator_type const& iter) const
{
    auto const line_number = [this](iterator_type const& iter) {

        std::size_t line_no { 1 };
        typename std::iterator_traits<iterator_type>::value_type prev { 0 };

        for (iterator_type pos = position_cache.first(); pos != iter; ++pos) {
            auto chr = *pos;
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
    };

    using boost::locale::format;
    using boost::locale::translate;

    os << format(translate(
          "In file {0}, line {1}:"
          ))
          % (!file_name().empty() ? file_name() : "<unknown>")
          % line_number(iter)
          ;
}


template <typename Iterator>
void error_handler<Iterator>::print_line(iterator_type first, iterator_type const& last) const
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

    typedef typename std::iterator_traits<Iterator>::value_type char_type;
    std::basic_string<char_type> line{ first, end };

    os << boost::locale::conv::utf_to_utf<char>(line) << std::endl;
}


template <typename Iterator>
void error_handler<Iterator>::print_indicator(iterator_type& first, iterator_type const& last, char indicator) const
{
    for ( ; first != last; ++first) {

        auto const chr = *first;

        if (chr == '\r' || chr == '\n') {
            break;
        }
        else if (chr == '\t') {
            for (unsigned i = 0; i != tab_sz; ++i)
                os << indicator;
        }
        else {
            os << indicator;
        }
    }
}


template <typename Iterator>
void error_handler<Iterator>::skip_whitespace(iterator_type& err_pos, iterator_type const& last) const
{
    // make sure err_pos does not point to white space
    while (err_pos != last) {

        char c = *err_pos;

        if (std::isspace(c)) {
            ++err_pos;
        }
        else {
            break;
        }
    }
}


template <class Iterator>
inline Iterator error_handler<Iterator>::get_line_start(iterator_type first, iterator_type const& pos) const
{
    iterator_type latest = first;

    for (iterator_type i = first; i != pos; ++i) {
        if (*i == '\r' || *i == '\n') {
            latest = i;
        }
    }

    return latest;
}


}}} // namespace eda.vhdl.parser


namespace eda { namespace vhdl { namespace parser {

// Explicit template instantiation
template class error_handler<parser::iterator_type>;

}}} // namespace eda.vhdl.parser

