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
    , indicator_symbol{ indicator_ }
    {}

    std::ostream& print(std::ostream& os) const {

        for ( ; first != last; ++first) {

            auto const ch = *first;

            if (ch == '\r' || ch == '\n') {
                break;
            }
            else if (ch == '\t') {
                for (unsigned i = 0; i != tab_size; ++i)
                    os << indicator_symbol;
            }
            else {
                os << indicator_symbol;
            }
        }

        return os;
    }

    iterator_type mutable               first;
    iterator_type const&                last;
    unsigned                            tab_size;
    char                                indicator_symbol;
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

            auto const ch = *end;

            if (ch == '\r' || ch == '\n') {
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
// modifies error_pos
template <class Iterator>
Iterator get_line_start(Iterator const& first, Iterator const& last, Iterator& error_pos)
{
    // make sure err_pos does not point to white space
    auto const skip_whitespace = [](auto& err_pos, auto const& last_) {

        while (err_pos != last_) {

            char const ch = *err_pos;
            // Note: The behavior is undefined if the value of ch is not
            // representable as unsigned char and is not equal to EOF.
            // [std::isspace](https://en.cppreference.com/w/cpp/string/byte/isspace)
            if (std::isspace(static_cast<unsigned char>(ch))) {
                ++err_pos;
            }
            else {
                break;
            }
        }
    };

    skip_whitespace(error_pos, last);

    Iterator latest{ first };

    for (Iterator i = first; i != error_pos; ++i) {
        if (*i == '\r' || *i == '\n') {
            latest = i;
        }
    }

    if (latest != error_pos) {
        // skip over line break
        ++latest;
    }

    return latest;
}

////////////////////////////////////////////////////////////////////
template <typename Iterator>
std::size_t line_number(Iterator const& first, Iterator const& it) {

    std::size_t line_no { 1 };
    typename std::iterator_traits<Iterator>::value_type prev { 0 };

    for (Iterator pos = first; pos != it; ++pos) {
        auto const ch = *pos;
        switch (ch) {
            case '\n':
                if (prev != '\r') ++line_no;
                break;
            case '\r':
                ++line_no;
                break;
            default:
                break;
        }
        prev = ch;
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

    auto start = get_line_start(first, last, error_pos);


    std::cout << "[Error]"
              << " in " << filename << ", line " << line_number(first, error_pos) << ":\n"
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

    auto start = get_line_start(first, last, error_first);

    std::cout << "[Error]"
              << " in " << filename << ", line " << line_number(first, error_first) << ":\n"
              << message << "\n";

    std::cout << print_line(start, last) << "\n";

    std::cout << indicator(error_first, error_last, tab_size, ' ')
              << "^"
              << indicator(start, error_last - 1, tab_size, '~')
              << "\n"
              ;
}

////////////////////////////////////////////////////////////////////
int main()
{
    std::string const string{ "The quick brown\nfox\tjumps over\nthe lazy dog" };
    std::string const err_str{ "lazy" };

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


    error_handler(first, last, error_first, error_last, "Shit happens (tagged)");
    std::cout << "--------------------------------------------------\n";
    error_handler(first, last, error_first, "Shit happens (x3)");
    std::cout << "\n";
}



