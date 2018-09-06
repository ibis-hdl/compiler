/*
 * test_ast.cpp
 *
 *  Created on: 05.09.2018
 *      Author: olaf
 */

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE "VHDL AST Test Suite"
#include <eda/compiler/warnings_off.hpp>            // IWYU pragma: keep
#include <boost/test/included/unit_test.hpp>        // IWYU pragma: keep
#include <eda/compiler/warnings_on.hpp>             // IWYU pragma: keep

#include <testsuite/position_cache_fixture.hpp>

using position_cache_fixture = testsuite::position_cache_fixture;

BOOST_GLOBAL_FIXTURE(position_cache_fixture);
