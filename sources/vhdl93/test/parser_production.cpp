/*
 * parser_production.cpp
 *
 *  Created on: 09.05.2017
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
 * function_call
 */
struct function_call_dataset : public ::x3_test::dataset_loader
{
    function_call_dataset()
    : dataset_loader{ "test_case/function_call" }
    { }
} const function_call_dataset;


BOOST_DATA_TEST_CASE( function_call,
      function_call_dataset.input()
    ^ function_call_dataset.expect()
    ^ function_call_dataset.test_file_name(),
    input, expect, file)
{
    using x3_test::testing_parser;

    typedef ast::function_call attribute_type;

    // avoid warning, used in case of error for error message by boost.test
    boost::ignore_unused(file);

    testing_parser<attribute_type> parse;
    auto [parse_ok, parse_result] = parse(input, parser::function_call);

    BOOST_TEST(parse_ok);
    BOOST_TEST_INFO("ATTR_RESULT = '" << parse_result << "'");
    BOOST_TEST(parse_result == expect, btt::per_element());
}


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
 * indexed_name
 */
struct indexed_name_dataset : public ::x3_test::dataset_loader
{
    indexed_name_dataset()
    : dataset_loader{ "test_case/indexed_name" }
    { }
} const indexed_name_dataset;


BOOST_DATA_TEST_CASE( indexed_name,
      indexed_name_dataset.input()
    ^ indexed_name_dataset.expect()
    ^ indexed_name_dataset.test_file_name(),
    input, expect, file)
{
    using x3_test::testing_parser;

    typedef ast::indexed_name attribute_type;

    // avoid warning, used in case of error for error message by boost.test
    boost::ignore_unused(file);

    testing_parser<attribute_type> parse;
    auto [parse_ok, parse_result] = parse(input, parser::indexed_name);

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
 * waveform
 */
struct waveform_dataset : public ::x3_test::dataset_loader
{
    waveform_dataset()
    : dataset_loader{ "test_case/waveform" }
    { }
} const waveform_dataset;


BOOST_DATA_TEST_CASE( waveform,
      waveform_dataset.input()
    ^ waveform_dataset.expect()
    ^ waveform_dataset.test_file_name(),
    input, expect, file)
{
    using x3_test::testing_parser;

    typedef ast::waveform attribute_type;

    // avoid warning, used in case of error for error message by boost.test
    boost::ignore_unused(file);

    testing_parser<attribute_type> parse;
    auto [parse_ok, parse_result] = parse(input, parser::waveform);

    BOOST_TEST(parse_ok);
    BOOST_TEST_INFO("ATTR_RESULT = '" << parse_result << "'");
    BOOST_TEST(parse_result == expect, btt::per_element());
}


/*
 * attribute_name
 */
struct attribute_name_dataset : public ::x3_test::dataset_loader
{
    attribute_name_dataset()
    : dataset_loader{ "test_case/attribute_name" }
    { }
} const attribute_name_dataset;


BOOST_DATA_TEST_CASE( attribute_name,
      attribute_name_dataset.input()
    ^ attribute_name_dataset.expect()
    ^ attribute_name_dataset.test_file_name(),
    input, expect, file)
{
    using x3_test::testing_parser;

    typedef ast::attribute_name attribute_type;

    // avoid warning, used in case of error for error message by boost.test
    boost::ignore_unused(file);

    testing_parser<attribute_type> parse;
    auto [parse_ok, parse_result] = parse(input, parser::attribute_name);

    BOOST_TEST(parse_ok);
    BOOST_TEST_INFO("ATTR_RESULT = '" << parse_result << "'");
    BOOST_TEST(parse_result == expect, btt::per_element());
}


/*
 * attribute_specification
 */
struct attribute_specification_dataset : public ::x3_test::dataset_loader
{
    attribute_specification_dataset()
    : dataset_loader{ "test_case/attribute_specification" }
    { }
} const attribute_specification_dataset;


BOOST_DATA_TEST_CASE( attribute_specification,
      attribute_specification_dataset.input()
    ^ attribute_specification_dataset.expect()
    ^ attribute_specification_dataset.test_file_name(),
    input, expect, file)
{
    using x3_test::testing_parser;

    typedef ast::attribute_specification attribute_type;

    // avoid warning, used in case of error for error message by boost.test
    boost::ignore_unused(file);

    testing_parser<attribute_type> parse;
    auto [parse_ok, parse_result] = parse(input, parser::attribute_specification);

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
 * range aka range_constraint
 */
struct range_dataset : public ::x3_test::dataset_loader
{
    range_dataset()
    : dataset_loader{ "test_case/range" }
    { }
} const range_dataset;


BOOST_DATA_TEST_CASE( range,
      range_dataset.input()
    ^ range_dataset.expect()
    ^ range_dataset.test_file_name(),
    input, expect, file)
{
    using x3_test::testing_parser;

    typedef ast::range attribute_type;

    // avoid warning, used in case of error for error message by boost.test
    boost::ignore_unused(file);

    testing_parser<attribute_type> parse;
    auto [parse_ok, parse_result] = parse(input, parser::range);

    BOOST_TEST(parse_ok);
    BOOST_TEST_INFO("ATTR_RESULT = '" << parse_result << "'");
    BOOST_TEST(parse_result == expect, btt::per_element());
}



/*
 * discrete_range
 */
struct discrete_range_dataset : public ::x3_test::dataset_loader
{
    discrete_range_dataset()
    : dataset_loader{ "test_case/discrete_range" }
    { }
} const discrete_range_dataset;


BOOST_DATA_TEST_CASE( discrete_range,
      discrete_range_dataset.input()
    ^ discrete_range_dataset.expect()
    ^ discrete_range_dataset.test_file_name(),
    input, expect, file)
{
    using x3_test::testing_parser;

    typedef ast::discrete_range attribute_type;

    // avoid warning, used in case of error for error message by boost.test
    boost::ignore_unused(file);

    testing_parser<attribute_type> parse;
    auto [parse_ok, parse_result] = parse(input, parser::discrete_range);

    BOOST_TEST(parse_ok);
    BOOST_TEST_INFO("ATTR_RESULT = '" << parse_result << "'");
    BOOST_TEST(parse_result == expect, btt::per_element());
}



/*
 * index_constraint
 */
struct index_constraint_dataset : public ::x3_test::dataset_loader
{
    index_constraint_dataset()
    : dataset_loader{ "test_case/index_constraint" }
    { }
} const index_constraint_dataset;


BOOST_DATA_TEST_CASE( index_constraint,
      index_constraint_dataset.input()
    ^ index_constraint_dataset.expect()
    ^ index_constraint_dataset.test_file_name(),
    input, expect, file)
{
    using x3_test::testing_parser;

    typedef ast::index_constraint attribute_type;

    // avoid warning, used in case of error for error message by boost.test
    boost::ignore_unused(file);

    testing_parser<attribute_type> parse;
    auto [parse_ok, parse_result] = parse(input, parser::index_constraint);

    BOOST_TEST(parse_ok);
    BOOST_TEST_INFO("ATTR_RESULT = '" << parse_result << "'");
    BOOST_TEST(parse_result == expect, btt::per_element());
}



/*
 * constraint
 */
struct constraint_dataset : public ::x3_test::dataset_loader
{
    constraint_dataset()
    : dataset_loader{ "test_case/constraint" }
    { }
} const constraint_dataset;


BOOST_DATA_TEST_CASE( constraint,
      constraint_dataset.input()
    ^ constraint_dataset.expect()
    ^ constraint_dataset.test_file_name(),
    input, expect, file)
{
    using x3_test::testing_parser;

    typedef ast::constraint attribute_type;

    // avoid warning, used in case of error for error message by boost.test
    boost::ignore_unused(file);

    testing_parser<attribute_type> parse;
    auto [parse_ok, parse_result] = parse(input, parser::constraint);

    BOOST_TEST(parse_ok);
    BOOST_TEST_INFO("ATTR_RESULT = '" << parse_result << "'");
    BOOST_TEST(parse_result == expect, btt::per_element());
}



/*
 * subtype_indication
 */
struct subtype_indication_dataset : public ::x3_test::dataset_loader
{
    subtype_indication_dataset()
    : dataset_loader{ "test_case/subtype_indication" }
    { }
} const subtype_indication_dataset;


BOOST_DATA_TEST_CASE( subtype_indication,
      subtype_indication_dataset.input()
    ^ subtype_indication_dataset.expect()
    ^ subtype_indication_dataset.test_file_name(),
    input, expect, file)
{
    using x3_test::testing_parser;

    typedef ast::subtype_indication attribute_type;

    // avoid warning, used in case of error for error message by boost.test
    boost::ignore_unused(file);

    testing_parser<attribute_type> parse;
    auto [parse_ok, parse_result] = parse(input, parser::subtype_indication);

    BOOST_TEST(parse_ok);
    BOOST_TEST_INFO("ATTR_RESULT = '" << parse_result << "'");
    BOOST_TEST(parse_result == expect, btt::per_element());
}


/*
 * association_list
 */
struct association_list_dataset : public ::x3_test::dataset_loader
{
    association_list_dataset()
    : dataset_loader{ "test_case/association_list" }
    { }
} const association_list_dataset;


BOOST_DATA_TEST_CASE( association_list,
      association_list_dataset.input()
    ^ association_list_dataset.expect()
    ^ association_list_dataset.test_file_name(),
    input, expect, file)
{
    using x3_test::testing_parser;

    typedef ast::association_list attribute_type;

    // avoid warning, used in case of error for error message by boost.test
    boost::ignore_unused(file);

    testing_parser<attribute_type> parse;
    auto [parse_ok, parse_result] = parse(input, parser::association_list);

    BOOST_TEST(parse_ok);
    BOOST_TEST_INFO("ATTR_RESULT = '" << parse_result << "'");
    BOOST_TEST(parse_result == expect, btt::per_element());
}


BOOST_AUTO_TEST_SUITE_END()

