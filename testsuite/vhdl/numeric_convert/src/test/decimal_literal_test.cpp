//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-or-later
//

#include <testsuite/vhdl/numeric_convert/numeric_parser.hpp>

#include <ibis/util/file_mapper.hpp>
#include <ibis/vhdl/parser/position_cache.hpp>
#include <ibis/vhdl/parser/diagnostic_handler.hpp>
#include <ibis/vhdl/parser/context.hpp>
#include <ibis/vhdl/type.hpp>

#include <ibis/vhdl/ast/node/decimal_literal.hpp>
#include <ibis/vhdl/ast/numeric_convert.hpp>

#include <boost/test/unit_test.hpp>
#include <boost/test/data/test_case.hpp>
#include <boost/test/data/monomorphic.hpp>
#include <boost/test/tools/output_test_stream.hpp>

#include <iostream>
#include <sstream>
#include <limits>
#include <algorithm>
#include <type_traits>
#include <cmath>
#include <vector>

// NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
BOOST_AUTO_TEST_SUITE(numeric_convert)

namespace detail {

//******************************************************************************
// generator helper functions
//******************************************************************************
template <class T>
typename std::enable_if<std::is_integral<T>::value, std::string>::type to_decimal_literal(T value)
{
    //  intentionally disabled
    if constexpr ((false)) {  // NOLINT(readability-simplify-boolean-expr)
        std::cout << "to_decimal_literal(" << value << ") <"
                  << boost::typeindex::type_id<T>().pretty_name() << ">\n";
    }

    return std::to_string(value);
}

template <class T>
typename std::enable_if<std::is_floating_point<T>::value, std::string>::type to_decimal_literal(
    T value)
{
    // intentionally disabled
    if constexpr ((false)) {  // NOLINT(readability-simplify-boolean-expr)
        std::cout << "to_decimal_literal(" << value << ") <"
                  << boost::typeindex::type_id<T>().pretty_name() << ">\n";
    }
    return std::to_string(value);
}

}  // namespace detail

namespace btt = boost::test_tools;

using namespace ibis::vhdl;

using ast::numeric_convert;

//******************************************************************************
// integer decimal_literal
//******************************************************************************
std::vector<std::string> const dec_int_lit{
    "0",
    "1",
    "1_000",
    "1e6",
    detail::to_decimal_literal(std::numeric_limits<uint32_t>::max()),
    detail::to_decimal_literal(std::numeric_limits<uint64_t>::max()),
};

std::vector<ibis::vhdl::intrinsic::unsigned_integer_type> const dec_int{
    0, 1, 1000, 1000000, std::numeric_limits<uint32_t>::max(), std::numeric_limits<uint64_t>::max(),
};

// NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
BOOST_DATA_TEST_CASE(decimal_literal_integer, utf_data::make(dec_int_lit) ^ dec_int, literal, N)
{
    using iterator_type = parser::iterator_type;

    ibis::util::file_mapper file_mapper{};
    auto const file_id = file_mapper.add_file("<decimal_literal>", literal);

    parser::position_cache<iterator_type> position_cache{};
    auto position_proxy = position_cache.get_proxy(file_id);

    btt::output_test_stream os;
    parser::context ctx;
    parser::diagnostic_handler<iterator_type> diagnostic_handler{ os, ctx,
                                                                  std::move(position_proxy) };

    auto const parse = testsuite::literal_parser<iterator_type>{};

    auto const [parse_ok, ast_node] = parse.decimal_literal(position_proxy, diagnostic_handler);
    BOOST_TEST_REQUIRE(parse_ok);

    using numeric_type_specifier = ibis::vhdl::ast::decimal_literal::numeric_type_specifier;
    BOOST_TEST_REQUIRE(ast_node.type_specifier == numeric_type_specifier::integer);

    numeric_convert numeric{ diagnostic_handler };

    auto const [conv_ok, value] = numeric(ast_node);
    BOOST_TEST_REQUIRE(conv_ok);
    BOOST_TEST(std::get<numeric_convert::integer_type>(value) == N);

    os << failure_status(ctx);
    if (!os.str().empty()) {
        // std::cout << '\n' << os.str() << '\n';
    }
}

// NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
BOOST_AUTO_TEST_CASE(decimal_literal_uint64max_ovrflw)
{
    uint64_t N = std::numeric_limits<uint64_t>::max();

    std::string const literal{ detail::to_decimal_literal(N) + "_0" };

    using iterator_type = parser::iterator_type;

    ibis::util::file_mapper file_mapper{};
    auto const file_id = file_mapper.add_file("<decimal_literal>", literal);

    parser::position_cache<iterator_type> position_cache{};
    auto position_proxy = position_cache.get_proxy(file_id);

    btt::output_test_stream os;
    parser::context ctx;
    parser::diagnostic_handler<iterator_type> diagnostic_handler{ os, ctx,
                                                                  std::move(position_proxy) };

    auto const parse = testsuite::literal_parser<iterator_type>{};

    auto const [parse_ok, ast_node] = parse.decimal_literal(position_proxy, diagnostic_handler);
    BOOST_TEST_REQUIRE(parse_ok);  // must parse ...

    numeric_convert numeric{ diagnostic_handler };

    bool conv_ok = true;
    std::tie(conv_ok, std::ignore) = numeric(ast_node);
    BOOST_TEST_REQUIRE(!conv_ok);  // ... but must fail to convert

    os << failure_status(ctx);
    if (!os.str().empty()) {
        // std::cout << '\n' << os.str() << '\n';
    }
}

//******************************************************************************
// real decimal_literal
//******************************************************************************
std::vector<std::string> const dec_real_lit{
    "0.0",
    "1.0",
    "1_000.000",
    "1.0e6",
    "1_024.125_0",
    "2.04825e+3",
    "2.04825e3",
    "2_048.25e-3",
    // from boost.spirit.x3 [x3/real2.cpp BOOST_SPIRIT_TEST_REAL_PRECISION test](
    // https://github.com/boostorg/spirit/blob/master/test/x3/real2.cpp)
    //
    // Note: The source's comments says exact match, but it seems machine
    //       depend. It's true on [Wandbox example](
    //       https://wandbox.org/permlink/be3cmg0STFleYAsK), but not on
    //       e.g. Windows10/MinGW. Hence test is based on tolerance
    //       as described at [Boost.UTF: Floating point comparison](
    //       https://www.boost.org/doc/libs/1_67_0/libs/test/doc/html/boost_test/testing_tools/extended_comparison/floating_point.html)
    //
    "2.0332938517515416e-308",
    "2.0332938517515416e+307",
};

std::vector<ibis::vhdl::intrinsic::real_type> const dec_real{
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

// IIFE Idiom used to initialize, see
// [IIFE for Complex Initialization](
//  https://www.bfilipek.com/2016/11/iife-for-complex-initialization.html),
// required for CLang++, but not for G++ (where probably std::pow() is
// probably constexpr).
double const REAL_TOLERANCE = []() {
    return std::pow(10, -std::numeric_limits<double>::digits10);
}();

// NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
BOOST_DATA_TEST_CASE(decimal_literal_real, utf_data::make(dec_real_lit) ^ dec_real, literal, N)
{
    using iterator_type = parser::iterator_type;

    ibis::util::file_mapper file_mapper{};
    auto const file_id = file_mapper.add_file("<decimal_literal>", literal);

    parser::position_cache<iterator_type> position_cache{};
    auto position_proxy = position_cache.get_proxy(file_id);

    btt::output_test_stream os;
    parser::context ctx;
    parser::diagnostic_handler<iterator_type> diagnostic_handler{ os, ctx,
                                                                  std::move(position_proxy) };

    auto const parse = testsuite::literal_parser<iterator_type>{};

    auto const [parse_ok, ast_node] = parse.decimal_literal(position_proxy, diagnostic_handler);
    BOOST_TEST_REQUIRE(parse_ok);

    using numeric_type_specifier = ibis::vhdl::ast::decimal_literal::numeric_type_specifier;
    BOOST_TEST_REQUIRE(ast_node.type_specifier == numeric_type_specifier::real);

    numeric_convert numeric{ diagnostic_handler };

    auto const [conv_ok, value] = numeric(ast_node);
    BOOST_TEST_REQUIRE(conv_ok);
    BOOST_TEST(std::get<numeric_convert::real_type>(value) == N, btt::tolerance(REAL_TOLERANCE));

    os << failure_status(ctx);
    if (!os.str().empty()) {
        std::cout << '\n' << os.str() << '\n';
    }
}

// NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
BOOST_AUTO_TEST_SUITE_END()
