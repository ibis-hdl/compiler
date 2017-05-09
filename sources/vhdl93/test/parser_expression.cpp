/*
 * production_rules.cpp
 *
 *  Created on: 02.04.2017
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
 * enumeration_type_definition
 */
struct enumeration_type_definition_dataset : public ::x3_test::dataset_loader
{
    enumeration_type_definition_dataset()
    : dataset_loader{ "test_case/enumeration_type_definition" }
    { }
} const enumeration_type_definition_dataset;


BOOST_DATA_TEST_CASE( enumeration_type_definition,
      enumeration_type_definition_dataset.input()
    ^ enumeration_type_definition_dataset.expect()
    ^ enumeration_type_definition_dataset.test_file_name(),
    input, expect, file)
{
    using x3_test::testing_parser;

    typedef ast::enumeration_type_definition attribute_type;

    // avoid warning, used in case of error for error message by boost.test
    boost::ignore_unused(file);

    bool parse_ok{ false };
    std::string parse_result {};

    testing_parser<attribute_type> parse;
    std::tie(parse_ok, parse_result) = parse(input, parser::enumeration_type_definition);

    BOOST_TEST(parse_ok);
    BOOST_TEST_INFO("ATTR_RESULT = '" << parse_result << "'");
    BOOST_TEST(parse_result == expect, btt::per_element());
}


/*
 * names
 */
struct name_definition_dataset : public ::x3_test::dataset_loader
{
    name_definition_dataset()
    : dataset_loader{ "test_case/name" }
    { }
} const name_definition_dataset;


BOOST_DATA_TEST_CASE( name,
      name_definition_dataset.input()
    ^ name_definition_dataset.expect()
    ^ name_definition_dataset.test_file_name(),
    input, expect, file)
{
    using x3_test::testing_parser;

    typedef ast::name attribute_type;

    // avoid warning, used in case of error for error message by boost.test
    boost::ignore_unused(file);

    bool parse_ok{ false };
    std::string parse_result {};

    testing_parser<attribute_type> parse;
    std::tie(parse_ok, parse_result) = parse(input, parser::name);

    BOOST_TEST(parse_ok);
    BOOST_TEST_INFO("ATTR_RESULT = '" << parse_result << "'");
    BOOST_TEST(parse_result == expect, btt::per_element());
}


/*
 * primary
 */
struct primary_dataset : public ::x3_test::dataset_loader
{
    primary_dataset()
    : dataset_loader{ "test_case/primary" }
    { }
} const primary_dataset;


BOOST_DATA_TEST_CASE( primary,
      primary_dataset.input()
    ^ primary_dataset.expect()
    ^ primary_dataset.test_file_name(),
    input, expect, file)
{
    using x3_test::testing_parser;

    typedef ast::primary attribute_type;

    // avoid warning, used in case of error for error message by boost.test
    boost::ignore_unused(file);

    bool parse_ok{ false };
    std::string parse_result {};

    testing_parser<attribute_type> parse;
    std::tie(parse_ok, parse_result) = parse(input, parser::primary);

    BOOST_TEST(parse_ok);
    BOOST_TEST_INFO("ATTR_RESULT = '" << parse_result << "'");
    BOOST_TEST(parse_result == expect, btt::per_element());
}


/*
 * factor
 */
struct factor_dataset : public ::x3_test::dataset_loader
{
    factor_dataset()
    : dataset_loader{ "test_case/factor" }
    { }
} const factor_dataset;


BOOST_DATA_TEST_CASE( factor,
      factor_dataset.input()
    ^ factor_dataset.expect()
    ^ factor_dataset.test_file_name(),
    input, expect, file)
{
    using x3_test::testing_parser;

    typedef ast::factor attribute_type;

    // avoid warning, used in case of error for error message by boost.test
    boost::ignore_unused(file);

    bool parse_ok{ false };
    std::string parse_result {};

    testing_parser<attribute_type> parse;
    std::tie(parse_ok, parse_result) = parse(input, parser::factor);

    BOOST_TEST(parse_ok);
    BOOST_TEST_INFO("ATTR_RESULT = '" << parse_result << "'");
    BOOST_TEST(parse_result == expect, btt::per_element());
}

/*
 * term
 */
struct term_dataset : public ::x3_test::dataset_loader
{
    term_dataset()
    : dataset_loader{ "test_case/term" }
    { }
} const term_dataset;


BOOST_DATA_TEST_CASE( term,
        term_dataset.input()
    ^ term_dataset.expect()
    ^ term_dataset.test_file_name(),
    input, expect, file)
{
    using x3_test::testing_parser;

    typedef ast::term attribute_type;

    // avoid warning, used in case of error for error message by boost.test
    boost::ignore_unused(file);

    bool parse_ok{ false };
    std::string parse_result {};

    testing_parser<attribute_type> parse;
    std::tie(parse_ok, parse_result) = parse(input, parser::term);

    BOOST_TEST(parse_ok);
    BOOST_TEST_INFO("ATTR_RESULT = '" << parse_result << "'");
    BOOST_TEST(parse_result == expect, btt::per_element());
}


/*
 * simple_expression
 */
struct simple_expression_dataset : public ::x3_test::dataset_loader
{
    simple_expression_dataset()
    : dataset_loader{ "test_case/simple_expression" }
    { }
} const simple_expression_dataset;


BOOST_DATA_TEST_CASE( simple_expression,
      simple_expression_dataset.input()
    ^ simple_expression_dataset.expect()
    ^ simple_expression_dataset.test_file_name(),
    input, expect, file)
{
    using x3_test::testing_parser;

    typedef ast::simple_expression attribute_type;

    // avoid warning, used in case of error for error message by boost.test
    boost::ignore_unused(file);

    bool parse_ok{ false };
    std::string parse_result {};

    testing_parser<attribute_type> parse;
    std::tie(parse_ok, parse_result) = parse(input, parser::simple_expression);

    BOOST_TEST(parse_ok);
    BOOST_TEST_INFO("ATTR_RESULT = '" << parse_result << "'");
    BOOST_TEST(parse_result == expect, btt::per_element());
}


/*
 * shift_expression
 */
struct shift_expression_dataset : public ::x3_test::dataset_loader
{
    shift_expression_dataset()
    : dataset_loader{ "test_case/shift_expression" }
    { }
} const shift_expression_dataset;


BOOST_DATA_TEST_CASE( shift_expression,
      shift_expression_dataset.input()
    ^ shift_expression_dataset.expect()
    ^ shift_expression_dataset.test_file_name(),
    input, expect, file)
{
    using x3_test::testing_parser;

    typedef ast::shift_expression attribute_type;

    // avoid warning, used in case of error for error message by boost.test
    boost::ignore_unused(file);

    bool parse_ok{ false };
    std::string parse_result {};

    testing_parser<attribute_type> parse;
    std::tie(parse_ok, parse_result) = parse(input, parser::shift_expression);

    BOOST_TEST(parse_ok);
    BOOST_TEST_INFO("ATTR_RESULT = '" << parse_result << "'");
    BOOST_TEST(parse_result == expect, btt::per_element());
}


/*
 * relation
 */
struct relation_dataset : public ::x3_test::dataset_loader
{
    relation_dataset()
    : dataset_loader{ "test_case/relation" }
    { }
} const relation_dataset;


BOOST_DATA_TEST_CASE( relation,
      relation_dataset.input()
    ^ relation_dataset.expect()
    ^ relation_dataset.test_file_name(),
    input, expect, file)
{
    using x3_test::testing_parser;

    typedef ast::relation attribute_type;

    // avoid warning, used in case of error for error message by boost.test
    boost::ignore_unused(file);

    bool parse_ok{ false };
    std::string parse_result {};

    testing_parser<attribute_type> parse;
    std::tie(parse_ok, parse_result) = parse(input, parser::relation);

    BOOST_TEST(parse_ok);
    BOOST_TEST_INFO("ATTR_RESULT = '" << parse_result << "'");
    BOOST_TEST(parse_result == expect, btt::per_element());
}


/*
 * expression
 */
struct expression_dataset : public ::x3_test::dataset_loader
{
    expression_dataset()
    : dataset_loader{ "test_case/expression" }
    { }
} const expression_dataset;


BOOST_DATA_TEST_CASE( expression,
      expression_dataset.input()
    ^ expression_dataset.expect()
    ^ expression_dataset.test_file_name(),
    input, expect, file)
{
    using x3_test::testing_parser;

    typedef ast::expression attribute_type;

    // avoid warning, used in case of error for error message by boost.test
    boost::ignore_unused(file);

    bool parse_ok{ false };
    std::string parse_result {};

    testing_parser<attribute_type> parse;
    std::tie(parse_ok, parse_result) = parse(input, parser::expression);

    BOOST_TEST(parse_ok);
    BOOST_TEST_INFO("ATTR_RESULT = '" << parse_result << "'");
    BOOST_TEST(parse_result == expect, btt::per_element());
}


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

    bool parse_ok{ false };
    std::string parse_result {};

    testing_parser<attribute_type> parse;
    std::tie(parse_ok, parse_result) = parse(input, parser::expression);

    BOOST_TEST(!parse_ok);
    BOOST_TEST_INFO("ATTR_RESULT = '" << parse_result << "'");
    BOOST_TEST(parse_result == expect, btt::per_element());
}


/*
 * signal_list
 */
struct signal_list_dataset : public ::x3_test::dataset_loader
{
    signal_list_dataset()
    : dataset_loader{ "test_case/signal_list" }
    { }
} const signal_list_dataset;


BOOST_DATA_TEST_CASE( signal_list,
      signal_list_dataset.input()
    ^ signal_list_dataset.expect()
    ^ signal_list_dataset.test_file_name(),
    input, expect, file)
{
    using x3_test::testing_parser;

    typedef ast::signal_list attribute_type;

    // avoid warning, used in case of error for error message by boost.test
    boost::ignore_unused(file);

    bool parse_ok{ false };
    std::string parse_result {};

    testing_parser<attribute_type> parse;
    std::tie(parse_ok, parse_result) = parse(input, parser::signal_list);

    BOOST_TEST(parse_ok);
    BOOST_TEST_INFO("ATTR_RESULT = '" << parse_result << "'");
    BOOST_TEST(parse_result == expect, btt::per_element());
}


BOOST_AUTO_TEST_SUITE_END()

