#pragma once

#include <cstdint>
#include <string>
#include <iosfwd>

namespace testsuite::vhdl_numeric_convert::util {

//******************************************************************************
// binary test pattern generator helper
//*******************************************************************************

///
/// Create a binary string from unsigned integer
///
struct binary_string {
    std::uint64_t number;

    binary_string(uint64_t n);

    std::string operator()() const;
};

///
/// Create an octal string from unsigned integer
///
struct octal_string {
    std::uint64_t number;

    octal_string(uint64_t n);

    std::string operator()() const;
};

///
/// Create a hexadecimal string from unsigned integer
///
struct hexadecimal_string {
    std::uint64_t number;

    hexadecimal_string(uint64_t n);

    std::string operator()() const;
};

std::ostream& operator<<(std::ostream& os, binary_string const& generator);
std::ostream& operator<<(std::ostream& os, octal_string const& generator);
std::ostream& operator<<(std::ostream& os, hexadecimal_string const& generator);

}  // namespace testsuite::vhdl_numeric_convert::util
