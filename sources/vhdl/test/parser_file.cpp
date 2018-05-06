/*
 * parser_file.cpp
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


BOOST_AUTO_TEST_SUITE( file )


GENERATE_DATASET_TEST_CASE(file_declaration)
GENERATE_DATASET_TEST_CASE(file_open_information)


BOOST_AUTO_TEST_SUITE_END()

