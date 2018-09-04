/*
 * facet.hpp
 *
 *  Created on: 06.08.2018
 *      Author: olaf
 */

#ifndef SOURCES_COMMON_INCLUDE_EDA_COLOR_FACET_HPP_
#define SOURCES_COMMON_INCLUDE_EDA_COLOR_FACET_HPP_

#include <eda/color/detail/color.hpp>

#include <iostream>
#include <locale> // facet

#include <cstdio> // fileno
#include <optional>
#include <unistd.h> // isatty

namespace eda {
namespace color {

template <typename Tag>
class message_facet : public std::locale::facet {
public:
    /**
     * Construct a message facte
     *
     * @param prefix_     The color before priting the embraced message.
     * @param postfix_    The color past priting the embraced message, commonly
     *                    restore the default state.
     * @param force_deco_ Force the color printing.
     *
     * \note Clang-Tidy '[misc-move-const-arg]' message:
     * std::move of the variable {'prefix_', 'postfix_'} of the
     * trivially-copyable type 'color::printer' (aka 'esc_printer<ansii::attribute, 4>')
     * has no effect.
     */
    explicit message_facet(color::printer prefix_, color::printer postfix_, bool force_deco_ = false)
        : facet{ 0 }
        , prefix{ prefix_ }
        , postfix{ postfix_ }
        , force_decoration{ force_deco_ }
    {
    }

    explicit message_facet(bool force_deco_ = false)
        : facet{ 0 }
        , force_decoration{ force_deco_ }
    {
    }

    ~message_facet() = default;
  
    message_facet(message_facet const&) = delete;
    message_facet& operator=(message_facet const&) = delete;

    message_facet(message_facet&&) = delete;
    message_facet& operator=(message_facet&&) = delete;

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
            //os << '\n';
        }

        if (*enable) {
            os << prefix;
        }
        decorator.print(os);
        if (*enable) {
            os << postfix;
        }

        return os;
    }

public:
    // clang-format off
    color::printer                                    prefix;
    color::printer                                    postfix;
    // clang-format on

private:
    bool is_tty(std::ostream& os) const
    {
        // no POSIX way to extract stream handler from the a given
        // `std::ostream` object
        auto const stream = [](std::ostream& os_) {
            if (&os_ == &std::cout) {
                return stdout;
            }
            if (&os_ == &std::cerr || &os_ == &std::clog) {
                return stderr;
            }
            return static_cast<FILE*>(nullptr);
        };

        auto const handle = stream(os);
        // Note, ::fileno(NULL) can crash (bug there?)
        if (handle) {
            return static_cast<bool>(::isatty(::fileno(handle)));
        }
        return false;
    }

public:
    // clang-format off
    static std::locale::id                          id;
    // clang-format on

private:
    // clang-format off
    bool                                            force_decoration;
    std::optional<bool> mutable                     enable;
    // clang-format off
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
    return decorator.print(os);
}


} } // namespace eda.color



#endif /* SOURCES_COMMON_INCLUDE_EDA_COLOR_FACET_HPP_ */
