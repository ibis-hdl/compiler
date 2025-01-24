//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-or-later
//

#include <testsuite/vhdl/numeric_convert/numeric_parser.hpp>
#include <testsuite/vhdl/numeric_convert/bit_string_literal_generator.hpp>
#include <testsuite/util/diagnostic_handler_fixture.hpp>

#include <ibis/util/file_mapper.hpp>
#include <ibis/vhdl/parser/position_cache.hpp>
#include <ibis/vhdl/parser/diagnostic_handler.hpp>
#include <ibis/vhdl/parser/context.hpp>
#include <ibis/vhdl/type.hpp>

#include <ibis/vhdl/ast/node/bit_string_literal.hpp>
#include <ibis/vhdl/ast/numeric_convert.hpp>

#include <boost/test/unit_test.hpp>
#include <boost/test/data/test_case.hpp>
#include <boost/test/data/monomorphic.hpp>
#include <boost/test/tools/output_test_stream.hpp>

#include <testsuite/namespace_alias.hpp>  // IWYU pragma: keep

#include <iostream>
#include <format>
#include <string_view>
#include <string>
#include <limits>
#include <vector>
#include <cmath>
#include <cstdint>

// NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
BOOST_AUTO_TEST_SUITE(numeric_convert)

namespace detail {
static auto const uint32_max = std::numeric_limits<std::uint32_t>::max();
static auto const uint64_max = std::numeric_limits<std::uint64_t>::max();
}  // namespace detail

//
// check, that bit_string_literal_generator is working as expected
//
// NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
BOOST_AUTO_TEST_CASE(bit_string_literal_pre_condition)
{
    using namespace testsuite::vhdl::numeric_convert;
    using bsl = util::bit_string_literal_generator;

    // binary
    BOOST_REQUIRE(bsl::bin(1, "_010") == R"(b"1_010")");
    BOOST_REQUIRE(bsl::bin(detail::uint32_max) == R"(b"11111111111111111111111111111111")");
    BOOST_REQUIRE(bsl::bin(detail::uint64_max) ==
                  R"(b"1111111111111111111111111111111111111111111111111111111111111111")");

    // octal
    BOOST_REQUIRE(bsl::oct(1, "_010") == R"(o"1_010")");
    BOOST_REQUIRE(bsl::oct(detail::uint32_max) == R"(o"37777777777")");
    BOOST_REQUIRE(bsl::oct(detail::uint64_max) == R"(o"1777777777777777777777")");

    // hexadecimal
    BOOST_REQUIRE(bsl::hex(1, "_010") == R"(x"1_010")");
    BOOST_REQUIRE(bsl::hex(detail::uint32_max) == R"(x"ffffffff")");
    BOOST_REQUIRE(bsl::hex(detail::uint64_max) == R"(x"ffffffffffffffff")");
}

namespace valid_data {

using base_specifier = ibis::vhdl::ast::bit_string_literal::numeric_base_specifier;
using namespace std::literals::string_view_literals;

// Valid input to test the grammar rule, no numeric conversion here.
static const std::string input = []() {
    constexpr std::string_view pkg_template = R"(
-- test 'bit_string_literal' numeric conversion
PACKAGE bitstring IS
    -- bin
    CONSTANT bin_01         : bit_vector := B"00_00";
    CONSTANT bin_02         : bit_vector := b"00_01";
    CONSTANT bin_03         : bit_vector := b"1_0000";
    CONSTANT bin_04         : bit_vector := b"00_1_00_01";  // leading zeros
    CONSTANT bin_uint32_max : bit_vector := {};
    CONSTANT bin_uint64_max : bit_vector := {};
    -- oct
    CONSTANT oct_01         : bit_vector := O"01234";
    CONSTANT oct_02         : bit_vector := o"01234";
    CONSTANT oct_03         : bit_vector := o"777";
    CONSTANT oct_04         : bit_vector := o"7";
    CONSTANT oct_05         : bit_vector := o"7_42";
    CONSTANT oct_06         : bit_vector := o"0_1_2";
    CONSTANT oct_uint32_max : bit_vector := {};
    CONSTANT oct_uint64_max : bit_vector := {};
    -- hex
    CONSTANT hex_01         : bit_vector := X"01234";
    CONSTANT hex_02         : bit_vector := x"01234";
    CONSTANT hex_03         : bit_vector := x"aB";
    CONSTANT hex_04         : bit_vector := x"f";
    CONSTANT hex_05         : bit_vector := x"ffff";
    CONSTANT hex_06         : bit_vector := x"a_b";
    CONSTANT hex_07         : bit_vector := x"a_b_c";
    CONSTANT hex_uint32_max : bit_vector := {};
    CONSTANT hex_uint64_max : bit_vector := {};
END PACKAGE;
)";
    using namespace testsuite::vhdl::numeric_convert;
    using gen = util::bit_string_literal_generator;
    auto constexpr uint32_max = detail::uint32_max;
    auto constexpr uint64_max = detail::uint64_max;

    return std::format(pkg_template,
                       // bin uint32_max, uint64_max
                       gen::bin(uint32_max), gen::bin(uint64_max),
                       // oct uint32_max, uint64_max
                       gen::oct(uint32_max), gen::oct(uint64_max),
                       // hex uint32_max, uint64_max
                       gen::hex(uint32_max), gen::hex(uint64_max));
}();

}  // namespace valid_data

// clang-format off
BOOST_AUTO_TEST_CASE(bit_string_literal__valid_test,    // test shall pass
                     *utf::label("bit_string_literal")
                     *utf::label("numeric"))
// clang-format on
{
    BOOST_TEST(true == true);

    // ToDo [Test] same approach as grammar/test_bit_string_literal, maybe move it into
}

using namespace ibis::vhdl;
using ast::numeric_convert;

//******************************************************************************
// bit_string_literal
//******************************************************************************
using namespace testsuite::vhdl::numeric_convert;
using bsl = util::bit_string_literal_generator;

std::vector<std::string> const bit_literal{
    // binary
    R"(B"00_00")",
    R"(B"00_01")",
    R"(B"1_0000")",
    R"(B"1_00_01")",
    R"(B"00_1_00_01")",  // leading zeros
    bsl::bin(detail::uint32_max),
    bsl::bin(detail::uint64_max),
    // octal
    R"(O"00_00")",
    R"(O"00_01")",
    R"(O"1_7654")",
    R"(O"7_6543210")",
    R"(O"000_7_6543210")",  // leading zeros
    bsl::oct(detail::uint32_max),
    bsl::oct(detail::uint64_max),
    // hexadecimal
    R"(X"00_00")",
    R"(X"00_01")",
    R"(X"1_AFFE")",
    R"(X"C001_CAFE")",
    R"(X"0000_C001_CAFE")",  // leading zeros
    bsl::hex(detail::uint32_max),
    bsl::hex(detail::uint64_max),
};

std::vector<ibis::vhdl::intrinsic::unsigned_integer_type> const bit_decimal{
    // binary
    0,
    1,
    16,
    17,
    17,
    detail::uint32_max,
    detail::uint64_max,
    // octal
    0,
    1,
    8108,
    16434824,
    16434824,
    detail::uint32_max,
    detail::uint64_max,
    // hexadecimal
    0,
    1,
    110590,
    3221342974,
    3221342974,
    detail::uint32_max,
    detail::uint64_max,
};

// NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
BOOST_DATA_TEST_CASE(bit_string_literal, utf_data::make(bit_literal) ^ bit_decimal, literal, N)
{
    using iterator_type = parser::iterator_type;

    ibis::util::file_mapper file_mapper{};
    auto const file_id = file_mapper.add_file("<bit_string_literal>", literal);

    parser::position_cache<iterator_type> position_cache{ file_mapper };
    auto position_proxy = position_cache.get_proxy(file_id);

    btt::output_test_stream os;
    parser::context ctx;
    parser::diagnostic_handler<iterator_type> diagnostic_handler{ os, ctx,
                                                                  std::move(position_proxy) };

    auto const parse = testsuite::literal_parser<iterator_type>{};

    auto const [parse_ok, ast_node] = parse.bit_string_literal(position_proxy, diagnostic_handler);
    BOOST_REQUIRE(parse_ok);

    numeric_convert numeric{ diagnostic_handler };

    auto const [conv_ok, value] = numeric(ast_node);
    BOOST_REQUIRE(conv_ok);
    BOOST_TEST(std::get<numeric_convert::integer_type>(value) == N);

    os << failure_status(ctx);
    if (!os.str().empty()) {
        // std::cout << '\n' << os.str() << '\n';
    }
}

//******************************************************************************
// bit_string_literal overflow tests
//******************************************************************************
std::vector<std::string> const literal_ovflw{
    bsl::bin(detail::uint64_max, "_0"),
    bsl::oct(detail::uint64_max, "_0"),
    bsl::hex(detail::uint64_max, "_0"),
};

// NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
BOOST_DATA_TEST_CASE(bit_string_literal_uint64_ovflw, utf_data::make(literal_ovflw), literal)
{
    using iterator_type = parser::iterator_type;

    ibis::util::file_mapper file_mapper{};
    auto const file_id = file_mapper.add_file("<bit_string_literal>", literal);

    parser::position_cache<iterator_type> position_cache{ file_mapper };
    auto position_proxy = position_cache.get_proxy(file_id);

    btt::output_test_stream os;
    parser::context ctx;
    parser::diagnostic_handler<iterator_type> diagnostic_handler{ os, ctx,
                                                                  std::move(position_proxy) };

    auto const parse = testsuite::literal_parser<iterator_type>{};

    auto const [parse_ok, ast_node] = parse.bit_string_literal(position_proxy, diagnostic_handler);
    BOOST_REQUIRE(parse_ok);  // must parse ...

    numeric_convert numeric{ diagnostic_handler };

    bool conv_ok = true;
    std::tie(conv_ok, std::ignore) = numeric(ast_node);
    BOOST_REQUIRE(!conv_ok);  // ... but must fail to convert

    os << failure_status(ctx);
    if (!os.str().empty()) {
        // std::cout << '\n' << os.str() << '\n';
    }
}

// NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
BOOST_AUTO_TEST_SUITE_END()
