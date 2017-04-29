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


namespace eda { namespace utils {


class indent_sbuf : public std::streambuf
{
    std::streambuf*     m_sbuf;
    std::string         m_indent_str;
    bool                m_start_of_line;
    static const int    TAB_WIDTH = 2;

public:
    explicit indent_sbuf(std::streambuf* sbuf, size_t start_indent = 0)
        : m_sbuf{ sbuf }
        , m_indent_str(start_indent, ' ')
        , m_start_of_line{ false }
    { }

    ~indent_sbuf()
    {
        // further write to ostream start at column 0 again
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
#if 1
        int_type const put_ret{ m_sbuf->sputc(chr) };
        if(chr == '\n') {
            /* Note: On success the number of characters written is returned
             *       and no check is done here. No fault expected ;-) */
            m_sbuf->sputn( m_indent_str.data(), m_indent_str.size() );
        }
        return put_ret;
#else
        // this code does wrong indent
        if (m_start_of_line && chr != '\n') {
            m_sbuf->sputn( m_indent_str.data(), m_indent_str.size() );
        }
        m_start_of_line = (chr == '\n');
        return m_sbuf->sputc( chr );
#endif
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
    indent_sbuf* buf = static_cast<indent_sbuf*>(os.rdbuf());
    buf->increase();
    return os;
}


static inline
std::ostream& decrease_indent(std::ostream& os)
{
    indent_sbuf* buf = static_cast<indent_sbuf*>(os.rdbuf());
    buf->decrease();
    return os;
}


} } // namespace eda.utils


#endif /* SOURCES_COMMON_INCLUDE_EDA_UTILS_INDENT_STREAM_HPP_ */