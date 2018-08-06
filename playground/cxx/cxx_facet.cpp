/*
 * cxx_facet.cpp
 *
 *  Created on: 05.08.2018
 *      Author: olaf
 */

/*
 * C++ facet related:
 *  - [iostream maniputor via xalloc/iword or via derived class?](https://stackoverflow.com/questions/23933655/iostream-maniputor-via-xalloc-iword-or-via-derived-class)
 * - [Dr. Dobbs: The Standard Librarian: Defining a Facet](http://www.drdobbs.com/the-standard-librarian-defining-a-facet/184403785#4=)
 * - [The Standard C++ Locale](http://www.cantrip.org/locale.html)
 *
 * Problem related
 *  - [Mutable flags on a std::facet object](https://stackoverflow.com/questions/28271898/mutable-flags-on-a-stdfacet-object)
 *
 * Not complete related here, but interesting:
 * - [Override more than one facet on std::locale](https://stackoverflow.com/questions/34855812/override-more-than-one-facet-on-stdlocale)
 */
#include <locale>   // facet
#include <iostream>

#include <optional>
#include <unistd.h> // isatty
#include <cstdio>   // fileno

#include <sstream>
#include <memory>


class embrace_decorator
{
public:
    embrace_decorator(std::string const& contents_)
    : contents{ contents_ }
    { }

    std::ostream& print(std::ostream& os) const {
        os << contents;
        return os;
    }

private:
    std::string const&                              contents;
};



class embrace_facet : public std::locale::facet
{
public:
    static std::locale::id                          id;

public:
    embrace_facet(std::string const& prefix_, std::string const& postfix_, bool force_deco_ = false)
    : facet{ 0 }
    , prefix{ prefix_ }
    , postfix{ postfix_ }
    , force_decoration{ force_deco_ }
    { }

public:
    std::ostream& print(std::ostream& os, embrace_decorator const& decorator) const
    {
        if (!enable) {
            *enable = is_tty(os);
            os << (*enable ? "is TTY" : "redirected");
            if (force_decoration) {
                os << ", but forced";
                *enable = true;
            }

            os << "\n";
        }

        if (*enable) { os << prefix; }
        decorator.print(os);
        if (*enable) { os << postfix; }

        return os;
    }

private:
    bool is_tty(std::ostream& os) const
    {
        // no POSIX way to extract stream handler from the a given
        // `std::ostream` object
        auto const stream = [](std::ostream& os) {
            if (&os == &std::cout)                      { return stdout; }
            if (&os == &std::cerr || &os == &std::clog) { return stderr; }
            return (FILE*)0;
        };

        if (::isatty(::fileno(stream(os)))) { return true; }
        return false;
    }

private:
    std::optional<bool> mutable                     enable;
    std::string const                               prefix;
    std::string const                               postfix;
    bool                                            force_decoration;
};

std::locale::id embrace_facet::id;



std::ostream& operator<<(std::ostream& os, embrace_decorator const& decorator)
{
    std::locale locale = os.getloc();

    if (std::has_facet<embrace_facet>(locale)) {
        return std::use_facet<embrace_facet>(locale).print(os, decorator);
    }
    else {
        return decorator.print(os);
    }
}


int main()
{
    {
        std::locale locale(std::locale(), new embrace_facet { "[", "]" });
        std::cout.imbue(locale);

        std::cout << embrace_decorator("(cout (Hello World))") << std::endl;

    }
    {
        bool want_decoration = true;

        if (want_decoration) {
            std::locale locale(std::locale(), new embrace_facet { "<", ">" });
            std::cerr.imbue(locale);
        }

        std::cerr << embrace_decorator("(cerr (Hello World))") << std::endl;
    }
#if 0 // Segmentation fault
    {
        std::stringstream ss;

        std::locale locale(std::locale(), new embrace_facet { "*", "*", true });
        ss.imbue(locale);

        ss <<  embrace_decorator("(stringstream (Hello World))");
        std::cout << ss.str() << std::endl;
    }
#endif
    {
        std::unique_ptr<embrace_facet> facet = std::make_unique<embrace_facet>("#", "#");
        // configure the object ...

        std::locale locale(std::locale(), facet.release());
        std::cout.imbue(locale);

        std::cout << embrace_decorator("(cout (Hello World))") << std::endl;
    }
}
