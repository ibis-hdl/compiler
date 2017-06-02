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


BOOST_AUTO_TEST_SUITE( parser_literals )


namespace x3 = boost::spirit::x3;
namespace btt = boost::test_tools;

namespace parser = eda::vhdl93::parser;
namespace ast    = eda::vhdl93::ast;


/*
 * string_literal
 */
struct string_literal_dataset : public ::x3_test::dataset_loader
{
    string_literal_dataset()
    : dataset_loader{ "test_case/string_literal" }
    { }
} const string_literal_dataset;

BOOST_DATA_TEST_CASE( string_literal,
      string_literal_dataset.input()
    ^ string_literal_dataset.expect()
    ^ string_literal_dataset.test_file_name(),
    input, expected, file)
{
    using x3_test::testing_parser;

    typedef ast::string_literal attribute_type;

    // avoid warning, used in case of error for error message by boost.test
    boost::ignore_unused(file);

    testing_parser<attribute_type> parse;
    auto [parse_ok, parse_result] =  parse(input, parser::string_literal);

    BOOST_TEST(parse_ok);
    BOOST_TEST_INFO("ATTR_RESULT = '" << parse_result << "'");
    BOOST_TEST(parse_result == expected, btt::per_element());
}


/*
 * character_literal
 */
struct character_literal_dataset : public ::x3_test::dataset_loader
{
    character_literal_dataset()
    : dataset_loader{ "test_case/character_literal" }
    { }
} const character_literal_dataset;


BOOST_DATA_TEST_CASE( character_literal,
      character_literal_dataset.input()
    ^ character_literal_dataset.expect()
    ^ character_literal_dataset.test_file_name(),
    input, expected, file )
{
    using x3_test::testing_parser;

    typedef ast::character_literal attribute_type;

    // avoid warning, used in case of error for error message by boost.test
    boost::ignore_unused(file);

    testing_parser<attribute_type> parse;
    auto [parse_ok, parse_result] =  parse(input, parser::character_literal);

    BOOST_TEST(parse_ok);
    BOOST_TEST_INFO("ATTR_RESULT = '" << parse_result << "'");
    BOOST_TEST(parse_result == expected, btt::per_element());
}


/*
 * integer
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


/*
 * identifier
 */
struct identifier_dataset : public ::x3_test::dataset_loader
{
    identifier_dataset()
    : dataset_loader{ "test_case/identifier" }
    { }
} const identifier_dataset;


BOOST_DATA_TEST_CASE( identifier,
      identifier_dataset.input()
    ^ identifier_dataset.expect()
    ^ identifier_dataset.test_file_name(),
    input, expected, file )
{
    using x3_test::testing_parser;

    typedef ast::identifier attribute_type;

    // avoid warning, used in case of error for error message by boost.test
    boost::ignore_unused(file);

    testing_parser<attribute_type> parse;
    auto [parse_ok, parse_result] = parse(input, parser::identifier);

    BOOST_TEST(parse_ok);
    BOOST_TEST_INFO("ATTR_RESULT = '" << parse_result << "'");
    BOOST_TEST(parse_result == expected, btt::per_element());
}


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


/*
 * identifier_list
 */
struct identifier_list_dataset : public ::x3_test::dataset_loader
{
    identifier_list_dataset()
    : dataset_loader{ "test_case/identifier_list" }
    { }
} const identifier_list_dataset;


BOOST_DATA_TEST_CASE( identifier_list,
      identifier_list_dataset.input()
    ^ identifier_list_dataset.expect()
    ^ identifier_list_dataset.test_file_name(),
    input, expected, file )
{
    using x3_test::testing_parser;

    typedef ast::identifier_list attribute_type;

    // avoid warning, used in case of error for error message by boost.test
    boost::ignore_unused(file);

    testing_parser<attribute_type> parse;
    auto [parse_ok, parse_result] = parse(input, parser::identifier_list);

    BOOST_TEST(parse_ok);
    BOOST_TEST_INFO("ATTR_RESULT = '" << parse_result << "'");
    BOOST_TEST(parse_result == expected, btt::per_element());
}


/*
 * based_literal
 */
struct based_literal_dataset : public ::x3_test::dataset_loader
{
    based_literal_dataset()
    : dataset_loader{ "test_case/based_literal" }
    { }
} const based_literal_dataset;


BOOST_DATA_TEST_CASE( based_literal,
      based_literal_dataset.input()
    ^ based_literal_dataset.expect()
    ^ based_literal_dataset.test_file_name(),
    input, expected, file )
{
    using x3_test::testing_parser;

    typedef ast::based_literal attribute_type;

    // avoid warning, used in case of error for error message by boost.test
    boost::ignore_unused(file);

    testing_parser<attribute_type> parse;
    auto [parse_ok, parse_result] = parse(input, parser::based_literal);

    BOOST_TEST(parse_ok);
    BOOST_TEST_INFO("ATTR_RESULT = '" << parse_result << "'");
    BOOST_TEST(parse_result == expected, btt::per_element());
}


/*
 * decimal_literal
 */
struct decimal_literal_dataset : public ::x3_test::dataset_loader
{
    decimal_literal_dataset()
    : dataset_loader{ "test_case/decimal_literal" }
    { }
} const decimal_literal_dataset;


BOOST_DATA_TEST_CASE( decimal_literal,
      decimal_literal_dataset.input()
    ^ decimal_literal_dataset.expect()
    ^ decimal_literal_dataset.test_file_name(),
    input, expected, file )
{
    using x3_test::testing_parser;

    typedef ast::decimal_literal attribute_type;

    // avoid warning, used in case of error for error message by boost.test
    boost::ignore_unused(file);

    testing_parser<attribute_type> parse;
    auto [parse_ok, parse_result] = parse(input, parser::decimal_literal);

    BOOST_TEST(parse_ok);
    BOOST_TEST_INFO("ATTR_RESULT = '" << parse_result << "'");
    BOOST_TEST(parse_result == expected, btt::per_element());
}


/*
 * bit_string_literal
 */
struct bit_string_literal_dataset : public ::x3_test::dataset_loader
{
    bit_string_literal_dataset()
    : dataset_loader{ "test_case/bit_string_literal" }
    { }
} const bit_string_literal_dataset;


BOOST_DATA_TEST_CASE( bit_string_literal,
      bit_string_literal_dataset.input()
    ^ bit_string_literal_dataset.expect()
    ^ bit_string_literal_dataset.test_file_name(),
    input, expected, file )
{
    using x3_test::testing_parser;

    typedef ast::bit_string_literal attribute_type;

    // avoid warning, used in case of error for error message by boost.test
    boost::ignore_unused(file);

    testing_parser<attribute_type> parse;
    auto [parse_ok, parse_result] =  parse(input, parser::bit_string_literal);

    BOOST_TEST(parse_ok);
    BOOST_TEST_INFO("ATTR_RESULT = '" << parse_result << "'");
    BOOST_TEST(parse_result == expected, btt::per_element());
}


/*
 * abstract_literal
 */
struct abstract_literal_dataset : public ::x3_test::dataset_loader
{
    abstract_literal_dataset()
    : dataset_loader{ "test_case/abstract_literal" }
    { }
} const abstract_literal_dataset;


BOOST_DATA_TEST_CASE( abstract_literal,
      abstract_literal_dataset.input()
    ^ abstract_literal_dataset.expect()
    ^ abstract_literal_dataset.test_file_name(),
    input, expected, file)
{
    using x3_test::testing_parser;

    typedef ast::abstract_literal attribute_type;

    // avoid warning, used in case of error for error message by boost.test
    boost::ignore_unused(file);

    testing_parser<attribute_type> parse;
    auto [parse_ok, parse_result] =  parse(input, parser::abstract_literal);

    BOOST_TEST(parse_ok);
    BOOST_TEST_INFO("ATTR_RESULT = '" << parse_result << "'");
    BOOST_TEST(parse_result == expected, btt::per_element());
}


/*
 * physical_literal
 */
struct physical_literal_dataset : public ::x3_test::dataset_loader
{
    physical_literal_dataset()
    : dataset_loader{ "test_case/physical_literal" }
    { }
} const physical_literal_dataset;


BOOST_DATA_TEST_CASE( physical_literal,
      physical_literal_dataset.input()
    ^ physical_literal_dataset.expect()
    ^ physical_literal_dataset.test_file_name(),
    input, expected, file)
{
    using x3_test::testing_parser;

    typedef ast::physical_literal attribute_type;

    // avoid warning, used in case of error for error message by boost.test
    boost::ignore_unused(file);

    testing_parser<attribute_type> parse;
    auto [parse_ok, parse_result] =  parse(input, parser::physical_literal);

    BOOST_TEST(parse_ok);
    BOOST_TEST_INFO("ATTR_RESULT = '" << parse_result << "'");
    BOOST_TEST(parse_result == expected, btt::per_element());
}


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


/*
 * numeric_literal
 */
struct numeric_dataset : public ::x3_test::dataset_loader
{
    numeric_dataset()
    : dataset_loader{ "test_case/numeric_literal" }
    { }
} const numeric_dataset;


BOOST_DATA_TEST_CASE(numeric_literal,
      numeric_dataset.input()
    ^ numeric_dataset.expect()
    ^ numeric_dataset.test_file_name(),
    input, expected, file)
{
    using x3_test::testing_parser;

    typedef ast::numeric_literal attribute_type;

    // avoid warning, used in case of error for error message by boost.test
    boost::ignore_unused(file);

    testing_parser<attribute_type> parse;
    auto [parse_ok, parse_result] =  parse(input, parser::numeric_literal);

    BOOST_TEST(parse_ok);
    BOOST_TEST_INFO("ATTR_RESULT = '" << parse_result << "'");
    BOOST_TEST(parse_result == expected, btt::per_element());
}


/*
 * literal
 */
struct literal_dataset : public ::x3_test::dataset_loader
{
    literal_dataset()
    : dataset_loader{ "test_case/literal" }
    { }
} const literal_dataset;


BOOST_DATA_TEST_CASE(literal,
      literal_dataset.input()
    ^ literal_dataset.expect()
    ^ literal_dataset.test_file_name(),
    input, expected, file)
{
    using x3_test::testing_parser;

    typedef ast::literal attribute_type;

    // avoid warning, used in case of error for error message by boost.test
    boost::ignore_unused(file);

    testing_parser<attribute_type> parse;
    auto [parse_ok, parse_result] =  parse(input, parser::literal);

    BOOST_TEST(parse_ok);
    BOOST_TEST_INFO("ATTR_RESULT = '" << parse_result << "'");
    BOOST_TEST(parse_result == expected, btt::per_element());
}


BOOST_AUTO_TEST_SUITE_END()

