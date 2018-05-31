/*
 * bit_string_literal_test.cpp
 *
 *  Created on: 29.05.2018
 *      Author: olaf
 */

#include <testsuite/numeric_convert/numeric_parser.hpp>

#include <eda/vhdl/ast/util/numeric_convert.hpp>
#include <eda/vhdl/type.hpp>

#include <boost/test/unit_test.hpp>
#include <boost/test/data/test_case.hpp>
#include <boost/test/data/monomorphic.hpp>
#include <boost/test/output_test_stream.hpp>
#include <boost/core/ignore_unused.hpp>

#include <iostream>
#include <sstream>
#include <limits>
#include <algorithm>
#include <cmath>
#include <vector>


BOOST_AUTO_TEST_SUITE( bit_string_literal )


namespace ast = eda::vhdl::ast;
namespace btt = boost::test_tools;
namespace but_data = boost::unit_test::data;


namespace detail {

/*******************************************************************************
 * bin/oct/hex generator helper functions
 ******************************************************************************/

auto const log = [](unsigned base, unsigned x) {
    return static_cast<unsigned>(std::ceil(std::log(x) / std::log(base)));
};


std::string to_bin(uint64_t n)
{
    std::size_t const sz = std::ceil(std::log2(n)) + 3;
    std::string s{};
    s.reserve(sz);

    std::stringstream ss{ s };

    while(n != 0) {
        ss << ( (n % 2 == 0) ? "0" : "1" );
        n /= 2;
    }

    s = ss.str();
    std::reverse(s.begin(), s.end());
    return s;
}


std::string to_bin_literal(uint64_t n, std::string const& postfix="")
{
    std::string const s{ "B\"" + to_bin(n) + postfix + '"'};
    return s;
}


std::string to_bin_literal(uint64_t n, std::string const& prefix, std::string const& postfix)
{
    std::string const s{ "B\"" + prefix + to_bin(n) + postfix + '"'};
    return s;
}

std::string to_oct_literal(uint64_t n, std::string const& postfix="")
{
    std::size_t const sz = log(8, n) + 3;
    std::string s{};
    s.reserve(sz);

    std::stringstream ss{ s };
    ss << "O\"" << std::oct << n << postfix << "\"";
    return ss.str();
}


std::string to_oct_literal(uint64_t n, std::string const& prefix, std::string const& postfix)
{
    std::size_t const sz = log(8, n) + 3;
    std::string s{};
    s.reserve(sz);

    std::stringstream ss{ s };
    ss << "O\"" << prefix << std::oct << n << postfix << "\"";
    return ss.str();
}


std::string to_hex_literal(uint64_t n, std::string const& postfix="")
{
    std::size_t const sz = log(16, n) + 3;
    std::string s{};
    s.reserve(sz);

    std::stringstream ss{ s };
    ss << "X\"" << std::hex << n << postfix << "\"";
    return ss.str();
}


std::string to_hex_literal(uint64_t n, std::string const& prefix, std::string const& postfix)
{
    std::size_t const sz = log(16, n) + 3;
    std::string s{};
    s.reserve(sz);

    std::stringstream ss{ s };
    ss << "X\"" << prefix << std::hex << n << postfix << "\"";
    return ss.str();
}


} // namespace detail


namespace /* anonymous */ {

// discard concrete error messages
btt::output_test_stream error_log;

// implicit check of state less conversion, otherwise test must fail
auto const numeric_convert =  ast::numeric_convert{ error_log };

}


/*******************************************************************************
 * binary bit_string_literal
 ******************************************************************************/
std::vector<std::string> const bin_lit{
    R"(B"00_00")",
    R"(B"00_01")",
    R"(B"1_0000")",
    R"(B"1_00_01")",
    detail::to_bin_literal(std::numeric_limits<uint32_t>::max()),
    detail::to_bin_literal(std::numeric_limits<uint64_t>::max()),
    // uin64 max with leading zeros
    detail::to_bin_literal(std::numeric_limits<uint64_t>::max(), "0000_", "")
};

std::vector<eda::vhdl::intrinsic::unsigned_integer_type> bin_dec{
    0,
    1,
    16,
    17,
    std::numeric_limits<uint32_t>::max(),
    std::numeric_limits<uint64_t>::max(),
    std::numeric_limits<uint64_t>::max(),
};


BOOST_DATA_TEST_CASE(
    bit_string_bin,
    but_data::make(bin_lit) ^ bin_dec,
    literal,                  N)
{
    auto const [parse_ok, ast_node] = x3_test::parse_bit_string_literal(literal);
    BOOST_REQUIRE(parse_ok);

    auto const [conv_ok, value] = numeric_convert(ast_node);
    BOOST_REQUIRE(conv_ok);
    BOOST_TEST( value == N );
}


BOOST_AUTO_TEST_CASE( bin_uint64max_ovrflw )
{
    uint64_t N = std::numeric_limits<uint64_t>::max();

    std::string const literal{ detail::to_bin_literal(N, "_0") };

    //std::cout << N << " = " << literal << " + 1\n";

    auto const [parse_ok, ast_node] = x3_test::parse_bit_string_literal(literal);
    BOOST_REQUIRE(parse_ok);    // must parse ...

    auto const [conv_ok, value] = numeric_convert(ast_node);
    BOOST_TEST(!conv_ok);       // ... but must fail to convert

    boost::ignore_unused(value);
}


/*******************************************************************************
 * octal bit_string_literal
 ******************************************************************************/
std::vector<std::string> const oct_lit{
    R"(O"00_00")",
    R"(O"00_01")",
    R"(O"1_7654")",
    R"(O"7_6543210")",
    detail::to_oct_literal(std::numeric_limits<uint32_t>::max()),
    detail::to_oct_literal(std::numeric_limits<uint64_t>::max()),
    // uin64 max with leading zeros
    detail::to_oct_literal(std::numeric_limits<uint64_t>::max(), "0000_", "")
};

std::vector<eda::vhdl::intrinsic::unsigned_integer_type> oct_dec{
    0,
    1,
    8108,
    16434824,
    std::numeric_limits<uint32_t>::max(),
    std::numeric_limits<uint64_t>::max(),
    std::numeric_limits<uint64_t>::max(),
};


BOOST_DATA_TEST_CASE(
    bit_string_oct,
    but_data::make(oct_lit) ^ oct_dec,
    literal,                  N)
{
    auto const [parse_ok, ast_node] = x3_test::parse_bit_string_literal(literal);
    BOOST_REQUIRE(parse_ok);

    auto const [conv_ok, value] = numeric_convert(ast_node);
    BOOST_REQUIRE(conv_ok);
    BOOST_TEST( value == N );
}


BOOST_AUTO_TEST_CASE( oct_uint64max_ovrflw )
{
    uint64_t N = std::numeric_limits<uint64_t>::max();

    std::string const literal{ detail::to_oct_literal(N, "_0") };

    //std::cout << N << " = " << literal << " + 1\n";

    auto const [parse_ok, ast_node] = x3_test::parse_bit_string_literal(literal);
    BOOST_REQUIRE(parse_ok);    // must parse ...

    auto const [conv_ok, value] = numeric_convert(ast_node);
    BOOST_TEST(!conv_ok);       // ... but must fail to convert

    boost::ignore_unused(value);
}


/*******************************************************************************
 * hexadecimal bit_string_literal
 ******************************************************************************/
std::vector<std::string> const hex_lit{
    R"(X"00_00")",
    R"(X"00_01")",
    R"(X"1_AFFE")",
    R"(X"C001_CAFE")",
    detail::to_hex_literal(std::numeric_limits<uint32_t>::max()),
    detail::to_hex_literal(std::numeric_limits<uint64_t>::max()),
    // uin64 max with leading zeros
    detail::to_hex_literal(std::numeric_limits<uint64_t>::max(), "0000_", "")
};

std::vector<eda::vhdl::intrinsic::unsigned_integer_type> hex_dec{
    0,
    1,
    110590,
    3221342974,
    std::numeric_limits<uint32_t>::max(),
    std::numeric_limits<uint64_t>::max(),
    std::numeric_limits<uint64_t>::max(),
};


BOOST_DATA_TEST_CASE(
    bit_string_hex,
    but_data::make(hex_lit) ^ hex_dec,
    literal,                  N)
{
    auto const [parse_ok, ast_node] = x3_test::parse_bit_string_literal(literal);
    BOOST_REQUIRE(parse_ok);

    auto const [conv_ok, value] = numeric_convert(ast_node);
    BOOST_REQUIRE(conv_ok);
    BOOST_TEST( value == N );
}


BOOST_AUTO_TEST_CASE( hex_uint64max_ovrflw )
{
    uint64_t N = std::numeric_limits<uint64_t>::max();

    std::string const literal{ detail::to_hex_literal(N, "_0") };

    //std::cout << N << " = " << literal << " + 1\n";

    auto const [parse_ok, ast_node] = x3_test::parse_bit_string_literal(literal);
    BOOST_REQUIRE(parse_ok);    // must parse ...

    auto const [conv_ok, value] = numeric_convert(ast_node);
    BOOST_TEST(!conv_ok);       // ... but must fail to convert

    boost::ignore_unused(value);
}


BOOST_AUTO_TEST_SUITE_END()



