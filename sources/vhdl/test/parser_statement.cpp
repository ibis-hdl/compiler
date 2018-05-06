/*
 * parser_statement.cpp
 *
 *  Created on: 05.06.2017
 *      Author: olaf
 */

#include <boost/test/unit_test.hpp>
#include <boost/core/ignore_unused.hpp>

#include <iostream>

#include <eda/vhdl/ast.hpp>
#include "data_set.hpp"
#include "testing_parser.hpp"
#include "testing_parser_def.hpp"
#include "generate_data_test_case.hpp"


BOOST_AUTO_TEST_SUITE( productions )


GENERATE_DATASET_TEST_CASE(case_statement)
GENERATE_DATASET_TEST_CASE(exit_statement)
GENERATE_DATASET_TEST_CASE(next_statement)
GENERATE_DATASET_TEST_CASE(return_statement)
GENERATE_DATASET_TEST_CASE(signal_assignment_statement)
GENERATE_DATASET_TEST_CASE(variable_assignment_statement)
GENERATE_DATASET_TEST_CASE(wait_statement)
GENERATE_DATASET_TEST_CASE(sequential_statement)
GENERATE_DATASET_TEST_CASE(if_statement)
GENERATE_DATASET_TEST_CASE(loop_statement)
GENERATE_DATASET_TEST_CASE(selected_signal_assignment)
GENERATE_DATASET_TEST_CASE(conditional_signal_assignment)


BOOST_AUTO_TEST_SUITE_END()

