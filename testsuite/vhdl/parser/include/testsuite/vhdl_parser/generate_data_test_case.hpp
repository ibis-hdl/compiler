/*
 * generate_data_test_case.hpp
 *
 *  Created on: 10.06.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_TEST_INCLUDE_TESTSUITE_VHDL_PARSER_GENERATE_DATA_TEST_CASE_HPP_
#define SOURCES_VHDL_TEST_INCLUDE_TESTSUITE_VHDL_PARSER_GENERATE_DATA_TEST_CASE_HPP_


#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/stringize.hpp>



/**
 * Helper macros to generate the boilerplate for test cases using boost.test's
 * dataset capabilities.
 *
 * The code skelet looks like:
 *
 * \code{.unparsed}
 * struct ${TEST_CASE${SPECIAL}}_dataset : public ::x3_test::dataset_loader
 * {
 *     ${TEST_CASE${SPECIAL}}_dataset()
 *     : dataset_loader{ "test_case/${TEST_CASE${SPECIAL}}" }
 *     { }
 * } const ${TEST_CASE${SPECIAL}}_dataset;
 *
 *
 * BOOST_DATA_TEST_CASE( ${TEST_CASE${SPECIAL}},
 *       ${TEST_CASE${SPECIAL}}_dataset.input()
 *     ^ ${TEST_CASE${SPECIAL}}_dataset.expect(),
 *     input, expect)
 * {
 *     using x3_test::testing_parser;
 *
 *     typedef ast::${TEST_CASE} attribute_type;
 *
 *     testing_parser<attribute_type> parse;
 *     auto [parse_ok, parse_result] = parse(input, parser::${TEST_CASE});
 *
 *     BOOST_TEST(parse_ok);
 *     BOOST_TEST_INFO("ATTR_RESULT = '" << parse_result << "'");
 *     BOOST_TEST(parse_result == expect, btt::per_element());
 * }
 * \endcode
 *
 * where ${TEST_CASE} is replaced by the concrete test case name given as
 * argument and ${SPECIAL} like '_failure' for failure handling tests
 */


/*
 * configuration area
 */

// path to all test cases
#define DATASET_PREFIX_PATH     "test_case/"
// namespace of the ast nodes
#define AST_NAMESPACE           eda::vhdl::ast::
// namespace of the parser
#define PARSER_NAMESPACE        eda::vhdl::parser::



/*
 * Private area
 * Helper macros for generating the BOOST_DATA_TEST_CASE boilerplate
 */

// concat the parser attribute type with ast's namespace defined above
#define ATTRIBUTE_TYPE(type)    AST_NAMESPACE type


// conact the parser rule with parser's namespace defined above
#define RULE_NAME(rule)         PARSER_NAMESPACE rule



// generate common name for the datasets
#define GENERATE_DATASET_NAME(test_case)                                       \
BOOST_PP_CAT(test_case, _dataset)                                              \
/* --- */


// generate common name for the datasets for FALURE tests
#define GENERATE_FAILURE_DATASET_NAME(test_case)                               \
GENERATE_DATASET_NAME((BOOST_PP_CAT(test_case, _failure))                      \
/* --- */


// generate the path name to the test case input files
#define GENERATE_DATASET_TESTINPUT_PATH(test_case)                             \
DATASET_PREFIX_PATH BOOST_PP_STRINGIZE(test_case)                              \
/* --- */


// the dataset class generation
#define GENERATE_DATASET(test_case)                                            \
struct GENERATE_DATASET_NAME(test_case) : public ::x3_test::dataset_loader     \
{                                                                              \
    GENERATE_DATASET_NAME(test_case)()                                         \
    : dataset_loader{ GENERATE_DATASET_TESTINPUT_PATH(test_case) }             \
    { }                                                                        \
} const GENERATE_DATASET_NAME(test_case);                                      \
/* --- */



#define GENERATE_DATASET_TEST_CASE_NAME(test_case)                             \
test_case                                                                      \
/* --- */


// generate the BOOST_DATA_TEST_CASE header part with the dataset
#define GENERATE_DATASET_TEST_CASE_HEADER(test_case)                           \
BOOST_DATA_TEST_CASE( GENERATE_DATASET_TEST_CASE_NAME(test_case),              \
     GENERATE_DATASET_NAME(test_case).input()                                  \
    ^GENERATE_DATASET_NAME(test_case).expect()                                 \
    ^GENERATE_DATASET_NAME(test_case).test_case_name(),                        \
    VHDL_code, expect_AST, test_case_name)                                     \
/* --- */


// generate the BOOST_DATA_TEST_CASE body part with the dataset
#define GENERATE_DATASET_TEST_CASE_BODY(test_case)                             \
{                                                                              \
    using per_element = boost::test_tools::per_element;                        \
    using attribute_type = ATTRIBUTE_TYPE(test_case);                          \
    auto const parser = RULE_NAME(test_case);                                  \
    boost::ignore_unused(test_case_name);                                      \
    x3_test::testing_parser<attribute_type> parse;                             \
    auto [parse_ok, parsed_AST] = parse(VHDL_code, parser);                    \
    BOOST_TEST(parse_ok);                                                      \
    BOOST_REQUIRE_MESSAGE(x3_test::current_test_passing(),                     \
                          "\n    PARSED AST = '\n" << parsed_AST << "'");      \
    BOOST_TEST(parsed_AST == expect_AST, per_element());                       \
    BOOST_REQUIRE_MESSAGE(x3_test::current_test_passing(),                     \
                          "\n    PARSED AST = '\n" << parsed_AST << "'");      \
}                                                                              \
/* --- */


// the final macro to generate the boilerplate
#define GENERATE_DATASET_TEST_CASE(test_case)                                  \
GENERATE_DATASET(test_case)                                                    \
GENERATE_DATASET_TEST_CASE_HEADER(test_case)                                   \
GENERATE_DATASET_TEST_CASE_BODY(test_case)                                     \
/* --- */



#endif /* SOURCES_VHDL_TEST_INCLUDE_TESTSUITE_VHDL_PARSER_GENERATE_DATA_TEST_CASE_HPP_ */
