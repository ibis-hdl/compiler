#include <testsuite/vhdl/numeric_convert/numeric_parser.hpp>
#include <testsuite/vhdl/numeric_convert/binary_string.hpp>

#include <ibis/vhdl/ast/node/bit_string_literal.hpp>
#include <ibis/vhdl/ast/numeric_convert.hpp>
#include <ibis/vhdl/parser/position_cache.hpp>
#include <ibis/vhdl/parser/iterator_type.hpp>
#include <ibis/vhdl/type.hpp>

#include <boost/test/unit_test.hpp>
#include <boost/test/data/test_case.hpp>
#include <boost/test/data/monomorphic.hpp>
#include <boost/test/tools/output_test_stream.hpp>

#include <boost/core/ignore_unused.hpp>

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

namespace  // anonymous
{

namespace btt = boost::test_tools;

// The numeric_convert utility writes messages, but concrete error messages
// aren't checked. For debugging is useful to see them otherwise. Switch to
// ostream sink to hide them or let's write to cerr to see them.
// Note, using global numeric_convert object tests  implicit of state less
// conversion, otherwise test must fail due to. */
//
// Note: technically, we initialize globals that access extern objects,
// and therefore can lead to order-of-initialization problems.

bool constexpr no_messages = true;

// NOLINTNEXTLINE(cppcoreguidelines-interfaces-global-init)
auto const numeric_convert = []() {
    if constexpr (no_messages) {
        static btt::output_test_stream nil_sink;
        return ast::numeric_convert{ nil_sink };
    }
    else {
        return ast::numeric_convert(std::cerr);
    }
}();

}  // namespace

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
    std::size_t const id = position_cache.add_file("<bit_string_literal>", literal);
    auto const position_proxy{ position_cache.handle(id) };

    auto const parse = testsuite::literal_parser<iterator_type>{};

    auto const [parse_ok, ast_node] = parse.bit_string_literal(position_proxy);
    BOOST_REQUIRE(parse_ok);

    auto const [conv_ok, value] = numeric_convert(ast_node);
    BOOST_REQUIRE(conv_ok);
    BOOST_TEST(value == N);
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
    std::size_t const id = position_cache.add_file("<bit_string_literal>", literal);
    auto const position_proxy{ position_cache.handle(id) };

    auto const parse = testsuite::literal_parser<iterator_type>{};

    auto const [parse_ok, ast_node] = parse.bit_string_literal(position_proxy);
    BOOST_REQUIRE(parse_ok);  // must parse ...

    auto const [conv_ok, value] = numeric_convert(ast_node);
    BOOST_REQUIRE(!conv_ok);  // ... but must fail to convert

    boost::ignore_unused(value);
}

// NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
BOOST_AUTO_TEST_SUITE_END()
