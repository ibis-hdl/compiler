//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-only
//

#include <testsuite/vhdl/grammar/testsuite_parse.hpp>
#include <testsuite/vhdl/grammar/failure_diagnostic_fixture.hpp>
#include <testsuite/vhdl/grammar/dataset.hpp>

#include <testsuite/namespace_alias.hpp>  // IWYU pragma: keep

#include <boost/test/unit_test.hpp>  // IWYU pragma: keep
#include <boost/test/data/test_case.hpp>

#include <iostream>

using testsuite::failure_diagnostic_fixture;
using boost::unit_test::framework::current_test_case;

// NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
BOOST_FIXTURE_TEST_SUITE(grammar_rules_1, failure_diagnostic_fixture)

// NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
BOOST_DATA_TEST_CASE(
    design_file_1,                                                   // --
    utf_data::make_delayed<testsuite::dataset>("abstract_literal"),  // --
    input, expected, test_case_name)
{
    using testsuite::testsuite_parse;
    using vhdl::ast::design_file;

    ast::design_file ast;
    testsuite_parse parse(current_test_case().p_name.get());

    auto const parse_ok = parse(input, ast);

    BOOST_TEST(parse_ok);
    if (!current_test_passing()) {
        //failure_closure(test_case_name, input, parse_result);
        return;
    }

    //BOOST_TEST(parse_result == expected, btt::per_element());
    //failure_closure(test_case_name, input, expected, parse_result);
}

// NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
BOOST_AUTO_TEST_SUITE_END()
