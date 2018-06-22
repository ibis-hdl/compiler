/*
 * group_declaration_test.cpp
 *
 *  Created on: 22.6.2018
 *      Author: olaf
 */


#include <boost/test/unit_test.hpp>
#include <boost/core/ignore_unused.hpp>

#include <iostream>

#include <eda/vhdl/ast.hpp>

#include <testsuite/data_set.hpp>
#include <testsuite/vhdl_parser/rules.hpp>
#include <testsuite/vhdl_parser/testing_parser.hpp>
#include <testsuite/vhdl_parser/generate_data_test_case.hpp>
#include <testsuite/vhdl_parser/testing_util.hpp>
#include <testsuite/vhdl_parser/testing_parser_grammar_hack.hpp>


BOOST_AUTO_TEST_SUITE( parser )


namespace btt    = boost::test_tools;
namespace parser = eda::vhdl::parser;
namespace ast    = eda::vhdl::ast;



struct group_declaration_dataset : public testsuite::dataset_loader
{
    group_declaration_dataset()
    : dataset_loader{ "test_case/group_declaration",
                      // hack for boost.test argc/argv problem
                      "../vhdl/parser",
                      ".input" }
    { }
} const group_declaration_dataset;




BOOST_DATA_TEST_CASE( group_declaration,
      group_declaration_dataset.input()
    ^ group_declaration_dataset.expect()
    ^ group_declaration_dataset.test_case_name(),
    input, expected, test_case_name)
{
    using attribute_type = ast::group_declaration; 
    auto const& parser = testsuite::vhdl_parser::group_declaration();

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

