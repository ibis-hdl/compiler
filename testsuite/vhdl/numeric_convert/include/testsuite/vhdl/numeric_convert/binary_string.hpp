//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-or-later
//

#pragma once

#include <cstdint>
#include <string>
#include <iosfwd>

namespace testsuite::vhdl::numeric_convert::util {

//******************************************************************************
// binary test pattern generator helper
//*******************************************************************************

///
/// Create a binary string from unsigned integer
///
/// Example usage:
/// @code {.cpp}
/// std::cout << base << '#' << binary_string(value) << '#';
/// @endcode
///
struct binary_string {
    std::uint64_t number;

    binary_string(uint64_t n);

    std::string operator()() const;
};

///
/// Create an octal string from unsigned integer
///
/// Example usage:
/// @code {.cpp}
/// std::cout << base << '#' << octal_string(value) << '#';
/// @endcode
///
struct octal_string {
    std::uint64_t number;

    octal_string(uint64_t n);

    std::string operator()() const;
};

///
/// Create a hexadecimal string from unsigned integer
///
/// Example usage:
/// @code {.cpp}
/// std::cout << base << '#' << hexadecimal_string(value) << '#';
/// @endcode
///
struct hexadecimal_string {
    std::uint64_t number;

    hexadecimal_string(uint64_t n);

    std::string operator()() const;
};

// ToDo [c++20] replace with std::formatter, also inside source using this (bad API)
std::ostream& operator<<(std::ostream& os, binary_string const& generator);
std::ostream& operator<<(std::ostream& os, octal_string const& generator);
std::ostream& operator<<(std::ostream& os, hexadecimal_string const& generator);

}  // namespace testsuite::vhdl::numeric_convert::util
