/*
 * parser_statement.cpp
 *
 *  Created on: 05.06.2017
 *      Author: olaf
 */

#include <boost/test/unit_test.hpp>
#include <boost/core/ignore_unused.hpp>

#include <iostream>

#include <eda/vhdl93/ast.hpp>
#include "data_set.hpp"
#include "testing_parser.hpp"


BOOST_AUTO_TEST_SUITE( productions )


namespace x3 = boost::spirit::x3;
namespace btt = boost::test_tools;

namespace parser = eda::vhdl93::parser;
namespace ast    = eda::vhdl93::ast;


/*
 * case_statement
 */
struct case_statement_dataset : public ::x3_test::dataset_loader
{
    case_statement_dataset()
    : dataset_loader{ "test_case/case_statement" }
    { }
} const case_statement_dataset;


BOOST_DATA_TEST_CASE( case_statement,
      case_statement_dataset.input()
    ^ case_statement_dataset.expect()
    ^ case_statement_dataset.test_file_name(),
    input, expect, file)
{
    using x3_test::testing_parser;

    typedef ast::case_statement attribute_type;

    // avoid warning, used in case of error for error message by boost.test
    boost::ignore_unused(file);

    testing_parser<attribute_type> parse;
    auto [parse_ok, parse_result] = parse(input, parser::case_statement);

    BOOST_TEST(parse_ok);
    BOOST_TEST_INFO("ATTR_RESULT = '" << parse_result << "'");
    BOOST_TEST(parse_result == expect, btt::per_element());
}


/*
 * exit_statement
 */
struct exit_statement_dataset : public ::x3_test::dataset_loader
{
    exit_statement_dataset()
    : dataset_loader{ "test_case/exit_statement" }
    { }
} const exit_statement_dataset;


BOOST_DATA_TEST_CASE( exit_statement,
      exit_statement_dataset.input()
    ^ exit_statement_dataset.expect()
    ^ exit_statement_dataset.test_file_name(),
    input, expect, file)
{
    using x3_test::testing_parser;

    typedef ast::exit_statement attribute_type;

    // avoid warning, used in case of error for error message by boost.test
    boost::ignore_unused(file);

    testing_parser<attribute_type> parse;
    auto [parse_ok, parse_result] = parse(input, parser::exit_statement);

    BOOST_TEST(parse_ok);
    BOOST_TEST_INFO("ATTR_RESULT = '" << parse_result << "'");
    BOOST_TEST(parse_result == expect, btt::per_element());
}


/*
 * next_statement
 */
struct next_statement_dataset : public ::x3_test::dataset_loader
{
    next_statement_dataset()
    : dataset_loader{ "test_case/next_statement" }
    { }
} const next_statement_dataset;


BOOST_DATA_TEST_CASE( next_statement,
      next_statement_dataset.input()
    ^ next_statement_dataset.expect()
    ^ next_statement_dataset.test_file_name(),
    input, expect, file)
{
    using x3_test::testing_parser;

    typedef ast::next_statement attribute_type;

    // avoid warning, used in case of error for error message by boost.test
    boost::ignore_unused(file);

    testing_parser<attribute_type> parse;
    auto [parse_ok, parse_result] = parse(input, parser::next_statement);

    BOOST_TEST(parse_ok);
    BOOST_TEST_INFO("ATTR_RESULT = '" << parse_result << "'");
    BOOST_TEST(parse_result == expect, btt::per_element());
}
/*
 * return_statement
 */
struct return_statement_dataset : public ::x3_test::dataset_loader
{
    return_statement_dataset()
    : dataset_loader{ "test_case/return_statement" }
    { }
} const return_statement_dataset;


BOOST_DATA_TEST_CASE( return_statement,
      return_statement_dataset.input()
    ^ return_statement_dataset.expect()
    ^ return_statement_dataset.test_file_name(),
    input, expect, file)
{
    using x3_test::testing_parser;

    typedef ast::return_statement attribute_type;

    // avoid warning, used in case of error for error message by boost.test
    boost::ignore_unused(file);

    testing_parser<attribute_type> parse;
    auto [parse_ok, parse_result] = parse(input, parser::return_statement);

    BOOST_TEST(parse_ok);
    BOOST_TEST_INFO("ATTR_RESULT = '" << parse_result << "'");
    BOOST_TEST(parse_result == expect, btt::per_element());
}


/*
 * signal_assignment_statement
 */
struct signal_assignment_statement_dataset : public ::x3_test::dataset_loader
{
    signal_assignment_statement_dataset()
    : dataset_loader{ "test_case/signal_assignment_statement" }
    { }
} const signal_assignment_statement_dataset;


BOOST_DATA_TEST_CASE( signal_assignment_statement,
      signal_assignment_statement_dataset.input()
    ^ signal_assignment_statement_dataset.expect()
    ^ signal_assignment_statement_dataset.test_file_name(),
    input, expect, file)
{
    using x3_test::testing_parser;

    typedef ast::signal_assignment_statement attribute_type;

    // avoid warning, used in case of error for error message by boost.test
    boost::ignore_unused(file);

    testing_parser<attribute_type> parse;
    auto [parse_ok, parse_result] = parse(input, parser::signal_assignment_statement);

    BOOST_TEST(parse_ok);
    BOOST_TEST_INFO("ATTR_RESULT = '" << parse_result << "'");
    BOOST_TEST(parse_result == expect, btt::per_element());
}


/*
 * wait_statement
 */
struct wait_statement_dataset : public ::x3_test::dataset_loader
{
    wait_statement_dataset()
    : dataset_loader{ "test_case/wait_statement" }
    { }
} const wait_statement_dataset;


BOOST_DATA_TEST_CASE( wait_statement,
      wait_statement_dataset.input()
    ^ wait_statement_dataset.expect()
    ^ wait_statement_dataset.test_file_name(),
    input, expect, file)
{
    using x3_test::testing_parser;

    typedef ast::wait_statement attribute_type;

    // avoid warning, used in case of error for error message by boost.test
    boost::ignore_unused(file);

    testing_parser<attribute_type> parse;
    auto [parse_ok, parse_result] = parse(input, parser::wait_statement);

    BOOST_TEST(parse_ok);
    BOOST_TEST_INFO("ATTR_RESULT = '" << parse_result << "'");
    BOOST_TEST(parse_result == expect, btt::per_element());
}


/*
 * sequential_statement
 */
struct sequential_statement_dataset : public ::x3_test::dataset_loader
{
    sequential_statement_dataset()
    : dataset_loader{ "test_case/sequential_statement" }
    { }
} const sequential_statement_dataset;


BOOST_DATA_TEST_CASE( sequential_statement,
      sequential_statement_dataset.input()
    ^ sequential_statement_dataset.expect()
    ^ sequential_statement_dataset.test_file_name(),
    input, expect, file)
{
    using x3_test::testing_parser;

    typedef ast::sequential_statement attribute_type;

    // avoid warning, used in case of error for error message by boost.test
    boost::ignore_unused(file);

    testing_parser<attribute_type> parse;
    auto [parse_ok, parse_result] = parse(input, parser::sequential_statement);

    BOOST_TEST(parse_ok);
    BOOST_TEST_INFO("ATTR_RESULT = '" << parse_result << "'");
    BOOST_TEST(parse_result == expect, btt::per_element());
}


BOOST_AUTO_TEST_SUITE_END()



