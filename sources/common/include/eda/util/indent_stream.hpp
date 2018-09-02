/*
 * indent_stream.hpp
 *
 *  Created on: 27.04.2017
 *      Author: olaf
 */

#ifndef SOURCES_COMMON_INCLUDE_EDA_UTILS_INDENT_STREAM_HPP_
#define SOURCES_COMMON_INCLUDE_EDA_UTILS_INDENT_STREAM_HPP_


#include <streambuf>
#include <ostream>


namespace eda { namespace util {


class indent_sbuf : public std::streambuf
{
    std::streambuf*                 m_sbuf;
    std::string                     m_indent_str;
    static constexpr std::size_t    TAB_WIDTH = 2;

public:
    explicit indent_sbuf(std::streambuf* sbuf, size_t start_indent = 0)
        : m_sbuf{ sbuf }
        , m_indent_str(start_indent, ' ')
    { }

    ~indent_sbuf() override
    {
        // start at column 0 again
        overflow('\n');
    }

    indent_sbuf& increase()
    {
        m_indent_str = std::string(m_indent_str.size() + TAB_WIDTH, ' ');
        return *this;
    }

    indent_sbuf& decrease()
    {
        if(m_indent_str.size() > TAB_WIDTH) {
            m_indent_str = std::string(m_indent_str.size() - TAB_WIDTH, ' ');
        }
        else {
            m_indent_str.clear();
        }
        return *this;
    }

private:
    int_type overflow(int_type chr) override
    {
        // CLang -Weverything Diagnostic:
        // warning: implicit conversion loses integer precision:
        // 'std::basic_streambuf<char, std::char_traits<char> >::int_type'
        // (aka 'int') to 'std::basic_streambuf<char, std::char_traits<char> >::char_type'
        // (aka 'char') [-Wconversion]
        // ... may not give problems due to ANSI charset of VHDL
        int_type const put_ret{ m_sbuf->sputc(chr) };

        if(chr == '\n') {
            // CLang -Weverything Diagnostic:
            // warning: implicit conversion changes signedness:
            // 'std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >::size_type'
            // (aka 'unsigned long') to 'std::streamsize' (aka 'long') [-Wsign-conversion]
            // Also, on success the number of characters written is returned
            // and no check is done here - no error expected ;-)
            // FixMe: Add some indent_level and assert to avoid non-intentionally
            //        behavior. There may be a problem on huge indent size.
            m_sbuf->sputn( m_indent_str.data(), m_indent_str.size() );
        }
        return put_ret;
    }
};


class indent_ostream : public std::ostream
{
    indent_sbuf buf;

public:
    indent_ostream(std::ostream& os, size_t width)
        : std::ostream(&buf)
        , buf(os.rdbuf(), width)
    { }
};


static inline
std::ostream& increase_indent(std::ostream& os)
{
    auto* buf = static_cast<indent_sbuf*>(os.rdbuf());
    buf->increase();
    return os;
}


static inline
std::ostream& decrease_indent(std::ostream& os)
{
    auto* buf = static_cast<indent_sbuf*>(os.rdbuf());
    buf->decrease();
    return os;
}


} } // namespace eda.util


#endif /* SOURCES_COMMON_INCLUDE_EDA_UTILS_INDENT_STREAM_HPP_ */
