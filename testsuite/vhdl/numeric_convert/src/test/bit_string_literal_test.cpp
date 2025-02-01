//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-or-later
//

#include <testsuite/vhdl/numeric_convert/numeric_parser.hpp>
#include <testsuite/vhdl/numeric_convert/bit_string_literal_generator.hpp>
#include <testsuite/testsuite_parser.hpp>

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

// global aliases and namespaces
using namespace ibis::vhdl;
using bsl_gen = testsuite::vhdl::numeric_convert::util::bit_string_literal_generator;

// -------------------------------------------------------------------------------------------------
// check, that bit_string_literal_generator is working as expected
// -------------------------------------------------------------------------------------------------
// NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
BOOST_AUTO_TEST_CASE(bit_string_literal_requirements_check)
{
    using namespace testsuite::vhdl::numeric_convert;

    // binary
    BOOST_REQUIRE(bsl_gen::bin(1, "_010") == R"(b"1_010")");
    BOOST_REQUIRE(bsl_gen::bin(detail::uint32_max) == R"(b"11111111111111111111111111111111")");
    BOOST_REQUIRE(bsl_gen::bin(detail::uint64_max) ==
                  R"(b"1111111111111111111111111111111111111111111111111111111111111111")");

    // octal
    BOOST_REQUIRE(bsl_gen::oct(1, "_010") == R"(o"1_010")");
    BOOST_REQUIRE(bsl_gen::oct(detail::uint32_max) == R"(o"37777777777")");
    BOOST_REQUIRE(bsl_gen::oct(detail::uint64_max) == R"(o"1777777777777777777777")");

    // hexadecimal
    BOOST_REQUIRE(bsl_gen::hex(1, "_010") == R"(x"1_010")");
    BOOST_REQUIRE(bsl_gen::hex(detail::uint32_max) == R"(x"ffffffff")");
    BOOST_REQUIRE(bsl_gen::hex(detail::uint64_max) == R"(x"ffffffffffffffff")");
}

// -------------------------------------------------------------------------------------------------
// valid input and expected data
// -------------------------------------------------------------------------------------------------
namespace valid_data {

// XXX check only the converted results with 0, 1, 42 and uint { 32, 64 }::max only.

static const std::string input = []() {
    // VHDL package template
    constexpr std::string_view pkg_template = R"(
-- test 'bit_string_literal' numeric conversion
PACKAGE bitstring IS
    -- bin
    CONSTANT bin_01         : bit_vector := B"00_0_0";
    CONSTANT bin_02         : bit_vector := b"00_0_1";
    CONSTANT bin_03         : bit_vector := b"1_0000";
    CONSTANT bin_04         : bit_vector := b"1_0001";      // all valid digits
    CONSTANT bin_05         : bit_vector := b"00_1_00_01";  // ~ with leading zeros
    CONSTANT bin_uint32_max : bit_vector := {};
    CONSTANT bin_uint64_max : bit_vector := {};
    -- oct
    CONSTANT oct_01         : bit_vector := O"00_0_0";
    CONSTANT oct_02         : bit_vector := o"00_0_1";
    CONSTANT oct_03         : bit_vector := o"7_6543210";     // all valid digits
    CONSTANT oct_04         : bit_vector := o"000_7_6543210"; // ~ with leading zeros
    CONSTANT oct_uint32_max : bit_vector := {};
    CONSTANT oct_uint64_max : bit_vector := {};
    -- hex
    CONSTANT hex_01         : bit_vector := X"00_0_0";
    CONSTANT hex_02         : bit_vector := x"00_0_1";
    CONSTANT hex_03         : bit_vector := x"0123456789";  // valid digits
    CONSTANT hex_04         : bit_vector := x"ABCDEF";      // valid digits
    CONSTANT hex_05         : bit_vector := x"0ABCDEF";     // ~ with leading zeros
    CONSTANT hex_uint32_max : bit_vector := {};
    CONSTANT hex_uint64_max : bit_vector := {};
END PACKAGE;
)";
    auto constexpr uint32_max = detail::uint32_max;
    auto constexpr uint64_max = detail::uint64_max;

    // format uint{32,64}::max values into input using pkg_template
    return std::format(pkg_template,
                       // bin uint32_max, uint64_max
                       bsl_gen::bin(uint32_max), bsl_gen::bin(uint64_max),
                       // oct uint32_max, uint64_max
                       bsl_gen::oct(uint32_max), bsl_gen::oct(uint64_max),
                       // hex uint32_max, uint64_max
                       bsl_gen::hex(uint32_max), bsl_gen::hex(uint64_max));
}();

using numeric_base_specifier = ibis::vhdl::ast::bit_string_literal::numeric_base_specifier;

// clang-format off_
// NOLINTNEXTLINE(cppcoreguidelines-avoid-c-arrays,modernize-avoid-c-arrays)
struct {
    numeric_base_specifier base_specifier;
    std::string_view literal;
    std::string_view formatted;
    ibis::vhdl::intrinsic::unsigned_integer_type result;
} constexpr gold_data[] = {
    // bin
    { .base_specifier = numeric_base_specifier::base2,
      .literal = "00_0_0",
      .formatted = "b00_0_0",
      .result = 0 },
    { .base_specifier = numeric_base_specifier::base2,
      .literal = "00_0_1",
      .formatted = "b00_0_1",
      .result = 0 },
    { .base_specifier = numeric_base_specifier::base2,
      .literal = "1_0000",
      .formatted = "b1_0000",
      .result = 0 },
    { .base_specifier = numeric_base_specifier::base2,
      .literal = "1_0001",
      .formatted = "b1_0001",
      .result = 0 },
    { .base_specifier = numeric_base_specifier::base2,
      .literal = "00_1_00_01",
      .formatted = "b00_1_00_01",
      .result = 0 },
    { .base_specifier = numeric_base_specifier::base2,
      .literal = "11111111111111111111111111111111",
      .formatted = "b11111111111111111111111111111111",
      .result = 0 },
    { .base_specifier = numeric_base_specifier::base2,
      .literal = "1111111111111111111111111111111111111111111111111111111111111111",
      .formatted = "b1111111111111111111111111111111111111111111111111111111111111111",
      .result = 0 },
    // oct
    { .base_specifier = numeric_base_specifier::base8,
      .literal = "o00_0_0",
      .formatted = "o00_0_0",
      .result = 0 },
    { .base_specifier = numeric_base_specifier::base8,
      .literal = "o00_0_1",
      .formatted = "o00_0_1",
      .result = 0 },
    { .base_specifier = numeric_base_specifier::base8,
      .literal = "O7_6543210",
      .formatted = "o7_6543210",
      .result = 0 },
    { .base_specifier = numeric_base_specifier::base8,
      .literal = "o000_7_6543210",
      .formatted = "o000_7_6543210",
      .result = 0 },
    { .base_specifier = numeric_base_specifier::base8,
      .literal = "O37777777777",
      .formatted = "o37777777777",
      .result = 0 },
    { .base_specifier = numeric_base_specifier::base8,
      .literal = "o1777777777777777777777",
      .formatted = "o1777777777777777777777",
      .result = 0 },
    // hex
    { .base_specifier = numeric_base_specifier::base16,
      .literal = "00_0_0",
      .formatted = "x00_0_0",
      .result = 0 },
    { .base_specifier = numeric_base_specifier::base16,
      .literal = "00_0_1",
      .formatted = "x00_0_1",
      .result = 0 },
    { .base_specifier = numeric_base_specifier::base16,
      .literal = "0123456789",
      .formatted = "x0123456789",
      .result = 0 },
    { .base_specifier = numeric_base_specifier::base16,
      .literal = "ABCDEF",
      .formatted = "ABCDEF",
      .result = 0 },
    { .base_specifier = numeric_base_specifier::base16,
      .literal = "0ABCDEF",
      .formatted = "0ABCDEF",
      .result = 0 },
    { .base_specifier = numeric_base_specifier::base16,
      .literal = "FFFFFFFF",
      .formatted = "xFFFFFFFF",
      .result = 0 },
    { .base_specifier = numeric_base_specifier::base16,
      .literal = "FFFFFFFFFFFFFFFF",
      .formatted = "xFFFFFFFFFFFFFFFF",
      .result = 0 },
};
// clang-format on

template <typename GoldDataT, bool verbose = false>
struct test_worker {
    test_worker(GoldDataT const& gold_data)
        : gold{ gold_data }
        , os{ std::cout }
    {
    }

    void operator()(ast::constant_declaration const& node,
                    [[maybe_unused]] std::string_view /* node_name */) const
    {
        if constexpr (verbose) {
            // ToDo [C++20] non-critical C++20 std::format, more complex work using ast walker
            static ast::printer print(os);
            os << std::format("({:2d}/{:2d}): identifier '", index + 1, std::size(gold_data));
            print(node.identifier_list);
            os << "' of subtype '";
            print(node.subtype_indication);
            os << "' with expr <";
            if (node.expression) {
                print(*node.expression);
            }
            os << ">\n";
        }
    }

    void operator()(ast::bit_string_literal const& node,
                    [[maybe_unused]] std::string_view /* node_name */) const
    {
        using namespace testsuite::vhdl::numeric_convert;

        BOOST_TEST_CONTEXT(">>> Test index at " << index << " <<<")
        {
            auto const expected = gold[index];
            BOOST_TEST(node.base_specifier == expected.base_specifier);
            auto const node_literal = std::string_view{ node.literal };
            BOOST_TEST(node_literal == expected.literal, btt::per_element());
            BOOST_TEST(std::format("{}", node) == expected.formatted, btt::per_element());
            auto result = 0;  // numeric convert
            BOOST_TEST(result == expected.result);
        }
        ++index;
    }

    // "catch them all" operator to be able to walk trough the AST organized by ast_walker
    template <typename NodeT>
    void operator()([[maybe_unused]] NodeT const& /* ast_node */,
                    [[maybe_unused]] std::string_view /* node_name */) const
    {
    }

private:
    std::reference_wrapper<GoldDataT> gold;
    std::size_t mutable index = 0;
    std::ostream& os;  // NOLINT(cppcoreguidelines-avoid-const-or-ref-data-members)
};

using verifier_type = ast::basic_ast_walker<test_worker<decltype(gold_data), false /* verbose */>>;

auto const verify = [](ast::design_file const& ast) {
    verifier_type verify(gold_data);
    verify(ast);
};

}  // namespace valid_data

// clang-format off
BOOST_AUTO_TEST_CASE(bit_string_literal__valid_test,    // test shall pass
                     *utf::label("bit_string_literal")
                     *utf::label("numeric"))
// clang-format on
{
    using ast::design_file;
    using testsuite::testsuite_parse;
    using namespace valid_data;

    testsuite_parse parse("<bit_string_literal>");
    ast::design_file ast;

    BOOST_TEST(parse(input, ast) == true);

    verify(ast);
}

using namespace ibis::vhdl;
using ast::numeric_convert;

// -------------------------------------------------------------------------------------------------

//******************************************************************************
// bit_string_literal
//******************************************************************************
using namespace testsuite::vhdl::numeric_convert;

std::vector<std::string> const bit_literal{
    // binary
    R"(B"00_00")",
    R"(B"00_01")",
    R"(B"1_0000")",
    R"(B"1_00_01")",
    R"(B"00_1_00_01")",  // leading zeros
    bsl_gen::bin(detail::uint32_max),
    bsl_gen::bin(detail::uint64_max),
    // octal
    R"(O"00_00")",
    R"(O"00_01")",
    R"(O"1_7654")",
    R"(O"7_6543210")",
    R"(O"000_7_6543210")",  // leading zeros
    bsl_gen::oct(detail::uint32_max),
    bsl_gen::oct(detail::uint64_max),
    // hexadecimal
    R"(X"00_00")",
    R"(X"00_01")",
    R"(X"1_AFFE")",
    R"(X"C001_CAFE")",
    R"(X"0000_C001_CAFE")",  // leading zeros
    bsl_gen::hex(detail::uint32_max),
    bsl_gen::hex(detail::uint64_max),
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

    parser::position_cache<iterator_type> position_cache{};
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
    bsl_gen::bin(detail::uint64_max, "_0"),
    bsl_gen::oct(detail::uint64_max, "_0"),
    bsl_gen::hex(detail::uint64_max, "_0"),
};

// NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
BOOST_DATA_TEST_CASE(bit_string_literal_uint64_ovflw, utf_data::make(literal_ovflw), literal)
{
    using iterator_type = parser::iterator_type;

    ibis::util::file_mapper file_mapper{};
    auto const file_id = file_mapper.add_file("<bit_string_literal>", literal);

    parser::position_cache<iterator_type> position_cache{};
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
