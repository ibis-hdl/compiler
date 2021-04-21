#include <testsuite/vhdl_numeric_convert/binary_string.hpp>

#include <string>
#include <sstream>
#include <cmath>
#include <algorithm>
#include <type_traits>
#include <bitset>
#include <iomanip>

namespace testsuite::vhdl_numeric_convert::util {

///
/// Helper function to get the integer result of log(n) to any base. Used for
/// calculating required digits of literal strings.
///
namespace detail {

constexpr auto log2 = [](unsigned x) { return static_cast<unsigned>(std::ceil(std::log2(x))); };

constexpr auto log = [](unsigned base, unsigned x) {
    return static_cast<unsigned>(std::ceil(std::log(x) / std::log(base)));
};

}  // namespace detail

///
/// Create a binary string from unsigned integer
///
binary_string::binary_string(uint64_t n)
    : number{ n }
{
}

std::string binary_string::operator()() const
{
    std::string s{};

    if constexpr (true) {
        using numeric_type = decltype(number);
        using unsigned_type = std::make_unsigned<numeric_type>::type;

        std::size_t const sz = sizeof(numeric_type) * 8;
        s.reserve(sz);

        auto const bits = std::bitset<sz>{ static_cast<unsigned_type>(number) };

        std::stringstream ss{ s };
        ss << bits;
        s = ss.str();
    }
    else {
        // original code as archive
        std::size_t const sz = detail::log2(number);
        s.reserve(sz);

        std::stringstream ss{ s };
        uint64_t n{ number };

        while (n != 0) {
            ss << ((n % 2 == 0) ? "0" : "1");
            n /= 2;
        }

        s = ss.str();
        std::reverse(s.begin(), s.end());
    }

    return s;
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
    std::size_t const sz = detail::log(8, number);
    std::string s{};
    s.reserve(sz);

    std::stringstream ss{ s };

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
    std::size_t const sz = detail::log(16, number);
    std::string s{};
    s.reserve(sz);

    std::stringstream ss{ s };

    ss << std::hex << number;

    return ss.str();
}

std::ostream& operator<<(std::ostream& os, hexadecimal_string const& generator)
{
    os << generator();
    return os;
}

}  // namespace testsuite::vhdl_numeric_convert::util
