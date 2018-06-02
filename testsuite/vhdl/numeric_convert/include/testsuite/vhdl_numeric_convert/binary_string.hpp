/*
 * to_binary.hpp
 *
 *  Created on: 01.06.2018
 *      Author: olaf
 */

#ifndef TESTSUITE_VHDL_NUMERIC_CONVERT_INCLUDE_TESTSUITE_VHDL_NUMERIC_CONVERT_BINARY_STRING_HPP_
#define TESTSUITE_VHDL_NUMERIC_CONVERT_INCLUDE_TESTSUITE_VHDL_NUMERIC_CONVERT_BINARY_STRING_HPP_


#include <iosfwd>
#include <string>


namespace testsuite { namespace vhdl_numeric_convert { namespace util {

/*******************************************************************************
 * binary test pattern generator helper
 *******************************************************************************/

/**
 * Create a binary string from unsigned integer
 */
struct binary_string
{
    uint64_t                                        number;

    binary_string(uint64_t n);

    std::string operator()() const;
};


/**
 * Create an octal string from unsigned integer
 */
struct octal_string
{
    uint64_t                                        number;

    octal_string(uint64_t n);

    std::string operator()() const;
};


/**
 * Create a hexadecimal string from unsigned integer
 */
struct hexadecimal_string
{
    uint64_t                                        number;

    hexadecimal_string(uint64_t n);

    std::string operator()() const;
};



std::ostream& operator<<(std::ostream& os, binary_string const& generator);
std::ostream& operator<<(std::ostream& os, octal_string const& generator);
std::ostream& operator<<(std::ostream& os, hexadecimal_string const& generator);


} } } // namespace testsuite.vhdl_numeric_convert.util


#endif /* TESTSUITE_VHDL_NUMERIC_CONVERT_INCLUDE_TESTSUITE_VHDL_NUMERIC_CONVERT_BINARY_STRING_HPP_ */
