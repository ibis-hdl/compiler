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


namespace tag {
	struct foo;
	struct bar;
};


template<typename Tag>
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



template<typename Tag>
class embrace_facet : public std::locale::facet
{
public:
    static std::locale::id                          id;

public:
    embrace_facet(std::string prefix_, std::string postfix_, bool force_deco_ = false)
    : facet{ 0 }
    , prefix{ std::move(prefix_) }
    , postfix{ std::move(postfix_) }
    , force_decoration{ force_deco_ }
    { }

public:
    std::ostream& print(std::ostream& os, embrace_decorator<Tag> const& decorator) const
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
    std::string const								prefix;
    std::string const								postfix;
    bool 											force_decoration;
};

template<typename Tag>
std::locale::id embrace_facet<Tag>::id;



template<typename Tag>
std::ostream& operator<<(std::ostream& os, embrace_decorator<Tag> const& decorator)
{
    std::locale locale = os.getloc();

    if (std::has_facet<embrace_facet<Tag>>(locale)) {
    	return std::use_facet<embrace_facet<Tag>>(locale).print(os, decorator);
    }
    else {
    	return decorator.print(os);
    }
}


using foo_decorator = embrace_decorator<tag::foo>;
using bar_decorator = embrace_decorator<tag::bar>;

using foo_facet = embrace_facet<tag::foo>;
using bar_facet = embrace_facet<tag::bar>;


int main()
{
	{
		std::cout << "--- Setup foo facet for std::cout ---\n";
		std::locale locale(std::locale(), new foo_facet{ "[", "]" });
		std::cout.imbue(locale);

		std::cout << foo_decorator("(foo (cout (Hello World)))") << std::endl;
		std::cout << bar_decorator("(bar (cout (Hello World)))") << std::endl;
		std::cout << "-------------------------------------\n";
	}
	{
		std::cout << "--- Setup bar facet for std::cout ---\n";
		bool want_decoration = true;

		if (want_decoration) {
			std::locale locale(std::locale(), new bar_facet{ "<", ">" });
			std::cerr.imbue(locale);
		}

		std::cout << foo_decorator("(foo (cerr (Hello World)))") << std::endl;
		std::cout << bar_decorator("(bar (cerr (Hello World)))") << std::endl;
		std::cout << "-------------------------------------\n";
	}
	{
		std::cout << "--- Setup foo facet for std::stringstream ---\n";
		std::stringstream ss;

		std::locale locale(std::locale(), new foo_facet{ "*", "*", true });
		ss.imbue(locale);

		ss << foo_decorator("(foo (stringstream (Hello World)))") << "\n"
		   << bar_decorator("(bar (stringstream (Hello World)))") << std::endl;
		std::cout << ss.str();
		std::cout << "---------------------------------------------\n";
	}
	{
		std::cout << "--- using foo facet with smart_ptr ---\n";
		/* [Calling initializer_list constructor via make_unique/make_shared](
		 *  https://stackoverflow.com/questions/26379311/calling-initializer-list-constructor-via-make-unique-make-shared)  */
		std::unique_ptr<bar_facet> facet = std::make_unique<bar_facet>("#", "#");
		// configure the object ...

		std::locale locale(std::locale(), facet.release());
		std::cout.imbue(locale);

		std::cout << bar_decorator("(bar (cout (Hello World)))") << std::endl;
		std::cout << "--------------------------------------\n";
	}
}
