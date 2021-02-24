/*
 * store_fixture.hpp
 *
 *  Created on: 19.08.2018
 *      Author: olaf
 */

#ifndef TESTSUITE_COMMON_INCLUDE_TESTSUITE_COMMON_FAILURE_DIAGNOSTIC_FIXTURE_HPP_
#define TESTSUITE_COMMON_INCLUDE_TESTSUITE_COMMON_FAILURE_DIAGNOSTIC_FIXTURE_HPP_

#include <string>


namespace testsuite {


/**
 * Boost.Test failure diagnostic fixture
 *
 * On failed test cases saves the test case data to file system.
 */
class failure_diagnostic_fixture
{
public:
    void setup();
    void teardown();

public:
    bool current_test_passing() const;

    void failure_closure (
        std::string const& test_case_name,
        std::string const& input,
        std::string const& result
    ) const;

private:
    class writer;
};

} // namespace testsuite


#endif /* TESTSUITE_COMMON_INCLUDE_TESTSUITE_COMMON_FAILURE_DIAGNOSTIC_FIXTURE_HPP_ */
