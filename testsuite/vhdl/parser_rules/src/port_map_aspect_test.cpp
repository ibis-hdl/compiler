/*
 * port_map_aspect_test.cpp
 *
 *  Created on: 26.6.2018
 *      Author: olaf
 */


#include <boost/test/unit_test.hpp>
#include <boost/core/ignore_unused.hpp>

#include <iostream>

#include <eda/vhdl/ast.hpp>

#include <testsuite/data_set.hpp>
#include <testsuite/vhdl_parser/rules.hpp>
#include <testsuite/vhdl_parser/testing_parser.hpp>
#include <testsuite/vhdl_parser/testing_util.hpp>
#include <testsuite/vhdl_parser/testing_parser_grammar_hack.hpp>
#include <testsuite/namespace_alias.hpp>


BOOST_AUTO_TEST_SUITE( parser_rule )


struct port_map_aspect_dataset : public testsuite::dataset_loader
{
    port_map_aspect_dataset()
    : dataset_loader{ "test_case/port_map_aspect",
                      // hack for boost.test argc/argv problem
                      "../vhdl/parser_rules",
                      ".input" }
    { }
} const port_map_aspect_dataset;



BOOST_DATA_TEST_CASE( port_map_aspect,
      port_map_aspect_dataset.input()
    ^ port_map_aspect_dataset.expect()
    ^ port_map_aspect_dataset.test_case_name(),
    input, expected, test_case_name)
{
    using attribute_type = ast::port_map_aspect; 
    auto const& parser = testsuite::vhdl_parser::port_map_aspect();

    using testsuite::vhdl_parser::util::testing_parser;
    using testsuite::vhdl_parser::util::current_test_passing;
    using testsuite::vhdl_parser::util::report_diagnostic;

    testing_parser<attribute_type> parse;
    auto [parse_ok, parse_result] = parse(input, parser, test_case_name);

    BOOST_TEST(parse_ok);
    BOOST_REQUIRE_MESSAGE(parse_ok,
        report_diagnostic(test_case_name, input, parse_result)
    );

    BOOST_TEST(parse_result == expected, btt::per_element());
    BOOST_REQUIRE_MESSAGE(current_test_passing(),
        report_diagnostic(test_case_name, input, parse_result)
    );
}


BOOST_AUTO_TEST_SUITE_END()

