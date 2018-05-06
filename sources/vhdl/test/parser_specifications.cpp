/*
 * parser_declaration.cpp
 *
 *  Created on: 11.06.2017
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


BOOST_AUTO_TEST_SUITE( parser_specifications )


GENERATE_DATASET_TEST_CASE(disconnection_specification)
GENERATE_DATASET_TEST_CASE(binding_indication)
GENERATE_DATASET_TEST_CASE(component_specification)


BOOST_AUTO_TEST_SUITE_END()



