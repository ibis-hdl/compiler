//
// @file alias_declaration_test.cpp
//
// Generated by <gen_parsertest_files.py> on: 7.5.2021, do not edit!
//

#include <ibis/vhdl/ast/node/alias_declaration.hpp>

#include <testsuite/vhdl/rules.hpp>
#include <testsuite/vhdl/parser/testing_parser.hpp>
#include <testsuite/vhdl/parser/failure_diagnostic_fixture.hpp>
#include <testsuite/vhdl/parser/dataset.hpp>

#include <testsuite/namespace_alias.hpp>  // IWYU pragma: keep

#include <boost/test/unit_test.hpp>  // IWYU pragma: keep
#include <boost/test/data/test_case.hpp>

#include <iostream>

using testsuite::vhdl::parser::failure_diagnostic_fixture;

// NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
BOOST_FIXTURE_TEST_SUITE(parser_rule, failure_diagnostic_fixture)

// NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
BOOST_DATA_TEST_CASE(alias_declaration, // --
    utf_data::make_delayed<testsuite::vhdl::parser::dataset>("alias_declaration"),  // --
    input, expected, test_case_name)
{
    using attribute_type = ast::alias_declaration;
    auto const parser = testsuite::vhdl::parser::alias_declaration();

    using testsuite::vhdl::parser::util::testing_parser;

    testing_parser<attribute_type> parse;
    auto [parse_ok, parse_result] = parse(input, parser, test_case_name);

    BOOST_TEST(parse_ok);
    if (!current_test_passing()) {
        failure_closure(test_case_name, input, parse_result);
        return;
    }

    BOOST_TEST(parse_result == expected, btt::per_element());
    failure_closure(test_case_name, input, expected, parse_result);
}

// NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
BOOST_AUTO_TEST_SUITE_END()
