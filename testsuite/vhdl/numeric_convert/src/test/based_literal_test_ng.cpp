//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-or-later
//

#include <ibis/vhdl/ast/numeric_convert/convert_based.hpp>

#include <ibis/vhdl/ast/basic_ast_walker.hpp>
#include <ibis/vhdl/ast/ast_printer.hpp>
#include <ibis/vhdl/parser/diagnostic_handler.hpp>
#include <ibis/vhdl/parser/context.hpp>
#include <ibis/vhdl/type.hpp>
#include <ibis/util/overloaded.hpp>

#include <ibis/vhdl/parser/context.hpp>
#include <ibis/vhdl/parser/parse.hpp>
#include <ibis/vhdl/ast.hpp>

#include <testsuite/namespace_alias.hpp>  // IWYU pragma: keep

#include <boost/test/unit_test.hpp>  // IWYU pragma: keep
#include <boost/test/tools/output_test_stream.hpp>
#include <boost/test/tree/decorator.hpp>

#include <fmt/format.h>

#include <iostream>
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
    CONSTANT int_05 : INTEGER := 10#0.0#;           -- value 0
    CONSTANT int_05 : INTEGER := 10#1.0#;           -- value 1
    CONSTANT int_05 : INTEGER := 10#42.666#e-1;     -- value 4.2666
END PACKAGE;

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
)";
// clang-format on

using numeric_type_specifier = ast::based_literal::numeric_type_specifier;
auto constexpr based_integer = numeric_type_specifier::integer;
auto constexpr based_real = numeric_type_specifier::real;

struct {
    numeric_type_specifier numeric_type;
    std::variant<uint64_t, double> value;
    struct {
        unsigned base;
        std::string_view integer;
        std::string_view fractional;
        std::string_view exponent;
    } literal;
} const expect[] = {
    // Examples from IEEE_VHDL_1076-1993: Chapter 13.4.2 Based literals
    { based_integer, 255U, { 2, "1111_1111", "", "" } },
    { based_integer, 255U, { 16, "FF", "", "" } },
    { based_integer, 255U, { 16, "0_FF", "", "" } },
    { based_integer, 224U, { 16, "E", "", "1" } },
    { based_integer, 224U, { 2, "1110_0000", "", "" } },
    { based_real, 4095.0, { 16, "F", "FF", "+2" } },
    { based_real, 4095.0, { 2, "1", "1111_1111_111", "11" } },
    // self-choosen
    { based_real, 0.0, { 10, "0", "0", "" } },
    { based_real, 1.0, { 10, "1", "0", "" } },
    { based_real, 4.2666, { 10, "42", "666", "-1" } },
};

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
// clang-format om

// FixMe: This API is insufficient (not easy to call); convert_based requires diagnostic_handler,
// which requires os, context, position_cache_proxy; maybe make them context bounded?
template<typename ExpectT, bool verbose = false>
struct verify_worker
{
    using diagnostic_handler_type = vhdl::diagnostic_handler<parser::iterator_type>;
    using basic_integer_type = vhdl::intrinsic::signed_integer_type;
    using integer_type = typename std::make_unsigned<basic_integer_type>::type;
    using real_type = vhdl::intrinsic::real_type;

    using converter_type = ast::convert_based<basic_integer_type, real_type>;

    verify_worker(std::ostream& os_, ExpectT const& expect_, diagnostic_handler_type& handler_)
    : os{ os_ }
    , expect{ expect_ }
    , max_index{ sizeof(expect_) / sizeof(expect_[0]) }
    , diagnostic_handler{ handler_ }
    , convert_based{ handler_ }
    {
        // work around to allow easy write of expected
        os << '\n';
    }

    void operator()(ast::constant_declaration const& node, [[maybe_unused]] std::string_view) const
    {
        if constexpr (verbose) {
            static ast::printer print(os);
            os << fmt::format("verify {0:2d}: identifier '", test_index);
            print(node.identifier_list);
            os << "'\n";
        }
    }

    void operator()(ast::based_literal const& node, [[maybe_unused]] std::string_view /*unused*/) const
    {
        // check on conversion
        auto const [conv_ok, result] = convert_based(node);

        if(test_index < max_index) {
            // success tests
            BOOST_TEST_MESSAGE("verify 'based_literal' success test with test_index = " << test_index);
            // check on parser
            BOOST_TEST(node.number.type_specifier == expect[test_index].numeric_type);
            BOOST_TEST(node.base == expect[test_index].literal.base);
            BOOST_TEST(node.number.integer_part == expect[test_index].literal.integer);
            BOOST_TEST(node.number.fractional_part == expect[test_index].literal.fractional);
            BOOST_TEST(node.number.exponent == expect[test_index].literal.exponent);

            BOOST_CHECK(conv_ok);

            using ibis::util::overloaded;
            std::visit(overloaded {
                [&](std::uint64_t value) {
                    // check on same type of converted and expected
                    if(std::holds_alternative<std::uint64_t>(expect[test_index].value)) {
                        auto const value_expected = std::get<std::uint64_t>(expect[test_index].value);
                        BOOST_TEST(value == value_expected);
                    }
                    else {
                        BOOST_TEST_INFO("convert_based's result isn't of expected type 'integer'");
                        BOOST_TEST(false);
                    }
                },
                [&](double value) {
                    // check on same type of converted and expected
                    if(std::holds_alternative<double>(expect[test_index].value)) {
                        auto const value_expected = std::get<double>(expect[test_index].value);
                        // https://www.boost.org/doc/libs/1_77_0/libs/test/doc/html/boost_test/testing_tools/extended_comparison/floating_point.html
                        auto const tolerance = btt::tolerance(std::numeric_limits<double>::epsilon());
                        BOOST_TEST(value == value_expected, tolerance);
                    }
                    else {
                        BOOST_TEST_INFO("convert_based's result isn't of expected type 'real'");
                        BOOST_TEST(false);
                    }
                }
            }, result);

            ++test_index;
        }
        else {
            // failure test; just gather output from reporting errors
            BOOST_TEST_MESSAGE("verify 'based_literal' failure test");
            BOOST_CHECK(!conv_ok);
        }
    }

    template <typename NodeT>
    void operator()([[maybe_unused]] NodeT const& /*unused*/, [[maybe_unused]] std::string_view /*unused*/) const
    { }

private:
    std::ostream& os;
    ExpectT const& expect;
    std::size_t const max_index;
    std::size_t mutable test_index = 0;
    diagnostic_handler_type& diagnostic_handler;
    converter_type convert_based;
};

using verifier_type = ast::basic_ast_walker<verify_worker<decltype(expect), false>>;

} // namespace testsuite_data

namespace utf = boost::unit_test;

BOOST_AUTO_TEST_CASE(based_literal_ng)
{
    //using testsuite::testsuite_parse;
    using diagnostic_handler_type = ibis::vhdl::diagnostic_handler<parser::iterator_type>;
    using vhdl::ast::design_file;
    using namespace testsuite_data;

    parser::position_cache<parser::iterator_type> position_cache;
    auto position_cache_proxy = position_cache.add_file("based_literal", input);

    //auto& os = std::cout;
    btt::output_test_stream os;
    parser::context ctx;
    ast::design_file ast;

    // parse
    parser::parse parse{ os };
    bool parse_ok = parse(position_cache_proxy, ctx, ast);
    BOOST_TEST(parse_ok);

    // convert
    diagnostic_handler_type diagnostic_handler{ os, ctx, position_cache_proxy };
    verifier_type verify(os, expect, diagnostic_handler);
    verify(ast);

    using ibis::vhdl::failure_status;
    os << failure_status(ctx) << '\n';

    //std::cout << os.str() << '\n';
    BOOST_TEST(os.str() == expected_os);
}
