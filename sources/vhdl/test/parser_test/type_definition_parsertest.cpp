/*
 * type_definition_parsertest.cpp
 *
 *  Created on: 16.5.2018
 *      Author: olaf
 */


#include <boost/test/unit_test.hpp>
#include <boost/core/ignore_unused.hpp>

#include <iostream>

#include <eda/vhdl/ast.hpp>
#include "data_set.hpp"
#include "testing_parser_def.hpp"
#include "testing_parser_grammar_hack.hpp"
#include "generate_data_test_case.hpp"
#include "testing_util.hpp"


BOOST_AUTO_TEST_SUITE( parser )


namespace btt    = boost::test_tools;
namespace parser = eda::vhdl::parser;
namespace ast    = eda::vhdl::ast;



struct type_definition_dataset : public ::x3_test::dataset_loader
{
    type_definition_dataset()
    : dataset_loader{ "test_case/type_definition" }
    { }
} const type_definition_dataset;




BOOST_DATA_TEST_CASE( type_definition,
      type_definition_dataset.input()
    ^ type_definition_dataset.expect()
    ^ type_definition_dataset.test_case_name(),
    input, expected, test_case_name)
{
    using attribute_type = ast::type_definition;
    auto const parser = parser::type_definition;

    boost::ignore_unused(test_case_name);

    x3_test::testing_parser<attribute_type> parse;
    auto [parse_ok, parse_result] = parse(input, parser);

    BOOST_TEST(parse_ok);
    BOOST_REQUIRE_MESSAGE(parse_ok,
        x3_test::report_diagnostic(test_case_name, input, parse_result)
    );

    BOOST_TEST(parse_result == expected, btt::per_element());
    BOOST_REQUIRE_MESSAGE(x3_test::current_test_passing(),
        x3_test::report_diagnostic(test_case_name, input, parse_result)
    );
}


BOOST_AUTO_TEST_SUITE_END()

