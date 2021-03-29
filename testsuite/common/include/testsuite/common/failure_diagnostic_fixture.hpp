#pragma once

#include <string_view>
#include <filesystem>

#include <testsuite/common/namespace_alias.hpp>  // IWYU pragma: keep

namespace testsuite {

///
/// @brief Boost.Test failure diagnostic fixture
///
/// On failed test cases saves the test case data to file system.
///
/*
    COMMAND
        ${PROJECT_NAME} --
        --source-dir=${PROJECT_SOURCE_DIR}
        --destination-dir=${PROJECT_BINARY_DIR}
        --input-extension=.input
    #    --write-extension=.expected
        --write-extension=.result
*/
class failure_diagnostic_fixture {
public:
    ///
    /// @brief Setup the Fixture
    ///
    /// For writer functionality it checks for "destination-dir" and
    /// "output-extension" command line arguments. Empty cli arguments
    /// are replaced with the builtin defaults. This function shall
    /// be overriden by derived classes to get other bultin compiled
    /// defaults.
    ///
    /// @see \ref cli_args
    ///
    virtual void setup();

    ///
    /// @brief Tear down the Fixture.
    ///
    virtual void teardown();

    failure_diagnostic_fixture() = default;
    failure_diagnostic_fixture(failure_diagnostic_fixture const&) = delete;
    failure_diagnostic_fixture(failure_diagnostic_fixture&&) = delete;
    failure_diagnostic_fixture& operator=(failure_diagnostic_fixture const&) = delete;
    failure_diagnostic_fixture& operator=(failure_diagnostic_fixture&&) = delete;

    virtual ~failure_diagnostic_fixture() {}

public:
    ///
    /// @brief Detect if boost test case failed
    ///
    /// @return true if test unit passed
    /// @return false if test unit failed
    /// @see [Detect if boost test case failed](
    ///  https://stackoverflow.com/questions/18466857/detect-if-boost-test-case-failed?answertab=active#tab-top)
    static bool current_test_passing();

    ///
    /// @brief Writes the test completion to the file system
    /// for later investigation for the causes
    ///
    /// @param test_case_name The name of the current test case.
    /// @param test_input The input string given to th test
    /// @param test_result The output string get from test back.
    ///
    void failure_closure(std::string test_case_name, std::string_view test_input,
                         std::string_view test_result);

protected:
    fs::path destination_dir;
    std::string output_extension;
    std::string fixture_name{ "failure_diagnostic_fixture" };

private:
    class writer;
};

}  // namespace testsuite
