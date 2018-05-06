/*
 * parser_design_unit.cpp
 *
 *  Created on: 08.07.2017
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


BOOST_AUTO_TEST_SUITE( parser_design_unit )


GENERATE_DATASET_TEST_CASE(library_clause)
GENERATE_DATASET_TEST_CASE(context_clause)


BOOST_AUTO_TEST_SUITE_END()





