/*
 * position_cache_def.hpp
 *
 *  Created on: 16.08.2018
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_POSITION_CACHE_DEF_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_POSITION_CACHE_DEF_HPP_

#include <eda/vhdl/ast/position_cache.hpp>

#include <boost/locale/encoding_utf.hpp>

#include <cctype>

#include <eda/util/cxx_bug_fatal.hpp>

namespace eda {
namespace vhdl {
namespace ast {

template <typename IteratorT>
std::size_t position_cache<IteratorT>::line_number(
    std::size_t file_id, iterator_type const& pos) const
{
    using char_type = typename std::iterator_traits<iterator_type>::value_type;

    std::size_t line_no{ 1 };
    char_type prev{ 0 };

    for (iterator_type iter{ file_contents(file_id).begin() }; iter != pos; ++iter) {
        auto chr = *iter;
        switch (chr) {
            case '\n':
                if (prev != '\r') {
                    ++line_no;
                }
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

template <typename IteratorT>
std::string position_cache<IteratorT>::current_line(
    std::size_t file_id, iterator_type const& first) const
{
    iterator_type line_end = first;

    while (line_end != file_contents(file_id).end()) {

        auto const chr = *line_end;

        if (chr == '\r' || chr == '\n') {
            break;
        }

        ++line_end;
    }

    using char_type = typename std::iterator_traits<iterator_type>::value_type;

    return boost::locale::conv::utf_to_utf<std::string::value_type>(
        std::basic_string<char_type>{ first, line_end });
}

template <typename IteratorT>
IteratorT position_cache<IteratorT>::get_line_start(std::size_t file_id, iterator_type& pos) const
{
    // make sure err_pos does not point to white space
    auto const skip_whitespace = [](iterator_type& iter, iterator_type const& last) {

        while (iter != last) {

            char const ch = *iter;
            // Note: The behavior is undefined if the value of ch is not
            // representable as unsigned char and is not equal to EOF.
            // [std::isspace](https://en.cppreference.com/w/cpp/string/byte/isspace)
            if (std::isspace(static_cast<unsigned char>(ch)) != 0) {
                ++iter;
            } else {
                break;
            }
        }
    };

    auto[begin, end] = range(file_id);

    skip_whitespace(pos, end);

#if defined(__clang__) && (__clang_major__ == 5) && (__clang_minor__ == 0)
    /* XXX clang's optimizer seems to be too eager, the indicator get wrong. */
    std::string volatile dummy{ pos, end };
#endif

    iterator_type latest{ begin };

    for (iterator_type i = begin; i != pos; ++i) {
        if (*i == '\r' || *i == '\n') {
            latest = i;
        }
    }

    // pos/latest is on the first line
    if (latest == begin) {
        return latest;
    }

    // skip over line breaks
    if (latest != pos) {
        ++latest;
    }
    cxx_assert(latest < end, "iterator range error");

    return latest;
}

} // namespace ast
} // namespace vhdl
} // namespace eda

#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_POSITION_CACHE_DEF_HPP_ */
