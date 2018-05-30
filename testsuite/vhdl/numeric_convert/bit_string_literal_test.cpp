/*
 * bit_string_literal_test.cpp
 *
 *  Created on: 29.05.2018
 *      Author: olaf
 */

#include <testsuite/numeric_convert/numeric_parser.hpp>

#include <eda/vhdl/ast/util/numeric_convert.hpp>

#include <boost/test/unit_test.hpp>

#include <iostream>
#include <sstream>
#include <limits>
#include <algorithm>
#include <cmath>


BOOST_AUTO_TEST_SUITE( numeric_convert )


namespace ast = eda::vhdl::ast;
namespace btt = boost::test_tools;


namespace detail {


std::string to_binary(uint64_t n)
{
    std::size_t const sz = std::ceil(std::log2(n));
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


std::string to_binary_literal(uint64_t n, std::string const& postix="")
{
    std::string const s{ R"(B")" + to_binary(n) + postix + '"'};
    return s;
}


std::string to_binary_literal(uint64_t n, std::string const& prefix, std::string const& postix)
{
    std::string const s{ R"(B")" + prefix + to_binary(n) + postix + '"'};
    return s;
}


} // namespace detail


namespace /* anonymous */ {

    auto const numeric_convert =  ast::numeric_convert{ std::cerr };
}


BOOST_AUTO_TEST_CASE( bit_string_0 )
{
    std::string const literal{ R"(B"00_00")" };

    auto const [parse_ok, ast_node] = x3_test::parse_bit_string_literal(literal);
    BOOST_REQUIRE(parse_ok);

    auto const [conv_ok, value] = numeric_convert(ast_node);
    BOOST_REQUIRE(conv_ok);
    BOOST_TEST( value == 0 );
}


BOOST_AUTO_TEST_CASE( bit_string_1 )
{
    std::string const literal{ R"(B"00_01")" };

    auto const [parse_ok, ast_node] = x3_test::parse_bit_string_literal(literal);
    BOOST_REQUIRE(parse_ok);

    auto const [conv_ok, value] = numeric_convert(ast_node);
    BOOST_REQUIRE(conv_ok);
    BOOST_TEST( value == 1 );
}


BOOST_AUTO_TEST_CASE( bit_string_16 )
{
    std::string const literal{ R"(B"1_0000")" };

    auto const [parse_ok, ast_node] = x3_test::parse_bit_string_literal(literal);
    BOOST_REQUIRE(parse_ok);

    auto const [conv_ok, value] = numeric_convert(ast_node);
    BOOST_REQUIRE(conv_ok);
    BOOST_TEST( value == 16 );
}


BOOST_AUTO_TEST_CASE( bit_string_17 )
{
    std::string const literal{ R"(B"1_00_01")" };

    auto const [parse_ok, ast_node] = x3_test::parse_bit_string_literal(literal);
    BOOST_REQUIRE(parse_ok);

    auto const [conv_ok, value] = numeric_convert(ast_node);
    BOOST_REQUIRE(conv_ok);
    BOOST_TEST( value == 17 );
}


BOOST_AUTO_TEST_CASE( bit_string_uint32max )
{
    uint32_t N = std::numeric_limits<uint32_t>::max();

    std::string const literal{ detail::to_binary_literal(N) };

    auto const [parse_ok, ast_node] = x3_test::parse_bit_string_literal(literal);
    BOOST_REQUIRE(parse_ok);

    auto const [conv_ok, value] = numeric_convert(ast_node);
    BOOST_REQUIRE(conv_ok);
    BOOST_TEST( value == N );
}


BOOST_AUTO_TEST_CASE( bit_string_uint64max )
{
    uint64_t N = std::numeric_limits<uint64_t>::max();

    std::string const literal{ detail::to_binary_literal(N) };

    auto const [parse_ok, ast_node] = x3_test::parse_bit_string_literal(literal);
    BOOST_REQUIRE(parse_ok);

    auto const [conv_ok, value] = numeric_convert(ast_node);
    BOOST_REQUIRE(conv_ok);
    BOOST_TEST( value == N );
}


BOOST_AUTO_TEST_CASE( bit_string_uint64max_leading_zero )
{
    uint64_t N = std::numeric_limits<uint64_t>::max();

    std::string const literal{ detail::to_binary_literal(N, "0000_", "") };

    auto const [parse_ok, ast_node] = x3_test::parse_bit_string_literal(literal);
    BOOST_REQUIRE(parse_ok);

    auto const [conv_ok, value] = numeric_convert(ast_node);
    BOOST_REQUIRE(conv_ok);
    BOOST_TEST( value == N );
}


BOOST_AUTO_TEST_CASE( bit_string_uint64max_ovrflw )
{
    uint64_t N = std::numeric_limits<uint64_t>::max();

    std::string const literal{ detail::to_binary_literal(N, "_1") };

    //std::cout << N << " = " << literal << '\n';

    auto const [parse_ok, ast_node] = x3_test::parse_bit_string_literal(literal);
    BOOST_REQUIRE(parse_ok);    // must parse

    auto const [conv_ok, value] = numeric_convert(ast_node);
    BOOST_TEST(!conv_ok);       // must fail to convert
}


BOOST_AUTO_TEST_SUITE_END()



