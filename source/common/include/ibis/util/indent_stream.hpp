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
    ~indent_sbuf() override
    {
        // NOLINTNEXTLINE(clang-analyzer-optin.cplusplus.VirtualCall) -- functionally intended
        overflow('\n');  // start at column 0 again
    }

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
        // CLang -Weverything Diagnostic:
        // warning: implicit conversion loses integer precision:
        // 'std::basic_streambuf<char, std::char_traits<char> >::int_type'
        // (aka 'int') to 'std::basic_streambuf<char, std::char_traits<char> >::char_type'
        // (aka 'char') [-Wconversion]
        // ... may not give problems due to ANSI charset of VHDL
        int_type const put_ret{ m_sbuf->sputc(chr) };

        if (chr == '\n') {
            // CLang -Weverything Diagnostic:
            // warning: implicit conversion changes signedness:
            // 'std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char>
            // >::size_type' (aka 'unsigned long') to 'std::streamsize' (aka 'long')
            // [-Wsign-conversion] Also, on success the number of characters written is returned and
            // no check is done here - no error expected ;-) FixMe: Add some indent_level and assert
            // to avoid non-intentionally behavior. There may be a problem on huge indent size.
            m_sbuf->sputn(m_indent_str.data(), m_indent_str.size());
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
