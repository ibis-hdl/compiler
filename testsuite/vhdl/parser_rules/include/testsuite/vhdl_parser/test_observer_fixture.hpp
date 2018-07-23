/*
 * test_observer_fixture.hpp
 *
 *  Created on: 23.07.2018
 *   Author: olaf
 */

#ifndef TESTSUITE_VHDL_PARSER_RULES_INCLUDE_TESTSUITE_VHDL_PARSER_TEST_OBSERVER_FIXTURE_HPP_
#define TESTSUITE_VHDL_PARSER_RULES_INCLUDE_TESTSUITE_VHDL_PARSER_TEST_OBSERVER_FIXTURE_HPP_


#include <eda/util/compiler_warnings_off.hpp>
#include <boost/test/unit_test.hpp>
#include <boost/test/tree/observer.hpp>
#include <eda/util/compiler_warnings_on.hpp>

#include <testsuite/namespace_alias.hpp>


namespace testsuite { namespace vhdl_parser { namespace util {


class test_observer_fixture
{
	struct test_observer : public utf::test_observer
	{
		// test observer interface
		virtual void test_start(utf::counter_t test_cases_amount) override;
		virtual void test_finish() override;
		virtual void test_aborted() override;

		virtual void test_unit_start(utf::test_unit const& tu) override;
		virtual void test_unit_finish(utf::test_unit const& tu, unsigned long elapsed) override;
		virtual void test_unit_skipped(utf::test_unit const& tu, utf::const_string name) override;
		virtual void test_unit_aborted(utf::test_unit const& tu) override;

		virtual void assertion_result(utf::assertion_result result) override;
		virtual void exception_caught(boost::execution_exception const& e) override;

		virtual int priority() override { return 100; }

		virtual ~test_observer() override;
	};

	test_observer									observer;

public:
	test_observer_fixture();
	~test_observer_fixture();

public:
	void setup();
	void teardown();
};


} } } // namespace testsuite.vhdl_parser.util


#endif /* TESTSUITE_VHDL_PARSER_RULES_INCLUDE_TESTSUITE_VHDL_PARSER_TEST_OBSERVER_FIXTURE_HPP_ */
