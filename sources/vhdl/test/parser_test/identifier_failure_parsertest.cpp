/*
 * identifier_failure_parsertest.cpp
 *
 *  Created on: 7.5.2018
 *      Author: olaf
 */


#include <boost/test/unit_test.hpp>

#include <iostream>

#include <eda/vhdl/ast.hpp>
#include "data_set.hpp"
#include "testing_parser.hpp"
#include "testing_parser_grammar_hack.hpp"
#include "generate_data_test_case.hpp"

BOOST_AUTO_TEST_SUITE( identifier_failure )

namespace btt    = boost::test_tools;
namespace parser = eda::vhdl::parser;
namespace ast    = eda::vhdl::ast;

struct identifier_failure_dataset : public ::x3_test::dataset_loader
{
    identifier_failure_dataset()
    : dataset_loader{ "test_case/identifier_failure" }
    { }
} const identifier_failure_dataset;


BOOST_DATA_TEST_CASE( identifier_failure,
      identifier_failure_dataset.input()
    ^ identifier_failure_dataset.expect(),
    VHDL_input, expect_AST)
{
    using attribute_type = ast::identifier;
    auto const parser = parser::identifier;

    x3_test::testing_parser<attribute_type> parse;
    auto [parse_ok, parsed_AST] = parse(VHDL_input, parser);

    BOOST_TEST(!parse_ok);
    BOOST_TEST_INFO("PARSED AST = '" << parsed_AST << "'");
    BOOST_TEST(parsed_AST == expect_AST, btt::per_element());
}

BOOST_AUTO_TEST_SUITE_END()
