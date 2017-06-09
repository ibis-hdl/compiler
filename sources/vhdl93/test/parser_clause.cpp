/*
 * parser_clause.cpp
 *
 *  Created on: 09.06.2017
 *      Author: olaf
 */


#include <boost/test/unit_test.hpp>
#include <boost/core/ignore_unused.hpp>

#include <iostream>

#include <eda/vhdl93/ast.hpp>
#include "data_set.hpp"
#include "testing_parser.hpp"


BOOST_AUTO_TEST_SUITE( clause )


namespace x3 = boost::spirit::x3;
namespace btt = boost::test_tools;

namespace parser = eda::vhdl93::parser;
namespace ast    = eda::vhdl93::ast;


/*
 * use_clause
 */
struct use_clause_dataset : public ::x3_test::dataset_loader
{
    use_clause_dataset()
    : dataset_loader{ "test_case/use_clause" }
    { }
} const use_clause_dataset;


BOOST_DATA_TEST_CASE( use_clause,
      use_clause_dataset.input()
    ^ use_clause_dataset.expect()
    ^ use_clause_dataset.test_file_name(),
    input, expect, file)
{
    using x3_test::testing_parser;

    typedef ast::use_clause attribute_type;

    // avoid warning, used in case of error for error message by boost.test
    boost::ignore_unused(file);

    testing_parser<attribute_type> parse;
    auto [parse_ok, parse_result] = parse(input, parser::use_clause);

    BOOST_TEST(parse_ok);
    BOOST_TEST_INFO("ATTR_RESULT = '" << parse_result << "'");
    BOOST_TEST(parse_result == expect, btt::per_element());
}


/*
 * port_clause
 */
struct port_clause_dataset : public ::x3_test::dataset_loader
{
    port_clause_dataset()
    : dataset_loader{ "test_case/port_clause" }
    { }
} const port_clause_dataset;


BOOST_DATA_TEST_CASE( port_clause,
      port_clause_dataset.input()
    ^ port_clause_dataset.expect()
    ^ port_clause_dataset.test_file_name(),
    input, expect, file)
{
    using x3_test::testing_parser;

    typedef ast::port_clause attribute_type;

    // avoid warning, used in case of error for error message by boost.test
    boost::ignore_unused(file);

    testing_parser<attribute_type> parse;
    auto [parse_ok, parse_result] = parse(input, parser::port_clause);

    BOOST_TEST(parse_ok);
    BOOST_TEST_INFO("ATTR_RESULT = '" << parse_result << "'");
    BOOST_TEST(parse_result == expect, btt::per_element());
}


/*
 * generic_clause
 */
struct generic_clause_dataset : public ::x3_test::dataset_loader
{
    generic_clause_dataset()
    : dataset_loader{ "test_case/generic_clause" }
    { }
} const generic_clause_dataset;


BOOST_DATA_TEST_CASE( generic_clause,
      generic_clause_dataset.input()
    ^ generic_clause_dataset.expect()
    ^ generic_clause_dataset.test_file_name(),
    input, expect, file)
{
    using x3_test::testing_parser;

    typedef ast::generic_clause attribute_type;

    // avoid warning, used in case of error for error message by boost.test
    boost::ignore_unused(file);

    testing_parser<attribute_type> parse;
    auto [parse_ok, parse_result] = parse(input, parser::generic_clause);

    BOOST_TEST(parse_ok);
    BOOST_TEST_INFO("ATTR_RESULT = '" << parse_result << "'");
    BOOST_TEST(parse_result == expect, btt::per_element());
}



BOOST_AUTO_TEST_SUITE_END()




