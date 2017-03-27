/*
 * test_vhdl93.cpp
 *
 *  Created on: 01.03.2017
 *      Author: olaf
 */

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE "VHDL93 Parser Test Suite"
#include <boost/test/included/unit_test.hpp>

#include "app_mock.hpp"

app_mock::app_mock()
: argc(boost::unit_test::framework::master_test_suite().argc)
, argv(boost::unit_test::framework::master_test_suite().argv)
{ }

