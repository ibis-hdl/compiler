//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-or-later
//

#include <testsuite/vhdl/numeric_convert/binary_string.hpp>

#include <string>
#include <sstream>
#include <cmath>
#include <algorithm>
#include <type_traits>
#include <bitset>
#include <iomanip>

namespace testsuite::vhdl::numeric_convert::util {

// ----------------------------------------------------------------------------

binary_string::binary_string(uint64_t num)
    : number{ num }
{
}

std::string binary_string::operator()() const
{
    using numeric_type = decltype(number);
    using unsigned_type = std::make_unsigned<numeric_type>::type;

    std::size_t const size = sizeof(numeric_type) * 8;
    auto const bits = std::bitset<size>{ static_cast<unsigned_type>(number) };

    std::stringstream ss;
    ss << bits;

    return ss.str();
}

std::ostream& operator<<(std::ostream& os, binary_string const& generator)
{
    os << generator();
    return os;
}

// ----------------------------------------------------------------------------

octal_string::octal_string(uint64_t num)
    : number{ num }
{
}

std::string octal_string::operator()() const
{
    std::stringstream ss;

    ss << std::oct << number;

    return ss.str();
}

std::ostream& operator<<(std::ostream& os, octal_string const& generator)
{
    os << generator();
    return os;
}

// ----------------------------------------------------------------------------

hexadecimal_string::hexadecimal_string(uint64_t num)
    : number{ num }
{
}

std::string hexadecimal_string::operator()() const
{
    std::stringstream ss;

    ss << std::hex << number;

    return ss.str();
}

std::ostream& operator<<(std::ostream& os, hexadecimal_string const& generator)
{
    os << generator();
    return os;
}

}  // namespace testsuite::vhdl::numeric_convert::util
