/*
 * decimal_literal_test.cpp
 *
 *  Created on: 31.05.2018
 *      Author: olaf
 */

#include <testsuite/numeric_convert/numeric_parser.hpp>

#include <eda/vhdl/ast/util/numeric_convert.hpp>
#include <eda/vhdl/type.hpp>

#include <boost/test/unit_test.hpp>
#include <boost/test/data/test_case.hpp>
#include <boost/test/data/monomorphic.hpp>
#include <boost/test/output_test_stream.hpp>

#include <boost/type_index.hpp>
#include <boost/core/ignore_unused.hpp>

#include <iostream>
#include <sstream>
#include <limits>
#include <algorithm>
#include <type_traits>
#include <cmath>
#include <vector>


BOOST_AUTO_TEST_SUITE( decimal_literal )


namespace ast = eda::vhdl::ast;
namespace btt = boost::test_tools;
namespace but_data = boost::unit_test::data;


namespace detail {


/*******************************************************************************
 * generator helper functions
 ******************************************************************************/
template<class T>
typename std::enable_if<
    std::is_integral<T>::value, std::string
>::type
to_decimal_literal(T value)
{
#if 0
    std::cout << "to_decimal_literal(" << value << ") <"
              << boost::typeindex::type_id<T>().pretty_name()
              << ">\n";
#endif
    return std::to_string(value);
}


template<class T>
typename std::enable_if<
    std::is_floating_point<T>::value, std::string
>::type
to_decimal_literal(T value)
{
#if 0
    std::cout << "to_decimal_literal(" << value << ") <"
              << boost::typeindex::type_id<T>().pretty_name()
              << ">\n";
#endif
    return std::to_string(value);
}


} // namespace detail


namespace /* anonymous */ {

// discard concrete error messages
btt::output_test_stream error_log;

// implicit check of state less conversion, otherwise test must fail
auto const numeric_convert =  ast::numeric_convert{ error_log };

}


namespace intrinsic {
    using unsigned_integer_type = eda::vhdl::intrinsic::unsigned_integer_type;
    using real_type = eda::vhdl::intrinsic::real_type;
}

/*******************************************************************************
 * integer decimal_literal
 ******************************************************************************/
std::vector<std::string> const dec_int_lit{
    "0",
    "1",
    "1_000",
    "1e6",
    detail::to_decimal_literal(std::numeric_limits<uint32_t>::max()),
    detail::to_decimal_literal(std::numeric_limits<uint64_t>::max()),
};

std::vector<intrinsic::unsigned_integer_type> dec_int{
    0,
    1,
    1000,
    1000000,
    std::numeric_limits<uint32_t>::max(),
    std::numeric_limits<uint64_t>::max(),
};


BOOST_DATA_TEST_CASE(
    integer,
    but_data::make(dec_int_lit) ^ dec_int,
    literal,                      N)
{
    auto const [parse_ok, ast_node] = x3_test::parse_decimal_literal(literal);
    BOOST_REQUIRE(parse_ok);

    using kind_specifier = eda::vhdl::ast::decimal_literal::kind_specifier;
    BOOST_REQUIRE(ast_node.kind_type == kind_specifier::integer);

    auto const [conv_ok, value] = numeric_convert(ast_node);
    BOOST_REQUIRE(conv_ok);
    BOOST_TEST( value == N );
}


BOOST_AUTO_TEST_CASE( integer_uint64max_ovrflw )
{
    uint64_t N = std::numeric_limits<uint64_t>::max();

    std::string const literal{ detail::to_decimal_literal(N) + "_0" };

    auto const [parse_ok, ast_node] = x3_test::parse_decimal_literal(literal);
    BOOST_REQUIRE(parse_ok);    // must parse ...

    auto const [conv_ok, value] = numeric_convert(ast_node);
    BOOST_TEST(!conv_ok);       // ... but must fail to convert

    boost::ignore_unused(value);
}


/*******************************************************************************
 * real decimal_literal
 ******************************************************************************/
std::vector<std::string> const dec_real_lit{
    "0.0",
    "1.0",
    "1_000.000",
    "1.0e6",
    "1_024.125_0",
    "2.04825e+3",
    "2.04825e3",
    "2_048.25e-3",
/* from boost.spirit.x3 [x3/real2.cpp BOOST_SPIRIT_TEST_REAL_PRECISION test](
 * https://github.com/boostorg/spirit/blob/master/test/x3/real2.cpp)
 *
 * Note: The source's comments says exact match, but it seems machine
 *       depend. It's true on [Wandbox example](
 *       https://wandbox.org/permlink/be3cmg0STFleYAsK), but not on
 *       e.g. Windows10/MinGW. Hence test is based on tolerance
 *       as described at [Boost.UTF: Floating point comparison](
 *       https://www.boost.org/doc/libs/1_67_0/libs/test/doc/html/boost_test/testing_tools/extended_comparison/floating_point.html)
 */
    "2.0332938517515416e-308",
    "2.0332938517515416e+307",
};

std::vector<intrinsic::real_type> dec_real{
    0.0,
    1.0,
    1000.0,
    1.0e6,
    1024.125,
    2048.25,
    2048.25,
    2.04825,
    // from boost.spirit.x3 BOOST_SPIRIT_TEST_REAL_PRECISION
    2.0332938517515416e-308,
    2.0332938517515416e+307,
};

/* IIFE Idiom used to initialize, see
 * [IIFE for Complex Initialization](
 *  https://www.bfilipek.com/2016/11/iife-for-complex-initialization.html),
 * required for CLang++, but not for G++ (where probably std::pow() is
 * probably constexpr). */
double const REAL_TOLERANCE = []() {
    return std::pow(10, -std::numeric_limits<double>::digits10);
}();


BOOST_DATA_TEST_CASE(
    real,
    but_data::make(dec_real_lit) ^ dec_real,
    literal,                       N)
{
    auto const [parse_ok, ast_node] = x3_test::parse_decimal_literal(literal);
    BOOST_REQUIRE(parse_ok);

    using kind_specifier = eda::vhdl::ast::decimal_literal::kind_specifier;
    BOOST_REQUIRE(ast_node.kind_type == kind_specifier::real);

    auto const [conv_ok, value] = numeric_convert(ast_node);
    BOOST_REQUIRE(conv_ok);
    BOOST_TEST(value == N, btt::tolerance(REAL_TOLERANCE));
}



BOOST_AUTO_TEST_SUITE_END()






