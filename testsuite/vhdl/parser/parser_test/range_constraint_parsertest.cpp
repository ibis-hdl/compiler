/*
 * range_constraint_parsertest.cpp
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



struct range_constraint_dataset : public ::x3_test::dataset_loader
{
    range_constraint_dataset()
    : dataset_loader{ "test_case/range_constraint" }
    { }
} const range_constraint_dataset;




BOOST_DATA_TEST_CASE( range_constraint,
      range_constraint_dataset.input()
    ^ range_constraint_dataset.expect()
    ^ range_constraint_dataset.test_case_name(),
    input, expected, test_case_name)
{
    using attribute_type = ast::range_constraint;
    auto const parser = parser::range_constraint;

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
