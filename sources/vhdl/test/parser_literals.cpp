/*
 * parser_literals.cpp
 *
 *  Created on: 01.03.2017
 *      Author: olaf
 */

#include <boost/test/unit_test.hpp>
#include <boost/core/ignore_unused.hpp>

#include <iostream>

#include "data_set.hpp"
#include "testing_parser.hpp"
#include "testing_parser_def.hpp"
#include "generate_data_test_case.hpp"


namespace x3 = boost::spirit::x3;
namespace btt = boost::test_tools;
namespace parser = eda::vhdl::parser;
namespace ast    = eda::vhdl::ast;


BOOST_AUTO_TEST_SUITE( parser_literals )


GENERATE_DATASET_TEST_CASE(string_literal)
GENERATE_DATASET_TEST_CASE(character_literal)

/*
 *  integer rule are special since isn't an AST member !
 */
struct integer_dataset : public ::x3_test::dataset_loader
{
    integer_dataset()
    : dataset_loader{ "test_case/integer" }
    { }
} const integer_dataset;


BOOST_DATA_TEST_CASE( integer,
      integer_dataset.input()
    ^ integer_dataset.expect()
    ^ integer_dataset.test_file_name(),
    input, expected, file )
{
    using x3_test::testing_parser;

    // Note, integer isn't an AST member
    typedef std::string attribute_type;

    // avoid warning, used in case of error for error message by boost.test
    boost::ignore_unused(file);

    testing_parser<attribute_type> parse;
    auto [parse_ok, parse_result] =  parse(input, parser::integer);

    BOOST_TEST(parse_ok);
    BOOST_TEST_INFO("ATTR_RESULT = '" << parse_result << "'");
    BOOST_TEST(parse_result == expected, btt::per_element());
}

/*
 * integer (failure)
 */
struct integer_failure_dataset : public ::x3_test::dataset_loader
{
    integer_failure_dataset()
    : dataset_loader{ "test_case/integer_failure" }
    { }
} const integer_failure_dataset;


BOOST_DATA_TEST_CASE( integer_failure,
      integer_failure_dataset.input()
    ^ integer_failure_dataset.expect()
    ^ integer_failure_dataset.test_file_name(),
    input, expected, file )
{
    using x3_test::testing_parser;

    // Note, integer isn't an AST member
    typedef std::string attribute_type;

    // avoid warning, used in case of error for error message by boost.test
    boost::ignore_unused(file);

    testing_parser<attribute_type> parse;
    auto [parse_ok, parse_result] = parse(input, parser::integer);

    BOOST_TEST(!parse_ok);
    BOOST_TEST_INFO("ATTR_RESULT = '" << parse_result << "'");
    BOOST_TEST(parse_result == expected, btt::per_element());
}

GENERATE_DATASET_TEST_CASE(identifier)

/*
 * identifier (failure)
 */
struct identifier_failure_dataset : public ::x3_test::dataset_loader
{
    identifier_failure_dataset()
    : dataset_loader{ "test_case/identifier_failure" }
    { }
} const identifier_failure_dataset;


BOOST_DATA_TEST_CASE( identifier_fail,
      identifier_failure_dataset.input()
    ^ identifier_failure_dataset.expect()
    ^ identifier_failure_dataset.test_file_name(),
    input, expected, file )
{
    using x3_test::testing_parser;

    typedef ast::identifier attribute_type;

    // avoid warning, used in case of error for error message by boost.test
    boost::ignore_unused(file);

    testing_parser<attribute_type> parse;
    auto [parse_ok, parse_result] = parse(input, parser::identifier);

    BOOST_TEST(!parse_ok);
    BOOST_TEST_INFO("ATTR_RESULT = '" << parse_result << "'");
    BOOST_TEST(parse_result == expected, btt::per_element());
}


GENERATE_DATASET_TEST_CASE(identifier_list)
GENERATE_DATASET_TEST_CASE(based_literal)
GENERATE_DATASET_TEST_CASE(decimal_literal)
GENERATE_DATASET_TEST_CASE(bit_string_literal)
GENERATE_DATASET_TEST_CASE(abstract_literal)
GENERATE_DATASET_TEST_CASE(physical_literal)

/*
 * physical_literal_failure
 */
struct physical_literal_failure_dataset : public ::x3_test::dataset_loader
{
    physical_literal_failure_dataset()
    : dataset_loader{ "test_case/physical_literal_failure" }
    { }
} const physical_literal_failure_dataset;


BOOST_DATA_TEST_CASE( physical_literal_fail,
      physical_literal_failure_dataset.input()
    ^ physical_literal_failure_dataset.expect()
    ^ physical_literal_failure_dataset.test_file_name(),
    input, expected, file)
{
    using x3_test::testing_parser;

    typedef ast::physical_literal attribute_type;

    // avoid warning, used in case of error for error message by boost.test
    boost::ignore_unused(file);

    testing_parser<attribute_type> parse;
    auto [parse_ok, parse_result] =  parse(input, parser::physical_literal);

    BOOST_TEST(!parse_ok);
    BOOST_TEST_INFO("ATTR_RESULT = '" << parse_result << "'");
    BOOST_TEST(parse_result == expected, btt::per_element());
}


GENERATE_DATASET_TEST_CASE(numeric_literal)
GENERATE_DATASET_TEST_CASE(literal)


BOOST_AUTO_TEST_SUITE_END()

