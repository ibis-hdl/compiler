#pragma once

#include <ostream>
#include <streambuf>

namespace ibis::util {

/// An indenting stream buffer
///
/// On each increase() member call the indent is increased respectively
/// decreased on decrease() call. The buffer is intended to be used with
/// indent_ostream and the IO manipulators increase_indent() and
/// decrease_indent()
///
/// FixMe: tabwith is hard coded.
///
/// Note: clang-tidy may complain about the overloaded overload()
///       member function, since it can throw inside the destructor
///       of the class. Yes, it can following
///       [Can C++ streambuf methods throw exceptions?](
///        https://stackoverflow.com/questions/19105657/can-c-streambuf-methods-throw-exceptions).
///       [std::stringbuf::overflow](
///        http://www.cplusplus.com/reference/sstream/stringbuf/overflow/)
///       states basic guarantee: if an exception is thrown, the
///       stream buffer is in a valid state.
class indent_sbuf : public std::streambuf {
public:
    explicit indent_sbuf(std::streambuf* sbuf, size_t start_indent = 0)
        : m_sbuf{ sbuf }
        , m_indent_str(start_indent, ' ')
    {
    }

    indent_sbuf(indent_sbuf const&) = delete;
    indent_sbuf& operator=(indent_sbuf const&) = delete;
    indent_sbuf(indent_sbuf&&) = delete;
    indent_sbuf& operator=(indent_sbuf&&) = delete;

public:
    ~indent_sbuf() override;

    indent_sbuf& increase()
    {
        m_indent_str = std::string(m_indent_str.size() + TAB_WIDTH, ' ');
        return *this;
    }

    indent_sbuf& decrease()
    {
        if (m_indent_str.size() > TAB_WIDTH) {
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
        // Quiet Compiler warning [-Wimplicit-int-conversion]
        // [Correct implementation of std::streambuf::overflow](
        //  https://stackoverflow.com/questions/20667951/correct-implementation-of-stdstreambufoverflow)
        // so no interest of eof, hence its legitimate to cast, see
        // [CharTraits](https://en.cppreference.com/w/cpp/named_req/CharTraits)
        int_type const put_ret{ m_sbuf->sputc(static_cast<char_type>(chr)) };

        if (chr == '\n') {
            // Quiet Compiler warning [-Wsign-conversion]. There may be a problem on huge indent size.
            m_sbuf->sputn(m_indent_str.data(), static_cast<std::streamsize>(m_indent_str.size()));
        }

        return put_ret;
    }

private:
    std::streambuf* m_sbuf;
    std::string m_indent_str;
    static constexpr std::size_t TAB_WIDTH = 2;
};

class indent_ostream : public std::ostream {
public:
    indent_ostream(std::ostream& os, size_t width)
        : std::ostream{ &buf }
        , buf{ os.rdbuf(), width }
    {
    }

    ~indent_ostream() override;

private:
    indent_sbuf buf;
};

inline std::ostream& increase_indent(std::ostream& os)
{
    // NOLINTNEXTLINE(cppcoreguidelines-pro-type-static-cast-downcast) -- assume this is legitimate
    auto* buf = static_cast<indent_sbuf*>(os.rdbuf());
    buf->increase();
    return os;
}

inline std::ostream& decrease_indent(std::ostream& os)
{
    // NOLINTNEXTLINE(cppcoreguidelines-pro-type-static-cast-downcast) -- assume this is legitimate
    auto* buf = static_cast<indent_sbuf*>(os.rdbuf());
    buf->decrease();
    return os;
}

}  // namespace ibis::util
