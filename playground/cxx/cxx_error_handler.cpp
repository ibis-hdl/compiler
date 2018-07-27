/*
 * cxx_error_handler.cpp
 *
 *  Created on: 27.07.2018
 *      Author: olaf
 */
// https://wandbox.org/permlink/5KeL2ZL82ERCAFxA

#include <iostream>
#include <string>
#include <iterator>

////////////////////////////////////////////////////////////////////
template<typename IteratorT>
struct indicator
{
    typedef IteratorT                   iterator_type;

    indicator(iterator_type first_, iterator_type const& last_, unsigned tab_size_, char indicator_)
    : first{ first_ }
    , last{ last_ }
    , tab_size{ tab_size_ }
    , indicator_char{ indicator_ }
    {}

    std::ostream& print(std::ostream& os) const {

        for ( ; first != last; ++first) {

            auto const chr = *first;

            if (chr == '\r' || chr == '\n') {
                break;
            }
            else if (chr == '\t') {
                for (unsigned i = 0; i != tab_size; ++i)
                    os << indicator_char;
            }
            else {
                os << indicator_char;
            }
        }

        return os;
    }

    iterator_type mutable               first;
    iterator_type const&                last;
    unsigned                            tab_size;
    char                                indicator_char;
};


template<typename IteratorT>
std::ostream& operator<<(std::ostream& os, indicator<IteratorT> const& indicator_) {
    return indicator_.print(os);
}

////////////////////////////////////////////////////////////////////
template <typename IteratorT>
struct print_line
{
    typedef IteratorT                   iterator_type;

    print_line(iterator_type const& first_, iterator_type const& last_)
    : first{ first_ }
    , last{ last_ }
    {}

    std::ostream& print(std::ostream& os) const
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

        os << std::string{ first, end };
        return os;
    }

    iterator_type const&                first;
    iterator_type const&                last;
};


template<typename IteratorT>
std::ostream& operator<<(std::ostream& os, print_line<IteratorT> const& print_line_) {
    return print_line_.print(os);
}


////////////////////////////////////////////////////////////////////
template <class Iterator>
Iterator get_line_start(Iterator first, Iterator const& pos)
{
    Iterator latest{ first };

    for (Iterator i = first; i != pos; ++i) {
        if (*i == '\r' || *i == '\n') {
            latest = i;
        }
    }

    return latest;
}

////////////////////////////////////////////////////////////////////
template <typename Iterator>
void skip_whitespace(Iterator& err_pos, Iterator const& last)
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

////////////////////////////////////////////////////////////////////
template <typename Iterator>
std::size_t line_number(Iterator const& first, Iterator const& it) {

    std::size_t line_no { 1 };
    typename std::iterator_traits<Iterator>::value_type prev { 0 };

    for (Iterator pos = first; pos != it; ++pos) {
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

template <typename Iterator>
void error_handler(Iterator const& first, Iterator const& last,
                   Iterator        error_pos,
                   std::string const& message)
{
    unsigned const tab_size = 4;
    std::string filename{"TestInput"};

    skip_whitespace(error_pos, last);

    auto start = get_line_start(first, error_pos);
    if (start != first) {
        std::cerr << "Adjust start iterator\n";
        ++start;
    }


    std::cout << "[Error]"
              << " in " << filename << ", line " << line_number(first, error_pos) << ": "
              << message << "\n";
    std::cout << print_line(start, last) << "\n";
    std::cout << indicator(start, error_pos, tab_size, '_')
              << "^_\n"
              ;
}

template <typename Iterator>
void error_handler(Iterator const& first, Iterator const& last,
                   Iterator        error_first, Iterator const& error_last, // tagged
                   std::string const& message)
{
    unsigned const tab_size = 4;
    std::string filename{"TestInput"};

    skip_whitespace(error_first, last);

    auto start = get_line_start(first, error_first);
    if (start != first) {
        std::cerr << "Adjust start iterator\n";
        ++start;
    }

    std::cout << "[Error]"
              << " in " << filename << ", line " << line_number(first, error_first) << ": "
              << message << "\n";

    std::cout << print_line(start, last) << "\n";

    std::cout << indicator(error_first, error_last, tab_size, ' ')
              << indicator(start, error_last, tab_size, '~')
              << " <<< Here\n"
              ;
}

////////////////////////////////////////////////////////////////////
int main()
{
    std::string string{ "The quick brown\nfox\tjumps over\nthe lazy dog" };
    std::string err_str{ "lazy" };

    auto first = string.begin();
    auto const& last = string.end();

    auto error_first = [&]{
        auto iter = string.begin();
        std::advance(iter, string.find(err_str));
        return iter;
    }();

    auto const error_last = [&]{
        auto iter = string.begin();
        std::advance(iter, string.find(err_str) + err_str.size());
        return iter;
    }();


    error_handler(first, last, error_first, error_last, "Shit happens");
    std::cout << "--------------------------------------------------\n";
    error_handler(first, last, error_first, "Shit happens");
    std::cout << "\n";
}



