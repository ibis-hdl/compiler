/*
 * cxx_indent_ostreambuf.cpp
 *
 *  Created on: 26.04.2017
 *      Author: olaf
 */

//https://www.google.de/search?q=c%2B%2B+streambuf+implementatio&oq=c%2B%2B+streambuf+implementatio&aqs=chrome..69i57.43747j0j1&sourceid=chrome&ie=UTF-8#q=class+streambuf+indent+overflow+%22%5Cn%22+site:github.com&start=10
//https://github.com/afett/jsoncc/blob/master/src/iostream.cc
// https://github.com/lambdafu/grakopp/blob/master/include/grakopp/ast-io.hpp

#include <iostream>
#include <string>
#include <boost/variant.hpp>
#include <boost/spirit/home/x3/support/ast/variant.hpp>
#include <boost/spirit/home/x3/support/traits/is_variant.hpp>

namespace x3 = boost::spirit::x3;

struct variant : public x3::variant<double, std::string>
{
    using base_type::base_type;
};



#include <iostream>
#include <streambuf>
#include <iomanip>

class indent_sbuf : public std::streambuf
{
    std::streambuf*     m_sbuf;
    std::string         m_indent_str;
    bool                m_start_of_line;
    static const int    TAB_WIDTH = 2;

public:
    explicit indent_sbuf(std::streambuf* sbuf, size_t indent = 0)
        : m_sbuf{ sbuf }
        , m_indent_str(indent, '.')
        , m_start_of_line{ false }
    { }

    ~indent_sbuf()
    {
        overflow('\n');
    }

    indent_sbuf& increase()
    {
        m_indent_str = std::string(m_indent_str.size() + TAB_WIDTH, '.');
        return *this;
    }

    indent_sbuf& decrease()
    {
        if(m_indent_str.size() > TAB_WIDTH) {
            m_indent_str = std::string(m_indent_str.size() - TAB_WIDTH, '.');
        }
        else {
            m_indent_str.clear();
        }
        return *this;
    }

private:
    int_type overflow(int_type chr) override
    {
        if (m_start_of_line && chr != '\n') {
            m_sbuf->sputn( m_indent_str.data(), m_indent_str.size() );
        }
        m_start_of_line = (chr == '\n');
        return m_sbuf->sputc( chr );
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


struct printer
{
    indent_ostream os;
    bool verbose_symbol;
    bool verbose_variant;

    printer(std::ostream& os_)
    : os{ os_ , 0}
    , verbose_symbol {false}
    , verbose_variant{ false }
    {}

    struct scope_printer
    {
        indent_ostream& os;
        const char* const name{ nullptr };
        bool const verbose;

        scope_printer(indent_ostream& os_, char const name[], bool verbose, char const name_pfx[] = nullptr)
        : os{ os_ }
        , name{ name }
        , verbose{ verbose }
        {
            if(verbose) {
                os << increase_indent << "(";
                os << name;
                if(name_pfx)
                    os << "<" << name_pfx << ">";
                os << "\n";
                //os << "_"; // FixMe, required for correct indent
            }
        }

        ~scope_printer()
        {
            if(verbose) {
                os << decrease_indent << "\n)";
            }
        }
    };

    template<
        typename T,
        typename Enable = void
    >
    struct symbol_scope
    : public scope_printer
    {
        symbol_scope(printer & root, char const name[])
        : scope_printer(root.os, name, root.verbose_symbol)
        { }
    };

    template<
        typename T
    >
    struct symbol_scope<T, typename std::enable_if<x3::traits::is_variant<T>::value>::type>
    : public scope_printer
    {
        symbol_scope(printer & root, char const name[])
        : scope_printer(root.os, name, root.verbose_variant, "v")
        { }
    };

    struct indent_scope
    {
        indent_ostream& os;
        indent_scope(indent_ostream& os_)
        : os{ os_ }
        { os << increase_indent; }
        ~indent_scope()
        { os << decrease_indent; }
    };

    void operator()(double d)
    {
        static char const symbol[]{ "double" };
        symbol_scope<double> _(*this, symbol);
        os << d;
    }

    void operator()(std::string const& str)
    {
        static char const symbol[]{ "string" };
        symbol_scope<std::string> _(*this, symbol);
        indent_scope indent(os);
        os << str;
    }

    void operator()(variant const& v)
    {
        static char const symbol[]{ "variant" };
        symbol_scope<variant> _(*this, symbol);
        // Note, decltype doesn't work here!! (*1)
        //symbol_scope<decltype(v)> _(*this, symbol);
        boost::apply_visitor(*this, v);
    }
};


int main()
{

    variant v { "Hello" };
    {
        printer print{ std::cout };
        print.verbose_symbol = true;
        print.verbose_variant = true;
        print(v);
    }
    {
        printer print{ std::cout };
        print.verbose_symbol = true;
        print.verbose_variant = false;
        print(v);
    }
    {
        printer print{ std::cout };
        print.verbose_symbol = false;
        print.verbose_variant = false;
        print(v);
    }
}

/* (1*)
----8<----
#include <iostream>
#include <boost/spirit/home/x3/support/ast/variant.hpp>
#include <boost/spirit/home/x3/support/traits/is_variant.hpp>

namespace x3 = boost::spirit::x3;

struct variant : public x3::variant<double, std::string>
{
    using base_type::base_type;
};

int main()
{
    std::cout << std::boolalpha
              << x3::traits::is_variant<variant>::value
              << '\n';

    variant v { "Hello" };
    std::cout << std::boolalpha
              << x3::traits::is_variant<decltype(v)>::value
              << '\n';
}
---->8----
true
true
*/

