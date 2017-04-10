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

struct printer 
{
    printer(std::ostream& os) 
    : os{ os }
    , verbose_symbol {false}
    , verbose_variant{ false }
    {}
    
    struct scope_printer
    {
        scope_printer(std::ostream& os, char const name[], bool verbose, char const name_pfx[] = nullptr) 
        : os{ os }
        , name{ name }
        , verbose{ verbose }
        {
            if(verbose) {
                os << prefix;
                if(name_pfx) 
                    os << name_pfx;
                os << name << "=";
            }
        }
        
        ~scope_printer()
        {
            if(verbose) {
                os << postfix;
            }  
        }
        
        std::ostream& os;
        const char* const name{ nullptr };
        bool const verbose;
        const char prefix{ '(' };  
        const char postfix{ ')' };

    };
    
    template<
        typename T,
        typename Enable = void
    >
    struct symbol_scope
    : public scope_printer
    {
        symbol_scope(printer const& root, char const name[]) 
        : scope_printer(root.os, name, root.verbose_symbol)
        { }
    };
    
    template<
        typename T
    >
    struct symbol_scope<T, typename std::enable_if<x3::traits::is_variant<T>::value>::type>
    : public scope_printer
    {
        symbol_scope(printer const& root, char const name[]) 
        : scope_printer(root.os, name, root.verbose_variant, "v:")
        { }
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

    std::ostream& os;    
    bool verbose_symbol;
    bool verbose_variant;
};


int main()
{
    
    variant v { "Hello" };
    printer print{ std::cout };
    
    print.verbose_symbol = true;
    print.verbose_variant = true;
    print(v);    
    std::cout << '\n';

    print.verbose_symbol = true;
    print.verbose_variant = false;
    print(v);
    std::cout << '\n';

    print.verbose_symbol = false;
    print.verbose_variant = false;
    print(v);    
    std::cout << '\n';
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