/*
 * facet.hpp
 *
 *  Created on: 06.08.2018
 *      Author: olaf
 */

#ifndef SOURCES_COMMON_INCLUDE_EDA_COLOR_FACET_HPP_
#define SOURCES_COMMON_INCLUDE_EDA_COLOR_FACET_HPP_

#include <eda/color/detail/ansii_color.hpp>

#include <locale>   // facet
#include <iostream>

#include <optional>
#include <unistd.h> // isatty
#include <cstdio>   // fileno


namespace eda { namespace color {


template<typename Tag>
class message_facet : public std::locale::facet
{
public:
    static std::locale::id                          id;

public:
    message_facet(esc_printer<ansii::attribute, 4> prefix_, esc_printer<ansii::attribute, 4> postfix_, bool force_deco_ = false)
    : facet{ 0 }
    , prefix{ std::move(prefix_) }
    , postfix{ std::move(postfix_) }
    , force_decoration{ force_deco_ }
    { }

    message_facet(bool force_deco_ = false)
    : facet{ 0 }
    , force_decoration{ force_deco_ }
    { }

//    message_facet(message_facet const&) = delete;
//    message_facet& operator=(message_facet const&) = delete;

public:
    std::ostream& print(std::ostream& os, message_decorator<Tag> const& decorator) const
    {
        if (!enable) {
            *enable = is_tty(os);
            //os << (*enable ? "is TTY" : "redirected");
            if (force_decoration) {
                //os << ", but forced";
                *enable = true;
            }
            //os << "\n";
        }

        if (*enable) { os << prefix; }
        decorator.print(os);
        if (*enable) { os << postfix; }

        return os;
    }

public:
    esc_printer<ansii::attribute, 4>                prefix;
    esc_printer<ansii::attribute, 4>                postfix;

private:
    bool is_tty(std::ostream& os) const
    {
        // no POSIX way to extract stream handler from the a given
        // `std::ostream` object
        auto const stream = [](std::ostream& os) {
            if (&os == &std::cout)                      { return stdout; }
            if (&os == &std::cerr || &os == &std::clog) { return stderr; }
            return static_cast<FILE*>(0);
        };

        auto const handle = stream(os);
        // Note, ::fileno(NULL) can crash (bug there?)
        if (handle && ::isatty(::fileno(handle))) { return true; }
        return false;
    }

private:
    bool                                            force_decoration;
    std::optional<bool> mutable                     enable;
};


template<typename Tag>
std::locale::id message_facet<Tag>::id;


template<typename Tag>
std::ostream& operator<<(std::ostream& os, message_decorator<Tag> const& decorator)
{
    std::locale locale = os.getloc();

    if (std::has_facet<message_facet<Tag>>(locale)) {
        return std::use_facet<message_facet<Tag>>(locale).print(os, decorator);
    }
    else {
        return decorator.print(os);
    }
}


} } // namespace eda.color



#endif /* SOURCES_COMMON_INCLUDE_EDA_COLOR_FACET_HPP_ */
