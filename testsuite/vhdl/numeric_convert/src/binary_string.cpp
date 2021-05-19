#include <testsuite/vhdl/numeric_convert/binary_string.hpp>

#include <string>
#include <sstream>
#include <cmath>
#include <algorithm>
#include <type_traits>
#include <bitset>
#include <iomanip>

namespace testsuite::vhdl::numeric_convert::util {

///
/// Create a binary string from unsigned integer
///
binary_string::binary_string(uint64_t n)
    : number{ n }
{
}

std::string binary_string::operator()() const
{
    using numeric_type = decltype(number);
    using unsigned_type = std::make_unsigned<numeric_type>::type;

    std::size_t const sz = sizeof(numeric_type) * 8;
    auto const bits = std::bitset<sz>{ static_cast<unsigned_type>(number) };

    std::stringstream ss;
    ss << bits;

    return ss.str();
}

std::ostream& operator<<(std::ostream& os, binary_string const& generator)
{
    os << generator();
    return os;
}

///
/// Create an octal string from unsigned integer
///
octal_string::octal_string(uint64_t n)
    : number{ n }
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

///
/// Create a hexadecimal string from unsigned integer
///
hexadecimal_string::hexadecimal_string(uint64_t n)
    : number{ n }
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
