//
// Copyright (c) 2017-2025 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-or-later
//

#include <ibis/vhdl/ast/ast_formatter.hpp>
#include <ibis/vhdl/ast/node/string_literal.hpp>

// #include <boost/test/unit_test.hpp>
#include <boost/test/tools/interface.hpp>  // BOOST_TEST()
#include <boost/test/tools/context.hpp>    // BOOST_TEST_CONTEXT()
#include <boost/test/unit_test_suite.hpp>  // BOOST_AUTO_TEST_CASE()
#include <boost/test/tree/decorator.hpp>   // utf::label
#include <boost/test/tools/output_test_stream.hpp>

#include <format>
#include <string_view>

#include <testsuite/namespace_alias.hpp>

// NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
BOOST_AUTO_TEST_SUITE(ast_formatter)

using namespace ibis::vhdl;
using namespace ibis::vhdl::ast;

//
// Check on correct printing of quoted string literals
//
namespace valid_data {

// NOLINTNEXTLINE(cppcoreguidelines-avoid-c-arrays,modernize-avoid-c-arrays)
struct {
    std::string_view input;
    std::string_view expected;
} constexpr gold_data[] = {  // --
    { .input = R"("""")", .expected = R"("")" },
    { .input = R"(%%%%)", .expected = R"(%%)" },
    { .input = R"(""Hello"")", .expected = R"("Hello")" },
    { .input = R"(Quotation: ""REPORT..."")", .expected = R"(Quotation: "REPORT...")" },
    { .input = R"("%"%")", .expected = R"("%"%")" },  // as-is
    { .input = R"(%"%"")", .expected = R"(%"%")" },
    { .input = R"(""")", .expected = R"("")" }
};

// make ast::string_literal from string_view input
auto const make_string_literal_from = [](std::string_view sv) {
    ast::string_literal str_lit;
    str_lit.literal = boost::make_iterator_range(sv);
    return str_lit;
};

}  // namespace valid_data

// clang-format off
BOOST_AUTO_TEST_CASE(string_literal_formatter,  // test shall pass
                     *utf::label("string_literal")
                     *utf::label("formatter"))
// clang-format on
{
    using namespace valid_data;

    btt::output_test_stream output;  // reused, flushed/cleared after each test

    for (auto index{ 0U }; auto const& [literal, expected] : valid_data::gold_data) {
        ast::string_literal const string_literal{ make_string_literal_from(literal) };

        BOOST_TEST_CONTEXT(">>> Test index at " << index << " <<<")
        {
            output << std::format("{}", string_literal);
            BOOST_REQUIRE(!output.str().empty());
            BOOST_TEST(output.str() == expected, btt::per_element());
        }
        output.flush();  // clear output for next run
        ++index;
    }
}

// clang-format off
BOOST_AUTO_TEST_CASE(string_literal_raw_formatter,  // test shall pass
                     *utf::label("string_literal")
                     *utf::label("formatter"))
// clang-format on
{
    using namespace valid_data;

    btt::output_test_stream output;  // reused, flushed/cleared after each test

    for (auto index{ 0U }; auto const& [raw_literal, expected] : valid_data::gold_data) {
        ast::string_literal const string_literal{ make_string_literal_from(raw_literal) };

        BOOST_TEST_CONTEXT(">>> Test index at " << index << " <<<")
        {
            output << std::format("{:raw}", string_literal);
            BOOST_REQUIRE(!output.str().empty());
            BOOST_TEST(output.str() == raw_literal, btt::per_element());
        }
        output.flush();  // clear output for next run
        ++index;
    }
}

/// Note: Here is stated, that formatter testing of
/// ast::{bit_string, decimal, based}_literal
/// etc. is too simple for testing, but preparing the tests is a big
/// effort. Implicit they are checked by parser and other tests.

// NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
BOOST_AUTO_TEST_SUITE_END()