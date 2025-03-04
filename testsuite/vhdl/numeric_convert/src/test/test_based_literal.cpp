//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-or-later
//

#include <ibis/vhdl/ast/numeric_convert/convert_based.hpp>

#include <ibis/vhdl/ast/basic_ast_walker.hpp>
#include <ibis/vhdl/ast/ast_printer.hpp>
#include <ibis/vhdl/ast/ast_formatter.hpp>
#include <ibis/vhdl/diagnostic_handler.hpp>
#include <ibis/vhdl/context.hpp>
#include <ibis/vhdl/type.hpp>
#include <ibis/util/overloaded.hpp>

#include <ibis/vhdl/parser/parse.hpp>
#include <ibis/vhdl/ast/nodes.hpp>

#include <testsuite/testsuite_parser.hpp>
#include <testsuite/namespace_alias.hpp>  // IWYU pragma: keep

#include <boost/test/unit_test.hpp>  // IWYU pragma: keep
#include <boost/test/unit_test_log.hpp>
#include <boost/test/tools/output_test_stream.hpp>
#include <boost/test/tree/decorator.hpp>

#include <array>
#include <cstdint>
#include <format>
#include <iostream>
#include <string_view>
#include <type_traits>
#include <utility>
#include <variant>

namespace testsuite_data {

// clang-format off
std::string_view const input = R"(
PACKAGE integer_based_literal IS
    -- Examples from IEEE_VHDL_1076-1993: Chapter 13.4.2 Based literals
    CONSTANT int_01 : INTEGER := 2#1111_1111#;      -- value 255
    CONSTANT int_02 : INTEGER := 16#FF#;            -- value 255
    CONSTANT int_03 : INTEGER := 016#0_FF#;         -- value 255
    CONSTANT int_04 : INTEGER := 16#E#E1;           -- value 224, hex2dec('E') * 16^1
    CONSTANT int_05 : INTEGER := 2#1110_0000#;      -- value 224
END PACKAGE;

PACKAGE real_based_literal IS
    -- Examples from IEEE_VHDL_1076-1993: Chapter 13.4.2 Based literals
    -- result = ( ...
    --    hex2dec('F')*base^0  ...
    -- + ( ...
    --      hex2dec('F')/base^1 ...
    --    + hex2dec('F')/base^2 ...
    --    ) ...
    -- ) * 16^2
    CONSTANT real_01 : REAL := 16#F.FF#E+2;         -- value 4095.0
    CONSTANT real_02 : REAL := 2#1.1111_1111_111#E11; -- value 4095.0
    -- other self-choosen
    -- FixMe Shouldn't this a syntax error? INT vs. floating point value?
    CONSTANT int_06 : INTEGER := 10#0.0#;           -- value 0
    CONSTANT int_07 : INTEGER := 10#1.0#;           -- value 1
    CONSTANT int_08 : INTEGER := 10#42.666#e-1;     -- value 4.2666
END PACKAGE;
)";
// clang-format on

#if 0  // ToDo
PACKAGE based_literal_failure IS
    CONSTANT invalid_01 : INTEGER := 2#012#;            -- invalid char(s)
    CONSTANT invalid_02 : INTEGER := 8#12345678#;       -- invalid char(s)
    CONSTANT invalid_03 : INTEGER := 10#1234567890A#;   -- invalid char(s)
    -- FixMe:
    -- below the vhdl grammar! catches invalid chars, hence the error
    -- message (expecting semicolon ';') is inconsistent to the other ones
    -- further, parsing package_body failed and iterators are restored
    -- so that only this error is shown
    -- CONSTANT invalid_04 : INTEGER := 16#0ABCDEFG#;
    CONSTANT invalid_05 : INTEGER := 3#1#;              -- parse ok, but unsupported base
END PACKAGE;

PACKAGE based_literal_overflow IS
    -- overflows 64bit-integer
    CONSTANT oflow_01 : INTEGER := 2#1111111111111111111111111111111111111111111111111111111111111111_0#;
    CONSTANT oflow_02 : INTEGER := 8#1777777777777777777777_0#;
    CONSTANT oflow_03 : INTEGER := 10#18446744073709551615_0#;
    CONSTANT oflow_04 : INTEGER := 16#ffffffffffffffff_0#;
END PACKAGE;
#endif

using namespace ibis::vhdl;

using numeric_type_specifier = ast::based_literal::numeric_type_specifier;

auto constexpr based_integer = numeric_type_specifier::integer;
auto constexpr based_real = numeric_type_specifier::real;

using integer_type = ibis::vhdl::intrinsic::unsigned_integer_type;
using real_type = ibis::vhdl::intrinsic::real_type;

struct gold_data_type {
    numeric_type_specifier numeric_type;
    std::variant<integer_type, real_type> value;
    struct {
        unsigned base;
        std::string_view integer;
        std::string_view fractional;
        std::string_view exponent;
    } literal;
};

constexpr auto gold_data = std::to_array<gold_data_type>({
    // Examples from IEEE_VHDL_1076-1993: Chapter 13.4.2 Based literals
    { .numeric_type = based_integer,
      .value = 255U,
      .literal = { .base = 2, .integer = "1111_1111", .fractional = "", .exponent = "" } },
    { .numeric_type = based_integer,
      .value = 255U,
      .literal = { .base = 16, .integer = "FF", .fractional = "", .exponent = "" } },
    { .numeric_type = based_integer,
      .value = 255U,
      .literal = { .base = 16, .integer = "0_FF", .fractional = "", .exponent = "" } },
    { .numeric_type = based_integer,
      .value = 224U,
      .literal = { .base = 16, .integer = "E", .fractional = "", .exponent = "1" } },
    { .numeric_type = based_integer,
      .value = 224U,
      .literal = { .base = 2, .integer = "1110_0000", .fractional = "", .exponent = "" } },
    { .numeric_type = based_real,
      .value = 4095.0,
      .literal = { .base = 16, .integer = "F", .fractional = "FF", .exponent = "+2" } },
    { .numeric_type = based_real,
      .value = 4095.0,
      .literal = { .base = 2, .integer = "1", .fractional = "1111_1111_111", .exponent = "11" } },
    // self-choosen
    { .numeric_type = based_real,
      .value = 0.0,
      .literal = { .base = 10, .integer = "0", .fractional = "0", .exponent = "" } },
    { .numeric_type = based_real,
      .value = 1.0,
      .literal = { .base = 10, .integer = "1", .fractional = "0", .exponent = "" } },
    { .numeric_type = based_real,
      .value = 4.2666,
      .literal = { .base = 10, .integer = "42", .fractional = "666", .exponent = "-1" } },
});

// clang-format off
auto const expected_os = R"(
In 'based_literal':29:40: parse error: in based literal parse of integer part '012' failed
  29|     CONSTANT invalid_01 : INTEGER := 2#012#;            -- invalid char(s)
    |                                        ~~~ <<-- here
In 'based_literal':30:40: parse error: in based literal parse of integer part '12345678' failed
  30|     CONSTANT invalid_02 : INTEGER := 8#12345678#;       -- invalid char(s)
    |                                        ~~~~~~~~ <<-- here
In 'based_literal':31:41: parse error: in based literal parse of integer part '1234567890A' failed
  31|     CONSTANT invalid_03 : INTEGER := 10#1234567890A#;   -- invalid char(s)
    |                                         ~~~~~~~~~~~ <<-- here
In 'based_literal':38:38: unsupported: in based literal the base specifier '3' isn't supported; only 2, 8, 10 and 16!
  38|     CONSTANT invalid_05 : INTEGER := 3#1#;              -- parse ok, but unsupported base
    |                                      ~ <<-- here
In 'based_literal':43:38: parse error: in based literal integer part '1111111111111111111111111111111111111111111111111111111111111111_0' can't fit the numeric type
  43|     CONSTANT oflow_01 : INTEGER := 2#1111111111111111111111111111111111111111111111111111111111111111_0#;
    |                                      ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ <<-- here
In 'based_literal':44:38: parse error: in based literal integer part '1777777777777777777777_0' can't fit the numeric type
  44|     CONSTANT oflow_02 : INTEGER := 8#1777777777777777777777_0#;
    |                                      ~~~~~~~~~~~~~~~~~~~~~~~~ <<-- here
In 'based_literal':45:39: parse error: in based literal integer part '18446744073709551615_0' can't fit the numeric type
  45|     CONSTANT oflow_03 : INTEGER := 10#18446744073709551615_0#;
    |                                       ~~~~~~~~~~~~~~~~~~~~~~ <<-- here
In 'based_literal':46:39: parse error: in based literal parse of integer part 'ffffffffffffffff_0' failed
  46|     CONSTANT oflow_04 : INTEGER := 16#ffffffffffffffff_0#;
    |                                       ~~~~~~~~~~~~~~~~~~ <<-- here
8 errors generated.
)";
// clang-format on

template <typename GoldDataT, bool verbose = false>
class verify_worker {
    using converter_type = ast::convert_based<integer_type, real_type>;

    std::ostream& os;  // NOLINT(cppcoreguidelines-avoid-const-or-ref-data-members)
    std::reference_wrapper<GoldDataT const> ref_gold_data;
    std::size_t mutable test_index = 0;
    converter_type convert_based;

public:
    using diagnostic_handler_type = ibis::vhdl::diagnostic_handler<parser::iterator_type>;

    verify_worker(std::ostream& os_, GoldDataT const& gold_data_,
                  diagnostic_handler_type& diagnostic_handler)
        : os{ os_ }
        , ref_gold_data{ std::ref(gold_data_) }
        , convert_based{ diagnostic_handler }
    {
        // work around to allow easy write of expected gold data
        os << '\n';
    }

    void operator()(ast::constant_declaration const& node,
                    [[maybe_unused]] std::string_view /*unused*/) const
    {
        if constexpr (verbose) {
            assert(node.identifier_list.size() == 1UZ &&
                   "expected single ast::identifier in identifier_list");
            auto const identifier = node.identifier_list.front();
            os << std::format("verify {:2d}: identifier '{}'\n", test_index, identifier.name);
        }
    }

    void operator()(ast::based_literal const& node,
                    [[maybe_unused]] std::string_view /*unused*/) const
    {
        assert(test_index < ref_gold_data.get().size());

        // check on conversion
        auto const [conv_ok, result] = convert_based(node);

        // success tests
        BOOST_TEST_MESSAGE("verify 'based_literal' success test with test_index = " << test_index);
        // check on parser
        auto const& expected = ref_gold_data.get()[test_index];
        BOOST_TEST(node.number.type_specifier == expected.numeric_type);
        BOOST_TEST(node.base_id == expected.literal.base);
        BOOST_TEST(node.number.integer_part == expected.literal.integer);
        BOOST_TEST(node.number.fractional_part == expected.literal.fractional);
        BOOST_TEST(node.number.exponent == expected.literal.exponent);

        BOOST_CHECK(conv_ok);

        using ibis::util::overloaded;
        std::visit(
            overloaded{
                [&](integer_type value) {
                    // check on same type of converted and expected
                    if (std::holds_alternative<integer_type>(expected.value)) {
                        auto const value_expected = std::get<integer_type>(expected.value);
                        BOOST_TEST(value == value_expected);
                    }
                    else {
                        BOOST_TEST_INFO("convert_based's result isn't of expected type 'integer'");
                        BOOST_TEST(false);
                    }
                },
                [&](real_type value) {
                    // check on same type of converted and expected
                    if (std::holds_alternative<real_type>(expected.value)) {
                        auto const value_expected = std::get<real_type>(expected.value);
                        // https://www.boost.org/doc/libs/1_87_0/libs/test/doc/html/boost_test/testing_tools/extended_comparison/floating_point.html
                        auto const tolerance =
                            btt::tolerance(std::numeric_limits<real_type>::epsilon());
                        BOOST_TEST(value == value_expected, tolerance);
                    }
                    else {
                        BOOST_TEST_INFO("convert_based's result isn't of expected type 'real'");
                        BOOST_TEST(false);
                    }
                } },
            result);

        ++test_index;
    }

    template <typename NodeT>
    void operator()([[maybe_unused]] NodeT const& /*unused*/,
                    [[maybe_unused]] std::string_view /*unused*/) const
    {
    }
};

using verifier_type =
    ast::basic_ast_walker<verify_worker<decltype(gold_data), false /* verbose */>>;

}  // namespace testsuite_data

namespace utf = boost::unit_test;

using namespace ibis;

BOOST_AUTO_TEST_CASE(based_literal)
{
    // using testsuite::testsuite_parse;
    using iterator_type = vhdl::parser::iterator_type;
    using file_mapper_type = util::file_mapper;
    using position_cache_type = vhdl::parser::position_cache<iterator_type>;
    using vhdl_context_type = vhdl::vhdl_global_context;
    using diagnostic_handler_type = vhdl::diagnostic_handler<iterator_type>;

    using vhdl::ast::design_file;

    using namespace testsuite_data;

    file_mapper_type file_mapper;
    position_cache_type position_cache;

    auto current_file = file_mapper.add_file("<based_literal>", input);

    ast::ast_context<iterator_type> ast_context{ current_file, position_cache };

    // auto& os = std::cout;
    btt::output_test_stream os;
    vhdl_context_type vhdl_ctx;
    ast::design_file ast;

    // parse
    parser::parse<iterator_type> parse{ os };
    bool parse_ok = parse(current_file, position_cache, vhdl_ctx, ast);
    BOOST_TEST(parse_ok);

    // convert and check results
    diagnostic_handler_type diagnostic_handler{ os, ast_context, vhdl_ctx };
    verifier_type verify(os, gold_data, diagnostic_handler);
    verify(ast);

    os << vhdl_ctx.get_failure_status() << '\n';

    std::cout << os.str() << '\n';
    // BOOST_TEST(os.str() == expected_os);
}
