/*
 * bit_string_literal.cpp
 *
 *  Created on: 29.05.2018
 *      Author: olaf
 */

#include <testsuite/numeric_convert/numeric_parser.hpp>

#include <eda/vhdl/ast/util/numeric_convert.hpp>

#include <boost/test/unit_test.hpp>

#include <iostream>


BOOST_AUTO_TEST_SUITE( numeric_convert )


namespace ast = eda::vhdl::ast;
namespace btt = boost::test_tools;


namespace /* anonymous */ {

    auto const numeric_convert =  ast::numeric_convert{};
}


BOOST_AUTO_TEST_CASE( value_0bin )
{
    std::string const literal{ R"(B"00_00")" };

    auto const [parse_ok, ast_node] = x3_test::parse_bit_string_literal(literal);
    BOOST_REQUIRE(parse_ok);

    auto const [conv_ok, value] = numeric_convert(ast_node);
    BOOST_REQUIRE(conv_ok);
    BOOST_TEST( value == 0 );
}

BOOST_AUTO_TEST_CASE( value_1bin )
{
    std::string const literal{ R"(B"00_01")" };

    auto const [parse_ok, ast_node] = x3_test::parse_bit_string_literal(literal);
    BOOST_REQUIRE(parse_ok);

    auto const [conv_ok, value] = numeric_convert(ast_node);
    BOOST_REQUIRE(conv_ok);
    BOOST_TEST( value == 1 );
}

BOOST_AUTO_TEST_CASE( value_16bin )
{
    std::string const literal{ R"(B"1_0000")" };

    auto const [parse_ok, ast_node] = x3_test::parse_bit_string_literal(literal);
    BOOST_REQUIRE(parse_ok);

    auto const [conv_ok, value] = numeric_convert(ast_node);
    BOOST_REQUIRE(conv_ok);
    BOOST_TEST( value == 16 );
}

BOOST_AUTO_TEST_SUITE_END()



