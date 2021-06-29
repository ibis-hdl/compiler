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
std::size_t position_cache<IteratorT>::line_number(  // --
    file_id_type file_id, iterator_type const& pos) const
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
std::string_view position_cache<IteratorT>::current_line(  // --
    file_id_type file_id, iterator_type const& first) const
{
    iterator_type line_end = first;

    while (line_end != file_contents(file_id).end()) {
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

    // FixMe [C++20]: constructor by pair of string_view iterators.
    return std::string_view(&(*first), static_cast<std::size_t>(std::distance(first, line_end)));
}

template <typename IteratorT>
IteratorT position_cache<IteratorT>::get_line_start(file_id_type file_id, iterator_type& pos) const
{
    auto [begin, end] = range(file_id);

    iterator_type latest = begin;

    for (iterator_type iter = begin; iter != pos;) {
        if (*iter == '\r' || *iter == '\n') {
            latest = ++iter;
        }
        else {
            ++iter;
        }
    }

    return latest;
}

}  // namespace ibis::vhdl::parser

namespace ibis::vhdl::parser {

// Explicit template instantiation
template class position_cache<parser::iterator_type>;

}  // namespace ibis::vhdl::parser
