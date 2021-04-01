//
// generic_clause_test.cpp
//
// Generated by <gen_parsertest_files.py> on: 1.4.2021, do not edit!
//

#include <eda/vhdl/ast/node/generic_clause.hpp>

#include <testsuite/util/data_set.hpp>
#include <testsuite/namespace_alias.hpp>  // IWYU pragma: keep

#include <testsuite/vhdl/rules.hpp>
#include <testsuite/vhdl_parser/testing_parser.hpp>
#include <testsuite/vhdl_parser/failure_diagnostic_fixture.hpp>

#include <boost/test/unit_test.hpp>  // IWYU pragma: keep
#include <boost/test/data/test_case.hpp>

#include <iostream>

// NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
BOOST_AUTO_TEST_SUITE(parser_rule)

// NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
BOOST_DATA_TEST_CASE_F(  // --
    testsuite::vhdl_parser::util::failure_diagnostic_fixture, generic_clause,
    utf_data::make_delayed<testsuite::util::dataset_loader>("test_data/generic_clause"),  // --
    input, expected, test_case_name)
{
    using attribute_type = ast::generic_clause;
    auto const& parser = testsuite::vhdl_parser::generic_clause();

    using testsuite::vhdl_parser::util::testing_parser;

    testing_parser<attribute_type> parse;
    auto [parse_ok, parse_result] = parse(input, parser, test_case_name);

    BOOST_TEST(parse_ok);
    if (!current_test_passing()) {
        failure_closure(test_case_name, input, parse_result);
        return;
    }

    BOOST_TEST(parse_result == expected, btt::per_element());
    failure_closure(test_case_name, input, parse_result);
}

// NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
BOOST_AUTO_TEST_SUITE_END()
