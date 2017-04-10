#include <iostream>
#include <string>
#include <boost/variant.hpp>
#include <boost/spirit/home/x3/support/ast/variant.hpp>
#include <boost/spirit/home/x3/support/traits/is_variant.hpp>



namespace x3 = boost::spirit::x3;


// variant to test proof-of-concept
struct variant : public x3::variant<double, std::string>
{
    using base_type::base_type;
};


namespace detail {


struct scope_printer_base
{
    scope_printer_base(std::ostream& os, char const name[])
    : os{ os }
    , name{ name }
    { }

    std::ostream& os;
    const char* const name{ nullptr };
};


struct verbose_printer : scope_printer_base
{
    char prefix() const { return '('; };
    char postfix() const { return ')'; };

    verbose_printer(std::ostream& os, char const name[])
    : scope_printer_base(os, name)
    {
        os << prefix() << name << "=";
    }
    ~verbose_printer()
    {
        os << postfix();
    }
};


struct silent_printer : scope_printer_base
{
    silent_printer(std::ostream& os, char const name[])
    : scope_printer_base(os, name)
    { }
    ~silent_printer()
    { }
};


struct verbose_variant_printer : scope_printer_base
{
    char prefix() const { return '('; };
    char postfix() const { return ')'; };

    verbose_variant_printer(std::ostream& os, char const name[])
    : scope_printer_base(os, name)
    {
        os << prefix() << "v:" << name << "=";
    }
    ~verbose_variant_printer()
    {
        os << postfix();
    }
};


struct silent_variant_printer : scope_printer_base
{
    silent_variant_printer(std::ostream& os, char const name[])
    : scope_printer_base(os, name)
    { }
    ~silent_variant_printer()
    { }
};


} // detail


template<
    typename NodePrinterT    = detail::verbose_printer,
    typename VariantPrinterT = detail::verbose_variant_printer
    >
struct printer
{
    printer(std::ostream& os)
    : os{ os }
    { }

    typedef NodePrinterT        node_printer;
    typedef VariantPrinterT     variant_printer;

    typedef printer<node_printer, variant_printer> printer_type;

    template<
        typename T,
        typename Enable = void
    >
    struct symbol_scope
    : public node_printer
    {
        symbol_scope(printer const& root, char const name[])
        : node_printer(root.os, name)
        { }
    };

    template<
        typename T
    >
    struct symbol_scope<T, typename std::enable_if<x3::traits::is_variant<T>::value>::type>
    : public variant_printer
    {
        symbol_scope(printer const& root, char const name[])
        : variant_printer(root.os, name)
        { }
    };


    void operator()(double d) const
    {
        static char const symbol[]{ "double" };
        symbol_scope<double> _(*this, symbol);
        os << d;
    }

    void operator()(std::string const& str) const
    {
        static char const symbol[]{ "string" };
        symbol_scope<std::string> _(*this, symbol);
        os << str;
    }

    void operator()(variant const& v) const
    {
        static char const symbol[]{ "variant" };
        symbol_scope<variant> _(*this, symbol);
        // decltype doesn't work as expected (*1)
        //symbol_scope<decltype(v)> _(*this, symbol);
        boost::apply_visitor(*this, v);
        // or recursive:
        //boost::apply_visitor(printer_type(os), v);
    }

    std::ostream& os;
};



typedef printer<detail::verbose_printer, detail::verbose_variant_printer> verbose_printer;
typedef printer<detail::verbose_printer, detail::silent_variant_printer> verbose_node_printer;
typedef printer<detail::silent_printer, detail::silent_variant_printer> node_printer;

int main()
{

    variant v { "Hello" };
    {
        printer<> print{ std::cout };
        print(v);
        std::cout << "\n";
    }
    {
        verbose_node_printer print{ std::cout };
        print(v);
        std::cout << "\n";
    }
    {
        node_printer print{ std::cout };
        print(v);
        std::cout << "\n";
    }
}

/*
 * *(1)
 * (variant=(string=Hello))
 */
