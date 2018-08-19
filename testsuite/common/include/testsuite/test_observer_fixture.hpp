/*
 * test_observer_fixture.hpp
 *
 *  Created on: 23.07.2018
 *   Author: olaf
 */

#ifndef TESTSUITE_VHDL_PARSER_RULES_INCLUDE_TESTSUITE_VHDL_PARSER_TEST_OBSERVER_FIXTURE_HPP_
#define TESTSUITE_VHDL_PARSER_RULES_INCLUDE_TESTSUITE_VHDL_PARSER_TEST_OBSERVER_FIXTURE_HPP_

#include <memory>


namespace testsuite {


/**
 * Global Boost.Test observer fixture
 *
 * Capture all Boost.Test relevant events and handle them, especially failed
 * test cases to save the generated data to file system.
 */
class test_observer_fixture
{
	bool											save_diagnostic;

	struct test_observer;

	/** pimpl idiom, since used once at each test suite */
	std::unique_ptr<test_observer>					observer;

public:
	test_observer_fixture();
	~test_observer_fixture();

public:
	void setup();
	void teardown();

public:
	void failure_diagnostic(
	    std::string const& test_case_name,
	    std::string const& input,
	    std::string const& result
	);
};


} // namespace testsuite

#endif /* TESTSUITE_VHDL_PARSER_RULES_INCLUDE_TESTSUITE_VHDL_PARSER_TEST_OBSERVER_FIXTURE_HPP_ */
