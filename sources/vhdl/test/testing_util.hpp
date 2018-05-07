/*
 * testing_util.hpp
 *
 *  Created on: 07.05.2018
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_TEST_TESTING_UTIL_HPP_
#define SOURCES_VHDL_TEST_TESTING_UTIL_HPP_

#include <boost/test/results_collector.hpp>


namespace x3_test {


/**
 * [Detect if boost test case failed](
 *  https://stackoverflow.com/questions/18466857/detect-if-boost-test-case-failed?answertab=active#tab-top)
 */
static inline
bool current_test_passing()
{
  using namespace boost::unit_test;
  auto const id = framework::current_test_case().p_id;
  auto const test_results = results_collector.results(id);
  return test_results.passed();
}


} // namespace x3_test


#endif /* SOURCES_VHDL_TEST_TESTING_UTIL_HPP_ */
