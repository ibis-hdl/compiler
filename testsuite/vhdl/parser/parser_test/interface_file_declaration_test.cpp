/*
 * interface_file_declaration_test.cpp
 *
 *  Created on: 11.6.2018
 *      Author: olaf
 */


#include <boost/test/unit_test.hpp>
#include <boost/core/ignore_unused.hpp>

#include <iostream>

#include <eda/vhdl/ast.hpp>

#include <testsuite/vhdl_parser/data_set.hpp>
#include <testsuite/vhdl_parser/testing_parser.hpp>
#include <testsuite/vhdl_parser/testing_parser_grammar_hack.hpp>
#include <testsuite/vhdl_parser/generate_data_test_case.hpp>
#include <testsuite/vhdl_parser/testing_util.hpp>


BOOST_AUTO_TEST_SUITE( parser )


namespace btt    = boost::test_tools;
namespace parser = eda::vhdl::parser;
namespace ast    = eda::vhdl::ast;



struct interface_file_declaration_dataset : public testsuite::vhdl_parser::util::dataset_loader
{
    interface_file_declaration_dataset()
    : dataset_loader{ "test_case/interface_file_declaration" }
    { }
} const interface_file_declaration_dataset;




BOOST_DATA_TEST_CASE( interface_file_declaration,
      interface_file_declaration_dataset.input()
    ^ interface_file_declaration_dataset.expect()
    ^ interface_file_declaration_dataset.test_case_name(),
    input, expected, test_case_name)
{
    using attribute_type = ast::interface_file_declaration;
    auto const parser = parser::interface_file_declaration;

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

