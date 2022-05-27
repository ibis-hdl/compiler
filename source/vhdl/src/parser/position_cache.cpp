#include <ibis/vhdl/parser/position_cache.hpp>
#include <ibis/vhdl/parser/iterator_type.hpp>  // for explicit template instantiation

#include <ibis/util/cxx_bug_fatal.hpp>

#include <cctype>
#include <iterator>
#include <string>
#include <iosfwd>

namespace ibis::vhdl::parser {

template <typename IteratorT>
std::tuple<std::size_t, std::size_t> position_cache<IteratorT>::line_column_number(  // --
    file_id_type file_id, iterator_type const& pos, std::size_t tab_sz) const
{
    // based on [.../x3/support/utility/error_reporting.hpp:position(...)](
    // https://github.com/boostorg/spirit/blob/master/include/boost/spirit/home/x3/support/utility/error_reporting.hpp)
    // Further reading at [What is the unit of a text column number?](
    // https://www.foonathan.net/2021/02/column/#content).

    using char_type = typename std::iterator_traits<iterator_type>::value_type;

    std::size_t line_no = 1;
    std::size_t col_no = 1;
    char_type chr_prev = 0;

    for (iterator_type iter = file_contents(file_id).begin(); iter != pos; ++iter) {
        auto const chr = *iter;
        switch (chr) {
            case '\n':
                if (chr_prev != '\r') {
                    ++line_no;
                    col_no = 1;
                }
                break;
            case '\r':
                ++line_no;
                col_no = 1;
                break;
            case '\t':
                // https://github.com/boostorg/spirit/blob/master/include/boost/spirit/home/support/iterators/line_pos_iterator.hpp
                col_no += tab_sz - (col_no - 1) % tab_sz;
                break;
            default:
                // On UTF8, skip code points, VHDL is fortunately ASCII.
                ++col_no;
                break;
        }
        chr_prev = chr;
    }

    return { line_no, col_no };
}

template <typename IteratorT>
std::string_view position_cache<IteratorT>::current_line(  // --
    file_id_type file_id, iterator_type const& first) const
{
    // based on [.../x3/support/utility/error_reporting.hpp:print_line(...)](
    // https://github.com/boostorg/spirit/blob/master/include/boost/spirit/home/x3/support/utility/error_reporting.hpp)

    auto line_end = first;
    auto const end = file_contents(file_id).end();

    while (line_end != end) {
        auto const chr = *line_end;

        if (chr == '\r' || chr == '\n') {
            break;
        }

        ++line_end;
    }

    // FixMe: Generally, UTF8 in VHDL is difficult, see also [VHDL file encoding](
    // https://insights.sigasi.com/tech/vhdl-file-encoding/). The X3 way is using:
    // @code{.cpp}
    // std::basic_string<char_type> line{start, end};
    // err_out << x3::to_utf8(line) << std::endl;
    // @endcode

    // FixMe [C++20]: constructor by pair of string_view iterators.
    auto const count = static_cast<std::size_t>(std::distance(first, line_end));
    return std::string_view(&(*first), count);
}

template <typename IteratorT>
IteratorT position_cache<IteratorT>::get_line_start(file_id_type file_id, iterator_type& pos) const
{
    auto [begin, end] = range(file_id);

    // based on [.../x3/support/utility/error_reporting.hpp:get_line_start(...)](
    // https://github.com/boostorg/spirit/blob/master/include/boost/spirit/home/x3/support/utility/error_reporting.hpp)
    auto last_iter = begin;

    for (auto iter = begin; iter != pos;) {
        if (*iter == '\r' || *iter == '\n') {
            last_iter = ++iter;
        }
        else {
            ++iter;
        }
    }

    return last_iter;
}

}  // namespace ibis::vhdl::parser

namespace ibis::vhdl::parser {

// Explicit template instantiation
template class position_cache<parser::iterator_type>;

}  // namespace ibis::vhdl::parser
