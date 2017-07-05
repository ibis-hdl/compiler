/*
 * parser_names.cpp
 *
 *  Created on: 05.07.2017
 *      Author: olaf
 */



#include <boost/test/unit_test.hpp>
#include <boost/core/ignore_unused.hpp>

#include <iostream>

#include <eda/vhdl/ast.hpp>
#include "data_set.hpp"
#include "testing_parser.hpp"
#include "generate_data_test_case.hpp"


BOOST_AUTO_TEST_SUITE( parser_names )


GENERATE_DATASET_TEST_CASE(slice_name)


BOOST_AUTO_TEST_SUITE_END()




