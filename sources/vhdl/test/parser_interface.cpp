/*
 * parser_interface.cpp
 *
 *  Created on: 07.06.2017
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


BOOST_AUTO_TEST_SUITE( interface )


GENERATE_DATASET_TEST_CASE(interface_file_declaration)
GENERATE_DATASET_TEST_CASE(interface_constant_declaration)
GENERATE_DATASET_TEST_CASE(interface_signal_declaration)
GENERATE_DATASET_TEST_CASE(interface_variable_declaration)


BOOST_AUTO_TEST_SUITE_END()



