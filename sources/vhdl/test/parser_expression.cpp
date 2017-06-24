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
#include "data_set.hpp"
#include "testing_parser.hpp"
#include "generate_data_test_case.hpp"


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

#if 0
GENERATE_FAILURE_DATASET_TEST_CASE(expression)
#else
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
    ^ expression_failure_dataset.test_file_name(),
    input, expect, file)
{
    using x3_test::testing_parser;

    typedef ast::expression attribute_type;

    // avoid warning, used in case of error for error message by boost.test
    boost::ignore_unused(file);

    testing_parser<attribute_type> parse;
    auto [parse_ok, parse_result] = parse(input, parser::expression);

    BOOST_TEST(!parse_ok);
    BOOST_TEST_INFO("ATTR_RESULT = '" << parse_result << "'");
    BOOST_TEST(parse_result == expect, btt::per_element());
}
#endif

GENERATE_DATASET_TEST_CASE(signal_list)

BOOST_AUTO_TEST_SUITE_END()

