/*
 * parser_literals.cpp
 *
 *  Created on: 01.03.2017
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


namespace x3 = boost::spirit::x3;
namespace btt = boost::test_tools;
namespace parser = eda::vhdl::parser;
namespace ast    = eda::vhdl::ast;


BOOST_AUTO_TEST_SUITE( parser_literals )


GENERATE_DATASET_TEST_CASE(string_literal)
GENERATE_DATASET_TEST_CASE(character_literal)
GENERATE_DATASET_TEST_CASE(integer)

/*
 * integer (failure)
 */
struct integer_failure_dataset : public testsuite::vhdl_parser::util::dataset_loader
{
    integer_failure_dataset()
    : dataset_loader{ "test_case/integer_failure" }
    { }
} const integer_failure_dataset;


BOOST_DATA_TEST_CASE( integer_failure,
      integer_failure_dataset.input()
    ^ integer_failure_dataset.expect()
    ^ integer_failure_dataset.test_case_name(),
    VHDL_code, expect_AST, test_case)
{
    using attribute_type = ast::integer;
    auto const parser = parser::integer;

    boost::ignore_unused(test_case);

    using testsuite::vhdl_parser::util::testing_parser;
    using testsuite::vhdl_parser::util::current_test_passing;

    testing_parser<attribute_type> parse;
    auto [parse_ok, parsed_AST] = parse(VHDL_code, parser);

    BOOST_TEST(!parse_ok);
    BOOST_REQUIRE_MESSAGE(current_test_passing(),
                          "\n    PARSED AST = '\n" << parsed_AST << "'");

    BOOST_TEST(parsed_AST == expect_AST, btt::per_element());
    BOOST_REQUIRE_MESSAGE(current_test_passing(),
                          "\n    PARSED AST = '\n" << parsed_AST << "'");
}

GENERATE_DATASET_TEST_CASE(identifier)

/*
 * identifier (failure)
 */
struct identifier_failure_dataset : public testsuite::vhdl_parser::util::dataset_loader
{
    identifier_failure_dataset()
    : dataset_loader{ "test_case/identifier_failure" }
    { }
} const identifier_failure_dataset;


BOOST_DATA_TEST_CASE( identifier_failure,
      identifier_failure_dataset.input()
    ^ identifier_failure_dataset.expect()
    ^ identifier_failure_dataset.test_case_name(),
    VHDL_code, expect_AST, test_case)
{
    using attribute_type = ast::identifier;
    auto const parser = parser::identifier;

    boost::ignore_unused(test_case);

    using testsuite::vhdl_parser::util::testing_parser;
    using testsuite::vhdl_parser::util::current_test_passing;

    testing_parser<attribute_type> parse;
    auto [parse_ok, parsed_AST] = parse(VHDL_code, parser);

    BOOST_TEST(!parse_ok);
    BOOST_REQUIRE_MESSAGE(current_test_passing(),
                          "\n    PARSED AST = '\n" << parsed_AST << "'");

    BOOST_TEST(parsed_AST == expect_AST, btt::per_element());
    BOOST_REQUIRE_MESSAGE(current_test_passing(),
                          "\n    PARSED AST = '\n" << parsed_AST << "'");
}


GENERATE_DATASET_TEST_CASE(identifier_list)
GENERATE_DATASET_TEST_CASE(based_literal)
GENERATE_DATASET_TEST_CASE(decimal_literal)
GENERATE_DATASET_TEST_CASE(bit_string_literal)
GENERATE_DATASET_TEST_CASE(abstract_literal)
GENERATE_DATASET_TEST_CASE(physical_literal)


/*
 * physical_literal_failure
 */
struct physical_literal_failure_dataset : public testsuite::vhdl_parser::util::dataset_loader
{
    physical_literal_failure_dataset()
    : dataset_loader{ "test_case/physical_literal_failure" }
    { }
} const physical_literal_failure_dataset;


BOOST_DATA_TEST_CASE( physical_literal_failure,
      physical_literal_failure_dataset.input()
    ^ physical_literal_failure_dataset.expect()
    ^ physical_literal_failure_dataset.test_case_name(),
    VHDL_code, expect_AST, test_case)
{
    using attribute_type = ast::physical_literal;
    auto const parser = parser::physical_literal;

    boost::ignore_unused(test_case);

    using testsuite::vhdl_parser::util::testing_parser;
    using testsuite::vhdl_parser::util::current_test_passing;

    testing_parser<attribute_type> parse;
    auto [parse_ok, parsed_AST] = parse(VHDL_code, parser);

    BOOST_TEST(!parse_ok);
    BOOST_REQUIRE_MESSAGE(current_test_passing(),
                          "\n    PARSED AST = '\n" << parsed_AST << "'");

    BOOST_TEST(parsed_AST == expect_AST, btt::per_element());
    BOOST_REQUIRE_MESSAGE(current_test_passing(),
                          "\n    PARSED AST = '\n" << parsed_AST << "'");
}


GENERATE_DATASET_TEST_CASE(numeric_literal)
GENERATE_DATASET_TEST_CASE(literal)


BOOST_AUTO_TEST_SUITE_END()

