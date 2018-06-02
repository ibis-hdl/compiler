/*
 * physical_literal_test.cpp
 *
 *  Created on: 2.6.2018
 *      Author: olaf
 */


#include <boost/test/unit_test.hpp>
#include <boost/core/ignore_unused.hpp>

#include <iostream>

#include <eda/vhdl/ast.hpp>

#include <testsuite/vhdl_parser/data_set.hpp>
#include <testsuite/vhdl_parser/testing_parser_def.hpp>
#include <testsuite/vhdl_parser/testing_parser_grammar_hack.hpp>
#include <testsuite/vhdl_parser/generate_data_test_case.hpp>
#include <testsuite/vhdl_parser/testing_util.hpp>


BOOST_AUTO_TEST_SUITE( parser )


namespace btt    = boost::test_tools;
namespace parser = eda::vhdl::parser;
namespace ast    = eda::vhdl::ast;



struct physical_literal_dataset : public testsuite::vhdl_parser::util::dataset_loader
{
    physical_literal_dataset()
    : dataset_loader{ "test_case/physical_literal" }
    { }
} const physical_literal_dataset;


struct physical_literal_failure_dataset : public testsuite::vhdl_parser::util::dataset_loader
{
    physical_literal_failure_dataset()
    : dataset_loader{ "test_case/physical_literal_failure" }
    { }
} const physical_literal_failure_dataset;




BOOST_DATA_TEST_CASE( physical_literal,
      physical_literal_dataset.input()
    ^ physical_literal_dataset.expect()
    ^ physical_literal_dataset.test_case_name(),
    input, expected, test_case_name)
{
    using attribute_type = ast::physical_literal;
    auto const parser = parser::physical_literal;

    boost::ignore_unused(test_case_name);
    
    using testsuite::vhdl_parser::util::testing_parser;
    using testsuite::vhdl_parser::util::current_test_passing;
    using testsuite::vhdl_parser::util::report_diagnostic;

    testing_parser<attribute_type> parse;
    auto [parse_ok, parse_result] = parse(input, parser);

    BOOST_TEST(parse_ok);
    BOOST_REQUIRE_MESSAGE(parse_ok,
        report_diagnostic(test_case_name, input, parse_result)
    );

    BOOST_TEST(parse_result == expected, btt::per_element());
    BOOST_REQUIRE_MESSAGE(current_test_passing(),
        report_diagnostic(test_case_name, input, parse_result)
    );
}


BOOST_DATA_TEST_CASE( physical_literal_failure,
      physical_literal_failure_dataset.input()
    ^ physical_literal_failure_dataset.expect()
    ^ physical_literal_failure_dataset.test_case_name(),
    input, expected, test_case_name)
{
    using attribute_type = ast::physical_literal;
    auto const parser = parser::physical_literal;

    boost::ignore_unused(test_case_name);
    
    using testsuite::vhdl_parser::util::testing_parser;
    using testsuite::vhdl_parser::util::current_test_passing;
    using testsuite::vhdl_parser::util::report_diagnostic;

    testing_parser<attribute_type> parse;
    auto [parse_ok, parse_result] = parse(input, parser);

    BOOST_TEST(!parse_ok);
    BOOST_REQUIRE_MESSAGE(!parse_ok,
        report_diagnostic(test_case_name, input, parse_result)
    );

    BOOST_TEST(parse_result == expected, btt::per_element());
    BOOST_REQUIRE_MESSAGE(current_test_passing(),
        report_diagnostic(test_case_name, input, parse_result)
    );
}


BOOST_AUTO_TEST_SUITE_END()
