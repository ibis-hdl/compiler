/*
 * parser_interface.cpp
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


BOOST_AUTO_TEST_SUITE( interface )


namespace x3 = boost::spirit::x3;
namespace btt = boost::test_tools;

namespace parser = eda::vhdl93::parser;
namespace ast    = eda::vhdl93::ast;

#if 0
/*
 * interface_constant_declaration
 */
struct interface_constant_declaration_dataset : public ::x3_test::dataset_loader
{
    interface_constant_declaration_dataset()
    : dataset_loader{ "test_case/interface_constant_declaration" }
    { }
} const interface_constant_declaration_dataset;


BOOST_DATA_TEST_CASE( interface_constant_declaration,
      interface_constant_declaration_dataset.input()
    ^ interface_constant_declaration_dataset.expect()
    ^ interface_constant_declaration_dataset.test_file_name(),
    input, expect, file)
{
    using x3_test::testing_parser;

    typedef ast::interface_constant_declaration attribute_type;

    // avoid warning, used in case of error for error message by boost.test
    boost::ignore_unused(file);

    testing_parser<attribute_type> parse;
    auto [parse_ok, parse_result] = parse(input, parser::interface_constant_declaration);

    BOOST_TEST(parse_ok);
    BOOST_TEST_INFO("ATTR_RESULT = '" << parse_result << "'");
    BOOST_TEST(parse_result == expect, btt::per_element());
}
#endif

#if 0
/*
 * interface_signal_declaration
 */
struct interface_signal_declaration_dataset : public ::x3_test::dataset_loader
{
    interface_signal_declaration_dataset()
    : dataset_loader{ "test_case/interface_signal_declaration" }
    { }
} const interface_signal_declaration_dataset;


BOOST_DATA_TEST_CASE( interface_signal_declaration,
      interface_signal_declaration_dataset.input()
    ^ interface_signal_declaration_dataset.expect()
    ^ interface_signal_declaration_dataset.test_file_name(),
    input, expect, file)
{
    using x3_test::testing_parser;

    typedef ast::interface_signal_declaration attribute_type;

    // avoid warning, used in case of error for error message by boost.test
    boost::ignore_unused(file);

    testing_parser<attribute_type> parse;
    auto [parse_ok, parse_result] = parse(input, parser::interface_signal_declaration);

    BOOST_TEST(parse_ok);
    BOOST_TEST_INFO("ATTR_RESULT = '" << parse_result << "'");
    BOOST_TEST(parse_result == expect, btt::per_element());
}
#endif

#if 0
/*
 * interface_variable_declaration
 */
struct interface_variable_declaration_dataset : public ::x3_test::dataset_loader
{
    interface_variable_declaration_dataset()
    : dataset_loader{ "test_case/interface_variable_declaration" }
    { }
} const interface_variable_declaration_dataset;


BOOST_DATA_TEST_CASE( interface_variable_declaration,
      interface_variable_declaration_dataset.input()
    ^ interface_variable_declaration_dataset.expect()
    ^ interface_variable_declaration_dataset.test_file_name(),
    input, expect, file)
{
    using x3_test::testing_parser;

    typedef ast::interface_variable_declaration attribute_type;

    // avoid warning, used in case of error for error message by boost.test
    boost::ignore_unused(file);

    testing_parser<attribute_type> parse;
    auto [parse_ok, parse_result] = parse(input, parser::interface_variable_declaration);

    BOOST_TEST(parse_ok);
    BOOST_TEST_INFO("ATTR_RESULT = '" << parse_result << "'");
    BOOST_TEST(parse_result == expect, btt::per_element());
}
#endif


BOOST_AUTO_TEST_SUITE_END()



