/*
 * production_rules.cpp
 *
 *  Created on: 02.04.2017
 *      Author: olaf
 */


#include <boost/test/unit_test.hpp>
#include <boost/core/ignore_unused.hpp>

#include <iostream>

#include "data_set.hpp"
#include "testing_parser.hpp"


BOOST_AUTO_TEST_SUITE( productions )


namespace x3 = boost::spirit::x3;
namespace btt = boost::test_tools;

namespace parser = eda::vhdl93::parser;
namespace ast    = eda::vhdl93::ast;


::x3_test::dataset_loader enumeration_type_definition_dataset{ "test/enumeration_type_definition" };

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
    BOOST_TEST_INFO("parsed attr (result) = '" << parse_result << "'");
    BOOST_TEST(parse_result == expect, btt::per_element());
}


::x3_test::dataset_loader name_definition_dataset{ "test/name" };

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
    BOOST_TEST_INFO("parsed attr (result) = '" << parse_result << "'");
    BOOST_TEST(parse_result == expect, btt::per_element());
}


::x3_test::dataset_loader primary_dataset{ "test/primary" };

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
    BOOST_TEST_INFO("parsed attr (result) = '" << parse_result << "'");
    BOOST_TEST(parse_result == expect, btt::per_element());
}



BOOST_AUTO_TEST_SUITE_END()

