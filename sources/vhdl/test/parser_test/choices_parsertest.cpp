/*
 * choices_parsertest.cpp
 *
 *  Created on: 7.5.2018
 *      Author: olaf
 */


#include <boost/test/unit_test.hpp>

#include <iostream>

#include <eda/vhdl/ast.hpp>
#include "data_set.hpp"
#include "testing_parser.hpp"
#include "testing_parser_grammar_hack.hpp"
#include "generate_data_test_case.hpp"

BOOST_AUTO_TEST_SUITE( choices )



GENERATE_DATASET_TEST_CASE( choices )            

BOOST_AUTO_TEST_SUITE_END()
