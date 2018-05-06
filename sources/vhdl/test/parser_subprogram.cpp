/*
 * parser_subprogram.cpp
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
#include "testing_parser_def.hpp"
#include "generate_data_test_case.hpp"


BOOST_AUTO_TEST_SUITE( parser_subprogram )


GENERATE_DATASET_TEST_CASE(subprogram_specification)
GENERATE_DATASET_TEST_CASE(subprogram_body)


BOOST_AUTO_TEST_SUITE_END()


