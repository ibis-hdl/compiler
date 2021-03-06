//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-or-later
//

#include <ibis/vhdl/ast/literal_printer.hpp>

#include <boost/test/unit_test.hpp>
#include <boost/test/data/test_case.hpp>
#include <boost/test/data/monomorphic.hpp>
#include <boost/test/tools/output_test_stream.hpp>

#include <testsuite/namespace_alias.hpp>

// NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
BOOST_AUTO_TEST_SUITE(literal_print)

using namespace ibis::vhdl::ast;

//
// Check on correct printing of quoted string literals
//
// clang-format off
std::vector<std::string_view> const input_string_literal{
    R"("""")",  R"(%%%%)", 
    R"(""Hello"")", R"(Quotation: ""REPORT..."")",
    R"("%"%")",
    R"(%"%"")",
    R"(""")"
};
// clang-format on

// clang-format off
std::vector<std::string> const expected_string_literal{
    R"("")",      R"(%%)",
    R"("Hello")", R"(Quotation: "REPORT...")",
    R"("%"%")",  // as-is
    R"(%"%")",
    R"("")"
};
// clang-format on

// NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
BOOST_DATA_TEST_CASE(                                                // --
    string_literal,                                                  // --
    utf_data::make(input_string_literal) ^ expected_string_literal,  // --
    input, expected)
{
    auto const as_strlit = [](std::string_view sv) {
        ast::string_literal strlit;
        strlit.literal = boost::make_iterator_range(sv);
        return strlit;
    };

    using ibis::vhdl::ast::literal_printer;

    btt::output_test_stream os;

    literal_printer literal{ as_strlit(input) };
    os << literal;

    BOOST_TEST(os.str() == expected, btt::per_element());
}

/// Note: Here is stated, that testing of
/// ast::{bit_string, decimal, based}_literal
/// etc. is too simple for testing, but preparing the tests is a big
/// effort. Implicit they are checked by parser tests.

// NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
BOOST_AUTO_TEST_SUITE_END()
