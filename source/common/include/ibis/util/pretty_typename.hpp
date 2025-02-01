//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-or-later
//

#pragma once

#include <regex>
#include <string>

#include <boost/type_index.hpp>

namespace ibis::util {

template <typename T>
class pretty_typename {
public:
    pretty_typename(std::string const& pattern_)
        : pattern{ pattern_ }
    {
    }

    pretty_typename() = default;
    ~pretty_typename() = default;

    pretty_typename(pretty_typename const&) = delete;
    pretty_typename const& operator=(pretty_typename const&) = delete;
    pretty_typename(pretty_typename&&) = delete;
    pretty_typename const& operator=(pretty_typename&&) = delete;

public:
    std::string str() const
    {
        std::string name{ boost::typeindex::type_id<T>().pretty_name() };
        return std::regex_replace(name, pattern, "");
    }

    std::ostream& print_on(std::ostream& os) const
    {
        os << this->str();
        return os;
    }

private:
    std::regex const pattern{ "::|boost|spirit|x3|ibis|vhdl|ast" };
};

template <typename T>
std::ostream& operator<<(std::ostream& os, pretty_typename<T> const& printer)
{
    return printer.print_on(os);
}

}  // namespace ibis::util
