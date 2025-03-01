//
// Copyright (c) 2017-2025 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-or-later
//

//
// @file discrete_range_test.cpp
//
// Generated by <gen_parsertest_files.py> on: 4.2.2025, do not edit!
//

#include <ibis/vhdl/ast/node/discrete_range.hpp>

#include <testsuite/vhdl/rules.hpp>
#include <testsuite/vhdl/parser/testing_parser.hpp>
#include <testsuite/vhdl/parser/failure_diagnostic_fixture.hpp>
#include <testsuite/vhdl/parser/dataset.hpp>

#include <testsuite/namespace_alias.hpp>  // IWYU pragma: keep

#include <boost/test/unit_test.hpp>  // IWYU pragma: keep
#include <boost/test/unit_test_suite.hpp>
#include <boost/test/data/test_case.hpp>
#include <boost/test/data/monomorphic/delayed.hpp>
#include <boost/test/tools/interface.hpp>  // BOOST_TEST()



using testsuite::vhdl::parser::failure_diagnostic_fixture;

// NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
BOOST_FIXTURE_TEST_SUITE(parser_rule, failure_diagnostic_fixture)

// NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
BOOST_DATA_TEST_CASE(discrete_range, // --
    utf_data::make_delayed<testsuite::vhdl::parser::dataset>("discrete_range"),  // --
    input, expected, test_case_name)
{
    using namespace testsuite;
    using attribute_type = ast::discrete_range;
    auto parser = testsuite::vhdl::parser::discrete_range();

    using testsuite::vhdl::parser::util::testing_parser;
    using namespace ibis::vhdl;

    testing_parser<attribute_type> const parse;
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
