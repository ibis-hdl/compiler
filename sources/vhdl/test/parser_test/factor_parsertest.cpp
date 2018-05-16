/*
 * factor_parsertest.cpp
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



struct factor_dataset : public ::x3_test::dataset_loader
{
    factor_dataset()
    : dataset_loader{ "test_case/factor" }
    { }
} const factor_dataset;




BOOST_DATA_TEST_CASE( factor,
      factor_dataset.input()
    ^ factor_dataset.expect()
    ^ factor_dataset.test_case_name(),
    VHDL_code, expect_AST, test_case_name)
{
    using attribute_type = ast::factor;
    auto const parser = parser::factor;

    boost::ignore_unused(test_case_name);

    x3_test::testing_parser<attribute_type> parse;
    auto [parse_ok, parsed_AST] = parse(VHDL_code, parser);

    BOOST_TEST(parse_ok);
    BOOST_REQUIRE_MESSAGE(x3_test::current_test_passing(),
                          "\n    PARSED AST = '\n" << parsed_AST << "'");

    BOOST_TEST(parsed_AST == expect_AST, btt::per_element());
    BOOST_REQUIRE_MESSAGE(x3_test::current_test_passing(),
                          "\n    PARSED AST = '\n" << parsed_AST << "'");
}


BOOST_AUTO_TEST_SUITE_END()

