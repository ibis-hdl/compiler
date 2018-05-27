/*
 * file_open_information_parsertest.cpp
 *
 *  Created on: 27.5.2018
 *      Author: olaf
 */


#include <boost/test/unit_test.hpp>
#include <boost/core/ignore_unused.hpp>

#include <iostream>

#include <eda/vhdl/ast.hpp>

#include <testsuite/vhdl_parser/data_set.hpp>
#include <testsuite/vhdl_parser/testing_parser_def.hpp>
#include <testsuite/vhdl_parser/testing_parser_grammar_hack.hpp>
#include <testsuite/vhdl_parser/generate_data_test_case.hpp>
#include <testsuite/vhdl_parser/testing_util.hpp>


BOOST_AUTO_TEST_SUITE( parser )


namespace btt    = boost::test_tools;
namespace parser = eda::vhdl::parser;
namespace ast    = eda::vhdl::ast;



struct file_open_information_dataset : public ::x3_test::dataset_loader
{
    file_open_information_dataset()
    : dataset_loader{ "test_case/file_open_information" }
    { }
} const file_open_information_dataset;




BOOST_DATA_TEST_CASE( file_open_information,
      file_open_information_dataset.input()
    ^ file_open_information_dataset.expect()
    ^ file_open_information_dataset.test_case_name(),
    input, expected, test_case_name)
{
    using attribute_type = ast::file_open_information;
    auto const parser = parser::file_open_information;

    boost::ignore_unused(test_case_name);

    x3_test::testing_parser<attribute_type> parse;
    auto [parse_ok, parse_result] = parse(input, parser);

    BOOST_TEST(parse_ok);
    BOOST_REQUIRE_MESSAGE(parse_ok,
        x3_test::report_diagnostic(test_case_name, input, parse_result)
    );

    BOOST_TEST(parse_result == expected, btt::per_element());
    BOOST_REQUIRE_MESSAGE(x3_test::current_test_passing(),
        x3_test::report_diagnostic(test_case_name, input, parse_result)
    );
}


BOOST_AUTO_TEST_SUITE_END()

