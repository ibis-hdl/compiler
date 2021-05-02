#pragma once

#include <ibis/color/attribute.hpp>
#include <ibis/color/detail/ansi_writer.hpp>
#include <ibis/color/detail/platform.hpp>

#include <iosfwd>
#include <array>
#include <iterator>
#include <algorithm>
#include <cassert>

namespace ibis::color {

namespace detail {

template <typename enum_type, std::size_t SIZE>
class ansi_esc_printer {
public:
    using attribute = detail::attribute_container<enum_type, 4>;

public:
    explicit ansi_esc_printer(attribute const attributes_)
        : attributes{ attributes_ }
    {
    }

public:
    std::ostream& print(std::ostream& os) const
    {
        detail::ansi_writer ansi{ os };
        ansi(attributes);
        return os;
    }

    attribute const attributes;
};

template <typename enum_type, std::size_t SIZE>
static inline std::ostream& operator<<(  // --
    std::ostream& os, ansi_esc_printer<enum_type, SIZE> const& printer)
{
    return printer.print(os);
}

}  // namespace detail

}  // namespace ibis::color
