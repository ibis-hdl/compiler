/*
 * test_vhdl.cpp
 *
 *  Created on: 01.03.2017
 *      Author: olaf
 */

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE "VHDL Parser Test Suite"
#include <eda/compiler/warnings_off.hpp>
#include <boost/test/included/unit_test.hpp>
#include <eda/compiler/warnings_on.hpp>

#include <testsuite/vhdl_parser/test_observer_fixture.hpp>

/* Directly use of 'testsuite::...::test_observer_fixture' doesn't compile */
using test_observer_fixture = testsuite::vhdl_parser::util::test_observer_fixture;

BOOST_TEST_GLOBAL_FIXTURE(test_observer_fixture);
