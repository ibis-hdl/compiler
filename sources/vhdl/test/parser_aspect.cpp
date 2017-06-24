/*
 * parser_aspect.cpp
 *
 *  Created on: 09.06.2017
 *      Author: olaf
 */


#include <boost/test/unit_test.hpp>
#include <boost/core/ignore_unused.hpp>

#include <iostream>

#include <eda/vhdl/ast.hpp>
#include "data_set.hpp"
#include "testing_parser.hpp"
#include "generate_data_test_case.hpp"

BOOST_AUTO_TEST_SUITE( clause )


GENERATE_DATASET_TEST_CASE(generic_map_aspect)
GENERATE_DATASET_TEST_CASE(port_map_aspect)
GENERATE_DATASET_TEST_CASE(entity_aspect)


BOOST_AUTO_TEST_SUITE_END()
