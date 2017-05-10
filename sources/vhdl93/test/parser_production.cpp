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

    bool parse_ok{ false };
    std::string parse_result {};

    testing_parser<attribute_type> parse;
    std::tie(parse_ok, parse_result) = parse(input, parser::function_call);

    BOOST_TEST(parse_ok);
    BOOST_TEST_INFO("ATTR_RESULT = '" << parse_result << "'");
    BOOST_TEST(parse_result == expect, btt::per_element());
}


/*
 * XXXX
 */
struct xxx_dataset : public ::x3_test::dataset_loader
{
    xxx_dataset()
    : dataset_loader{ "test_case/xxx" }
    { }
} const xxx_dataset;


BOOST_DATA_TEST_CASE( xxxx,
      xxx_dataset.input()
    ^ xxx_dataset.expect()
    ^ xxx_dataset.test_file_name(),
    input, expect, file)
{
    using x3_test::testing_parser;

    typedef ast::selected_name attribute_type;

    // avoid warning, used in case of error for error message by boost.test
    boost::ignore_unused(file);

    bool parse_ok{ false };
    std::string parse_result {};

    testing_parser<attribute_type> parse;
    std::tie(parse_ok, parse_result) = parse(input, parser::selected_name);

    BOOST_TEST(parse_ok);
    BOOST_TEST_INFO("ATTR_RESULT = '" << parse_result << "'");
    BOOST_TEST(parse_result == expect, btt::per_element());
}



BOOST_AUTO_TEST_SUITE_END()

