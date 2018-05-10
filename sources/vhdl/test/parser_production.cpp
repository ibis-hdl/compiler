/*
 * parser_production.cpp
 *
 *  Created on: 09.05.2017
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
#include "testing_util.hpp"


BOOST_AUTO_TEST_SUITE( productions )


GENERATE_DATASET_TEST_CASE(function_call)
GENERATE_DATASET_TEST_CASE(indexed_name)
GENERATE_DATASET_TEST_CASE(waveform)
GENERATE_DATASET_TEST_CASE(attribute_name)
GENERATE_DATASET_TEST_CASE(attribute_specification)
GENERATE_DATASET_TEST_CASE(range_constraint)
GENERATE_DATASET_TEST_CASE(index_constraint)
GENERATE_DATASET_TEST_CASE(constraint)
GENERATE_DATASET_TEST_CASE(discrete_range)
GENERATE_DATASET_TEST_CASE(subtype_indication)
GENERATE_DATASET_TEST_CASE(association_list)
GENERATE_DATASET_TEST_CASE(choices)
GENERATE_DATASET_TEST_CASE(assertion)
GENERATE_DATASET_TEST_CASE(parameter_specification)


BOOST_AUTO_TEST_SUITE_END()
