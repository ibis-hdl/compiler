/*
 * to_binary.hpp
 *
 *  Created on: 01.06.2018
 *      Author: olaf
 */

#ifndef TESTSUITE_VHDL_NUMERIC_CONVERT_INCLUDE_TESTSUITE_NUMERIC_CONVERT_BINARY_STRING_HPP_
#define TESTSUITE_VHDL_NUMERIC_CONVERT_INCLUDE_TESTSUITE_NUMERIC_CONVERT_BINARY_STRING_HPP_


#include <iosfwd>
#include <sstream>
#include <string>
#include <cmath>


namespace detail {

/*******************************************************************************
 * generator helper functions
 ******************************************************************************/

/**
 * Helper function to get the integer result of log(n) to any base. Used for
 * calculating required digits of literal strings.
 */
constexpr auto log2 = [](unsigned x) {
    return static_cast<unsigned>(std::ceil(std::log2(x)));
};

constexpr auto log = [](unsigned base, unsigned x) {
    return static_cast<unsigned>(std::ceil(std::log(x) / std::log(base)));
};


/**
 * Create a binary string from unsigned integer
 */
struct binary_string
{
    uint64_t                                        number;

    binary_string(uint64_t n)
    : number{ n }
    { }

    std::string operator()() const
    {
        std::size_t const sz = detail::log2(number) + 3;
        std::string s{};
        s.reserve(sz);

        std::stringstream ss{ s };
        uint64_t n{ number };

        while(n != 0) {
            ss << ( (n % 2 == 0) ? "0" : "1" );
            n /= 2;
        }

        s = ss.str();
        std::reverse(s.begin(), s.end());
        return s;
    }
};



std::ostream& operator<<(std::ostream& os, binary_string const& generator) {
    os << generator();
    return os;
}

} // namespace detail


#endif /* TESTSUITE_VHDL_NUMERIC_CONVERT_INCLUDE_TESTSUITE_NUMERIC_CONVERT_BINARY_STRING_HPP_ */
