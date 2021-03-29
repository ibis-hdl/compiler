#pragma once

#include <eda/color/detail/color.hpp>

#include <eda/color/detail/api.hpp>

#include <iostream>
#include <locale>  // facet
#include <optional>

namespace eda::color {

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
    explicit message_facet(color::printer prefix_, color::printer postfix_,
                           bool force_deco_ = false)
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
            *enable = detail::isatty{ os };
            // os << (*enable ? "is TTY" : "redirected");
            if (force_decoration) {
                // os << ", but forced";
                *enable = true;
            }
            // os << '\n';
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
    color::printer prefix;
    color::printer postfix;

public:
    static std::locale::id id;

private:
    bool force_decoration;
    std::optional<bool> mutable enable;
};

template <typename Tag>
std::locale::id message_facet<Tag>::id;

template <typename Tag>
std::ostream& operator<<(std::ostream& os, message_decorator<Tag> const& decorator)
{
    std::locale locale = os.getloc();

    if (std::has_facet<message_facet<Tag>>(locale)) {
        return std::use_facet<message_facet<Tag>>(locale).print(os, decorator);
    }

    return decorator.print(os);
}

}  // namespace eda::color
