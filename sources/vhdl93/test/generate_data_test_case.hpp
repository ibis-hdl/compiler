/*
 * generate_data_test_case.hpp
 *
 *  Created on: 10.06.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL93_TEST_GENERATE_DATA_TEST_CASE_HPP_
#define SOURCES_VHDL93_TEST_GENERATE_DATA_TEST_CASE_HPP_


#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/stringize.hpp>



/**
 * Helper macros to generate the boilerplate for test cases using boost.test's
 * dataset capabilities.
 *
 * The code skelet looks like:
 *
 * \code{.unparsed}
 * struct ${TEST_CASE}_dataset : public ::x3_test::dataset_loader
 * {
 *     ${TEST_CASE}_dataset()
 *     : dataset_loader{ "test_case/${TEST_CASE}" }
 *     { }
 * } const ${TEST_CASE}_dataset;
 *
 *
 * BOOST_DATA_TEST_CASE( ${TEST_CASE},
 *       ${TEST_CASE}_dataset.input()
 *     ^ ${TEST_CASE}_dataset.expect()
 *     ^ ${TEST_CASE}_dataset.test_file_name(),
 *     input, expect, file)
 * {
 *     using x3_test::testing_parser;
 *
 *     typedef ast::${TEST_CASE} attribute_type;
 *
 *     // avoid warning, used in case of error for error message by boost.test
 *     boost::ignore_unused(file);
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
 * argument.
 */


/*
 * configuration area
 */

// path to all test cases
#define DATASET_PREFIX_PATH     test_case
// namespace of the ast nodes
#define AST_NAMESPACE           ast::
// namespace of the parser
#define PARSER_NAMESPACE        parser::



/*
 * Private area
 * Helper macros for generating the BOOST_DATA_TEST_CASE boilerplate
 */

// generate common name for the datasets
#define GENERATE_DATASET_NAME(test_case)                                       \
BOOST_PP_CAT(test_case, _dataset)                                              \
/* --- */


// the dataset class generation
#define GENERATE_DATASET(test_case)                                            \
struct GENERATE_DATASET_NAME(test_case) : public ::x3_test::dataset_loader     \
{                                                                              \
    GENERATE_DATASET_NAME(test_case)()                                         \
    : dataset_loader{ "test_case/" BOOST_PP_STRINGIZE(test_case) }             \
    { }                                                                        \
} const GENERATE_DATASET_NAME(test_case);                                      \
/* --- */


// concat the parser attribute type with ast's namespace defined above
#define ATTRIBUTE_TYPE(type)    AST_NAMESPACE type


// conact the parser rule with parser's namespace defined above
#define RULE_NAME(rule)         PARSER_NAMESPACE rule


// generate the BOOST_DATA_TEST_CASE header part with the dataset
#define GENERATE_DATASET_TEST_CASE_HEADER(test_case)                           \
BOOST_DATA_TEST_CASE( test_case,                                               \
     GENERATE_DATASET_NAME(test_case).input()                                  \
    ^GENERATE_DATASET_NAME(test_case).expect()                                 \
    ^GENERATE_DATASET_NAME(test_case).test_file_name(),                        \
    input, expect, file)                                                       \
/* --- */


// generate the BOOST_DATA_TEST_CASE body part with the dataset
#define GENERATE_DATASET_TEST_CASE_BODY(test_case)                             \
{                                                                              \
    using x3_test::testing_parser;                                             \
    typedef ATTRIBUTE_TYPE(test_case) attribute_type;                          \
    boost::ignore_unused(file);                                                \
    testing_parser<attribute_type> parse;                                      \
    auto [parse_ok, parse_result] = parse(input, RULE_NAME(test_case));        \
    BOOST_TEST(parse_ok);                                                      \
    BOOST_TEST_INFO("ATTR_RESULT = '" << parse_result << "'");                 \
    BOOST_TEST(parse_result == expect, btt::per_element());                    \
}                                                                              \
/* --- */


// the final macro to generate the boilerplate
#define GENERATE_DATASET_TEST_CASE(test_case)                                  \
GENERATE_DATASET(test_case)                                                    \
GENERATE_DATASET_TEST_CASE_HEADER(test_case)                                   \
GENERATE_DATASET_TEST_CASE_BODY(test_case)                                     \
/* --- */


#endif /* SOURCES_VHDL93_TEST_GENERATE_DATA_TEST_CASE_HPP_ */
