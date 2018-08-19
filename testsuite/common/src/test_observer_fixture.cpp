/*
 * test_observer_fixture.cpp
 *
 *  Created on: 23.07.2018
 *      Author: olaf
 */

#include <testsuite/test_observer_fixture.hpp>

#include <eda/compiler/warnings_off.hpp>
#include <boost/test/unit_test.hpp>
#include <boost/test/tree/observer.hpp>
#include <boost/test/execution_monitor.hpp>
#include <boost/test/utils/basic_cstring/io.hpp>
#include <eda/compiler/warnings_on.hpp>


#include <testsuite/namespace_alias.hpp>

#include <iostream>


namespace testsuite {


struct test_observer_fixture::test_observer : public utf::test_observer
{
	bool&											save_diagnostic;

	test_observer(bool& save_diagnostic_)
	: save_diagnostic{ save_diagnostic_ }
	{ }

	virtual ~test_observer() override { }

#if 0
	virtual void test_start(utf::counter_t test_cases_amount) override {
		std::cout << "# start " << test_cases_amount << std::endl;
	}

	virtual void test_finish() override {
		std::cout << "# finish" << std::endl;
	}

	virtual void test_aborted() override {
		std::cout << "# aborted" << std::endl;
	}

	virtual void test_unit_start(utf::test_unit const& tu) override {
		std::cout << "# unit_start " << tu.p_id << std::endl;
	}

	virtual void test_unit_finish(utf::test_unit const& tu, unsigned long elapsed) override {
		std::cout << "# unit_finish " << tu.p_id << " " << elapsed << std::endl;
	}

	virtual void test_unit_skipped(utf::test_unit const& tu, utf::const_string name) override {
		std::cout << "# unit_skipped " << tu.p_id << "(" << name << ")" << std::endl;
	}

	virtual void test_unit_aborted(utf::test_unit const& tu) override {
		std::cout << "# unit_aborted " << tu.p_id << std::endl;
	}
#endif

	virtual void test_unit_start(utf::test_unit const& tu) override;
	virtual void test_unit_finish(utf::test_unit const& tu, unsigned long elapsed) override;

	virtual void assertion_result(utf::assertion_result result) override;
	virtual void exception_caught(boost::execution_exception const& e) override;

	virtual int priority() override { return 100; }
};


/*
 * https://github.com/boostorg/test/tree/develop/include/boost/test/impl
 * https://github.com/djeedjay/BoostTestUi/blob/master/BoostTestSample/unit_test_gui.hpp
 * https://github.com/PLLUG/boost/blob/master/libs/test/test/test-organization-ts/test_unit-order-test.cpp
 */
void test_observer_fixture::test_observer::test_unit_start(utf::test_unit const& tu) {
	std::cout << "# unit_start " << tu.p_id << std::endl;
	save_diagnostic = false;
}

void test_observer_fixture::test_observer::test_unit_finish(utf::test_unit const& tu, unsigned long elapsed) {
	std::cout << "# unit_finish " << tu.p_id << " " << elapsed << std::endl;
}

void test_observer_fixture::test_observer::assertion_result(utf::assertion_result result)
{
	std::cout << "# assertion ";
    switch( result ) {
		case utf::AR_PASSED:{
		    std::cout << "passed";
		    break;
		}
		case utf::AR_FAILED: {
		    auto const& test_case = utf::framework::current_test_case();
		    std::cout << "failed: " << test_case.full_name();
		    save_diagnostic = true;
		    break;
		}
		case utf::AR_TRIGGERED: {
		    std::cout << "triggered";
		    break;
		}
		default:
		    break;
    }
    std::cout << std::endl;
}

void test_observer_fixture::test_observer::exception_caught(boost::execution_exception const& e)
{
	std::cout << "# exception " << e.what() << std::endl;
}


} // namespace testsuite



namespace testsuite {

/*
 * https://www.boost.org/doc/libs/1_67_0/libs/test/doc/html/boost_test/tests_organization/fixtures/global.html
 */
test_observer_fixture::test_observer_fixture()
: save_diagnostic{ true }
, observer{ std::make_unique<test_observer>(save_diagnostic) }
{
	utf::framework::register_observer(*observer);
}

test_observer_fixture::~test_observer_fixture()
{
	utf::framework::deregister_observer(*observer);
}

void test_observer_fixture::setup()
{
    BOOST_TEST_MESSAGE( "## Setup Global Test Observer Fixture" );
}

void test_observer_fixture::teardown()
{
    BOOST_TEST_MESSAGE( "## Teardown Global Test Observer Fixture" );
}

void test_observer_fixture::failure_diagnostic(
    std::string const& test_case_name,
    std::string const& input, std::string const& result)
{
	std::cout << "## test_observer_fixture::failure_diagnostic: "
	          << "save " << (save_diagnostic ? "diagnostic" : "no action") << "\n";
}



} // namespace testsuite
