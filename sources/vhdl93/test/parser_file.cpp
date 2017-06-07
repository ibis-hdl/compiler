/*
 * parser_file.cpp
 *
 *  Created on: 07.06.2017
 *      Author: olaf
 */


#include <boost/test/unit_test.hpp>
#include <boost/core/ignore_unused.hpp>

#include <iostream>

#include <eda/vhdl93/ast.hpp>
#include "data_set.hpp"
#include "testing_parser.hpp"


BOOST_AUTO_TEST_SUITE( file )


namespace x3 = boost::spirit::x3;
namespace btt = boost::test_tools;

namespace parser = eda::vhdl93::parser;
namespace ast    = eda::vhdl93::ast;


#if 0
/*
 * file_declaration
 */
struct file_declaration_dataset : public ::x3_test::dataset_loader
{
    file_declaration_dataset()
    : dataset_loader{ "test_case/file_declaration" }
    { }
} const file_declaration_dataset;


BOOST_DATA_TEST_CASE( file_declaration,
      file_declaration_dataset.input()
    ^ file_declaration_dataset.expect()
    ^ file_declaration_dataset.test_file_name(),
    input, expect, file)
{
    using x3_test::testing_parser;

    typedef ast::file_declaration attribute_type;

    // avoid warning, used in case of error for error message by boost.test
    boost::ignore_unused(file);

    testing_parser<attribute_type> parse;
    auto [parse_ok, parse_result] = parse(input, parser::file_declaration);

    BOOST_TEST(parse_ok);
    BOOST_TEST_INFO("ATTR_RESULT = '" << parse_result << "'");
    BOOST_TEST(parse_result == expect, btt::per_element());
}
#endif

#if 0
/*
 * file_open_information
 */
struct file_open_information_dataset : public ::x3_test::dataset_loader
{
    file_open_information_dataset()
    : dataset_loader{ "test_case/file_open_information" }
    { }
} const file_open_information_dataset;


BOOST_DATA_TEST_CASE( file_open_information,
      file_open_information_dataset.input()
    ^ file_open_information_dataset.expect()
    ^ file_open_information_dataset.test_file_name(),
    input, expect, file)
{
    using x3_test::testing_parser;

    typedef ast::file_open_information attribute_type;

    // avoid warning, used in case of error for error message by boost.test
    boost::ignore_unused(file);

    testing_parser<attribute_type> parse;
    auto [parse_ok, parse_result] = parse(input, parser::file_open_information);

    BOOST_TEST(parse_ok);
    BOOST_TEST_INFO("ATTR_RESULT = '" << parse_result << "'");
    BOOST_TEST(parse_result == expect, btt::per_element());
}
#endif

BOOST_AUTO_TEST_SUITE_END()

