/*
 * parser_concurrent_statements.cpp
 *
 *  Created on: 13.07.2017
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


BOOST_AUTO_TEST_SUITE( concurrent_statements )


GENERATE_DATASET_TEST_CASE(concurrent_assertion_statement)
GENERATE_DATASET_TEST_CASE(concurrent_procedure_call_statement)
GENERATE_DATASET_TEST_CASE(concurrent_signal_assignment_statement)


BOOST_AUTO_TEST_SUITE_END()


