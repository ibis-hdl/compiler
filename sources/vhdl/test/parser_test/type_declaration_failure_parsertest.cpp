/*
 * type_declaration_failure_parsertest.cpp
 *
 *  Created on: 7.5.2018
 *      Author: olaf
 */


#include <boost/test/unit_test.hpp>
#include <boost/core/ignore_unused.hpp>

#include <iostream>

#include <eda/vhdl/ast.hpp>
#include "data_set.hpp"
#include "testing_parser.hpp"
#include "testing_parser_grammar_hack.hpp"
#include "generate_data_test_case.hpp"
#include "testing_util.hpp"

BOOST_AUTO_TEST_SUITE( type_declaration_failure )

namespace btt    = boost::test_tools;
namespace parser = eda::vhdl::parser;
namespace ast    = eda::vhdl::ast;

struct type_declaration_failure_dataset : public ::x3_test::dataset_loader
{
    type_declaration_failure_dataset()
    : dataset_loader{ "test_case/type_declaration_failure" }
    { }
} const type_declaration_failure_dataset;


BOOST_DATA_TEST_CASE( type_declaration_failure,
      type_declaration_failure_dataset.input()
    ^ type_declaration_failure_dataset.expect()
    ^ type_declaration_failure_dataset.test_case_name(),
    VHDL_code, expect_AST, test_case)
{
    using attribute_type = ast::type_declaration;
    auto const parser = parser::type_declaration;

    boost::ignore_unused(test_case);

    x3_test::testing_parser<attribute_type> parse;
    auto [parse_ok, parsed_AST] = parse(VHDL_code, parser);

    BOOST_TEST(!parse_ok);
    BOOST_REQUIRE_MESSAGE(x3_test::current_test_passing(),
                          "\n    PARSED AST = '\n" << parsed_AST << "'");

    BOOST_TEST(parsed_AST == expect_AST, btt::per_element());
    BOOST_REQUIRE_MESSAGE(x3_test::current_test_passing(),
                          "\n    PARSED AST = '\n" << parsed_AST << "'");
}

BOOST_AUTO_TEST_SUITE_END()
