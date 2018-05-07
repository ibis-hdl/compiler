/*
 * disconnection_specification_parsertest.cpp
 *
 *  Created on: 7.5.2018
 *      Author: olaf
 */


#include <boost/test/unit_test.hpp>
#include <boost/core/ignore_unused.hpp>

#include <iostream>

#include <eda/vhdl/ast.hpp>
#include "data_set.hpp"
#include "testing_parser.hpp"
#include "testing_parser_grammar_hack.hpp"
#include "generate_data_test_case.hpp"
#include "testing_util.hpp"

BOOST_AUTO_TEST_SUITE( disconnection_specification )



GENERATE_DATASET_TEST_CASE( disconnection_specification )            

BOOST_AUTO_TEST_SUITE_END()
