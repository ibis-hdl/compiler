#include <ibis/vhdl/parser/position_cache.hpp>
#include <ibis/vhdl/parser/iterator_type.hpp>  // for explicit template instantiation

#include <ibis/util/cxx_bug_fatal.hpp>

// #include <boost/locale/encoding_utf.hpp>

#include <cctype>
#include <iterator>
#include <string>
#include <iosfwd>

namespace ibis::vhdl::parser {

template <typename IteratorT>
std::tuple<std::size_t, std::size_t> position_cache<IteratorT>::line_column_number(  // --
    file_id_type file_id, iterator_type const& pos, std::size_t tab_sz) const
{
    using char_type = typename std::iterator_traits<iterator_type>::value_type;

    std::size_t line_no = 1;
    std::size_t col_no = 1;
    char_type chr_prev = 0;

    // The implementation is based on the original one from Spirit X3. Further reading
    // is done at [What is the unit of a text column number?](
    // https://www.foonathan.net/2021/02/column/#content).

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
                // Note:
                // https://github.com/boostorg/spirit/blob/master/include/boost/spirit/home/support/iterators/line_pos_iterator.hpp
                // has get_column() with column += tabs - (column - 1) % tabs;
                // not sure about the intention of trailing expression.
                col_no += tab_sz;
                break;
            default:
                // On UTF8, skip code points, VHDL is fortunately ASCII.
                // skip_code_point(iter, end);
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
    //     return boost::locale::conv::utf_to_utf<std::string::value_type>(
    //         std::string_view(&(*first), std::distance(first, line_end)));
    // @endcode
    // but with using ```std::string_view``` this isn't possible any more due to
    // use of this. Personally, the intention of converting UTF to UTF isn't clear.
    // Further, Starting with Spirit V3.0.7 (Boost V1.74.0) dependence on Boost.Locale
    // is ceased (replace locale::conv::utf_to_utf with x3::to_utf8)

    auto const count = static_cast<std::size_t>(std::distance(first, line_end));

    // FixMe [C++20]: constructor by pair of string_view iterators.
    return std::string_view(&(*first), count);
}

template <typename IteratorT>
IteratorT position_cache<IteratorT>::get_line_start(file_id_type file_id, iterator_type& pos) const
{
    auto [begin, end] = range(file_id);

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
