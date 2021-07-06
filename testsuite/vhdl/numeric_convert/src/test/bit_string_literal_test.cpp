#include <testsuite/vhdl/numeric_convert/numeric_parser.hpp>
#include <testsuite/vhdl/numeric_convert/binary_string.hpp>

#include <ibis/vhdl/parser/diagnostic_handler.hpp>
#include <ibis/vhdl/parser/context.hpp>
#include <ibis/vhdl/type.hpp>

#include <ibis/vhdl/ast/node/bit_string_literal.hpp>
#include <ibis/vhdl/ast/numeric_convert.hpp>

#include <boost/test/unit_test.hpp>
#include <boost/test/data/test_case.hpp>
#include <boost/test/data/monomorphic.hpp>
#include <boost/test/tools/output_test_stream.hpp>

#include <iostream>
#include <sstream>
#include <limits>
#include <algorithm>
#include <cmath>
#include <vector>

// NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
BOOST_AUTO_TEST_SUITE(numeric_convert)

namespace detail {

//******************************************************************************
// bin/oct/hex generator helper functions
//******************************************************************************

static std::string to_bin_literal(uint64_t n, std::string const& postfix = "")
{
    using namespace testsuite::vhdl::numeric_convert::util;

    std::string s{ "B\"" + binary_string{ n }() + postfix + '"' };
    return s;
}

static std::string to_oct_literal(uint64_t n, std::string const& postfix = "")
{
    using namespace testsuite::vhdl::numeric_convert::util;

    std::string s{ "O\"" + octal_string{ n }() + postfix + '"' };
    return s;
}

static std::string to_hex_literal(uint64_t n, std::string const& postfix = "")
{
    using namespace testsuite::vhdl::numeric_convert::util;

    std::string s{ "X\"" + hexadecimal_string{ n }() + postfix + '"' };
    return s;
}

}  // namespace detail

namespace btt = boost::test_tools;

using ast::numeric_convert;

//******************************************************************************
// bit_string_literal
//******************************************************************************
std::vector<std::string> const bit_literal{
    // binary
    R"(B"00_00")",
    R"(B"00_01")",
    R"(B"1_0000")",
    R"(B"1_00_01")",
    R"(B"00_1_00_01")",  // leading zeros
    detail::to_bin_literal(std::numeric_limits<uint32_t>::max()),
    detail::to_bin_literal(std::numeric_limits<uint64_t>::max()),
    // octal
    R"(O"00_00")",
    R"(O"00_01")",
    R"(O"1_7654")",
    R"(O"7_6543210")",
    R"(O"000_7_6543210")",  // leading zeros
    detail::to_oct_literal(std::numeric_limits<uint32_t>::max()),
    detail::to_oct_literal(std::numeric_limits<uint64_t>::max()),
    // hexadecimal
    R"(X"00_00")",
    R"(X"00_01")",
    R"(X"1_AFFE")",
    R"(X"C001_CAFE")",
    R"(X"0000_C001_CAFE")",  // leading zeros
    detail::to_hex_literal(std::numeric_limits<uint32_t>::max()),
    detail::to_hex_literal(std::numeric_limits<uint64_t>::max()),
};

std::vector<ibis::vhdl::intrinsic::unsigned_integer_type> const bit_decimal{
    // binary
    0,
    1,
    16,
    17,
    17,
    std::numeric_limits<uint32_t>::max(),
    std::numeric_limits<uint64_t>::max(),
    // octal
    0,
    1,
    8108,
    16434824,
    16434824,
    std::numeric_limits<uint32_t>::max(),
    std::numeric_limits<uint64_t>::max(),
    // hexadecimal
    0,
    1,
    110590,
    3221342974,
    3221342974,
    std::numeric_limits<uint32_t>::max(),
    std::numeric_limits<uint64_t>::max(),
};

// NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
BOOST_DATA_TEST_CASE(bit_string_literal, utf_data::make(bit_literal) ^ bit_decimal, literal, N)
{
    using iterator_type = parser::iterator_type;

    parser::position_cache<iterator_type> position_cache;
    auto position_proxy = position_cache.add_file("<bit_string_literal>", literal);

    btt::output_test_stream os;
    parser::context ctx;
    parser::diagnostic_handler<iterator_type> diagnostic_handler{ os, ctx, position_proxy };

    auto const parse = testsuite::literal_parser<iterator_type>{};

    auto const [parse_ok, ast_node] = parse.bit_string_literal(position_proxy, diagnostic_handler);
    BOOST_REQUIRE(parse_ok);

    numeric_convert numeric{ diagnostic_handler };

    auto const [conv_ok, value] = numeric(ast_node);
    BOOST_REQUIRE(conv_ok);
    BOOST_TEST(std::get<numeric_convert::integer_type>(value) == N);

    os << vhdl::failure_status(ctx);
    if (!os.str().empty()) {
        std::cout << '\n' << os.str() << '\n';
    }
}

//******************************************************************************
// bit_string_literal overflow tests
//******************************************************************************
std::vector<std::string> const literal_ovflw{
    detail::to_bin_literal(std::numeric_limits<uint64_t>::max(), "_0"),
    detail::to_oct_literal(std::numeric_limits<uint64_t>::max(), "_0"),
    detail::to_hex_literal(std::numeric_limits<uint64_t>::max(), "_0"),
};

// NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
BOOST_DATA_TEST_CASE(bit_string_literal_uint64_ovflw, utf_data::make(literal_ovflw), literal)
{
    using iterator_type = parser::iterator_type;

    parser::position_cache<iterator_type> position_cache;
    auto position_proxy = position_cache.add_file("<bit_string_literal>", literal);

    btt::output_test_stream os;
    parser::context ctx;
    parser::diagnostic_handler<iterator_type> diagnostic_handler{ os, ctx, position_proxy };

    auto const parse = testsuite::literal_parser<iterator_type>{};

    auto const [parse_ok, ast_node] = parse.bit_string_literal(position_proxy, diagnostic_handler);
    BOOST_REQUIRE(parse_ok);  // must parse ...

    numeric_convert numeric{ diagnostic_handler };

    bool conv_ok = true;
    std::tie(conv_ok, std::ignore) = numeric(ast_node);
    BOOST_REQUIRE(!conv_ok);  // ... but must fail to convert

    os << vhdl::failure_status(ctx);
    if (!os.str().empty()) {
        std::cout << '\n' << os.str() << '\n';
    }
}

// NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
BOOST_AUTO_TEST_SUITE_END()
