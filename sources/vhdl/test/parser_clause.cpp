/*
 * parser_clause.cpp
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


GENERATE_DATASET_TEST_CASE(use_clause)
GENERATE_DATASET_TEST_CASE(port_clause)
GENERATE_DATASET_TEST_CASE(generic_clause)


BOOST_AUTO_TEST_SUITE_END()
