/*
 * package_body_test.cpp
 *
 *  Created on: 20.8.2018
 *      Author: olaf
 */


#include <boost/test/unit_test.hpp>
#include <boost/core/ignore_unused.hpp>

#include <iostream>

#include <eda/vhdl/ast.hpp>

#include <testsuite/vhdl_parser/rules.hpp>
#include <testsuite/vhdl_parser/testing_parser.hpp>
#include <testsuite/vhdl_parser/testing_parser_grammar_hack.hpp>

#include <testsuite/data_set.hpp>
#include <testsuite/failure_diagnostic_fixture.hpp>

#include <testsuite/namespace_alias.hpp>


BOOST_AUTO_TEST_SUITE( parser_rule )


BOOST_DATA_TEST_CASE_F( testsuite::failure_diagnostic_fixture,
    package_body,
    utf_data::make_delayed<testsuite::dataset_loader>( "test_case/package_body" ),
    input, expected, test_case_name)
{
    using attribute_type = ast::package_body; 
    auto const& parser = testsuite::vhdl_parser::package_body();

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


BOOST_AUTO_TEST_SUITE_END()

