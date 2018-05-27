/*
 * parser_expression.cpp
 *
 *  Created on: 02.04.2017
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


namespace x3 = boost::spirit::x3;
namespace btt = boost::test_tools;
namespace parser = eda::vhdl::parser;
namespace ast    = eda::vhdl::ast;


BOOST_AUTO_TEST_SUITE( parser_expression )


GENERATE_DATASET_TEST_CASE(aggregate)
GENERATE_DATASET_TEST_CASE(name)
GENERATE_DATASET_TEST_CASE(primary)
GENERATE_DATASET_TEST_CASE(factor)
GENERATE_DATASET_TEST_CASE(term)
GENERATE_DATASET_TEST_CASE(simple_expression)
GENERATE_DATASET_TEST_CASE(shift_expression)
GENERATE_DATASET_TEST_CASE(relation)
GENERATE_DATASET_TEST_CASE(expression)


/*
 * expression failure
 */
struct expression_failure_dataset : public ::x3_test::dataset_loader
{
    expression_failure_dataset()
    : dataset_loader{ "test_case/expression_failure" }
    { }
} const expression_failure_dataset;


BOOST_DATA_TEST_CASE( expression_failure,
      expression_failure_dataset.input()
    ^ expression_failure_dataset.expect()
    ^ expression_failure_dataset.test_case_name(),
    VHDL_code, expect_AST, test_case)
{
    using attribute_type = ast::expression;
    auto const parser = parser::expression;

    boost::ignore_unused(test_case);

    x3_test::testing_parser<attribute_type> parse;
    auto [parse_ok, parsed_AST] = parse(VHDL_code, parser);

    BOOST_TEST(!parse_ok);
    BOOST_REQUIRE_MESSAGE(x3_test::current_test_passing(),
                          "\n    PARSED AST = '\n" << parsed_AST << "'");

    BOOST_TEST(parsed_AST == expect_AST, btt::per_element());
    BOOST_REQUIRE_MESSAGE(x3_test::current_test_passing(),
                          "\n    PARSED AST = '\n" << parsed_AST << "'");
}


GENERATE_DATASET_TEST_CASE(signal_list)

BOOST_AUTO_TEST_SUITE_END()

