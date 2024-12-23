//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-or-later
//

#pragma once

#include <string_view>
#include <filesystem>
#include <memory>

#include <testsuite/namespace_alias.hpp>  // IWYU pragma: keep

namespace testsuite {
    namespace fs = std::filesystem;
}

namespace testsuite::util {

///
/// @brief Boost.Test failure diagnostic fixture basic functionality.
///
/// On failed test cases saves the test case data to file system.
///
/// FixMe: written to fs::path(destination_dir) / "test_case" / testcase_name;
/// Make the path to the destination/write folder configurable, also the file
/// extension for the result.
//
//  COMMAND
//      ${PROJECT_NAME} --
//      --source-dir=${PROJECT_SOURCE_DIR}
//      --destination-dir=${PROJECT_BINARY_DIR}
//      --input-extension=.input
//      --write-extension=.result
//
/// @todo At this time, input, expected and output result are captured. Save the difference as
/// unified format for convenience, using [cubicdaiya/dtl](https://github.com/cubicdaiya/dtl)
/// doesn't work since it's on character level.
/// [leutloff/diff-match-patch-cpp-stl](https://github.com/leutloff/diff-match-patch-cpp-stl) based
/// on [google/diff-match-patch](https://github.com/google/diff-match-patch) also doesn't bring the
/// expected output. Maybe the simplest is to call diff on unix via external process. Windows will
/// lose.
///
/// @todo Also useful information to store on filesystem are the messages,
/// maybe [Observing test failure messages](
///  https://stackoverflow.com/questions/56963902/observing-test-failure-messages/61371602#61371602)
/// is the right way for this. See
/// [github](https://github.com/boostorg/test/blob/boost-1.76.0/include/boost/test/impl/plain_report_formatter.ipp)
///
class basic_failure_diagnostic_fixture {
public:
    ///
    /// @brief Setup the Fixture, follows Boost.Test Fixture API.
    ///
    virtual void setup();

    ///
    /// @brief Tear down the Fixture, follows Boost.Test Fixture API.
    ///
    virtual void teardown();

    explicit basic_failure_diagnostic_fixture();
    virtual ~basic_failure_diagnostic_fixture() = default;

    basic_failure_diagnostic_fixture(basic_failure_diagnostic_fixture const&) = delete;
    basic_failure_diagnostic_fixture(basic_failure_diagnostic_fixture&&) = delete;
    basic_failure_diagnostic_fixture& operator=(basic_failure_diagnostic_fixture const&) = delete;
    basic_failure_diagnostic_fixture& operator=(basic_failure_diagnostic_fixture&&) = delete;

public:
    ///
    /// @brief Detect if boost test case failed.
    ///
    /// @return true if test unit passed
    /// @return false if test unit failed
    /// @see [Detect if boost test case failed](
    ///  https://stackoverflow.com/questions/18466857/detect-if-boost-test-case-failed?answertab=active#tab-top)
    ///
    static bool current_test_passing();

    ///
    /// @brief Writes the test completion to the file system
    /// for later investigation for the causes.
    ///
    /// @param test_case_name The name of the current test case.
    /// @param test_input The input string given to th test
    /// @param test_result The output string get from test back.
    ///
    void failure_closure(std::string test_case_name,  // --
                         std::string_view test_input, std::string_view test_result);

    ///
    /// @brief Writes the test completion to the file system
    /// for later investigation for the causes.
    ///
    /// @param test_case_name The name of the current test case.
    /// @param test_input The input string given to the test
    /// @param test_expected The expected string given to the test
    /// @param test_result The output string get from test back.
    ///
    void failure_closure(std::string test_case_name,  // --
                         std::string_view test_input, std::string_view test_expected,
                         std::string_view test_result);

protected:
    ///
    /// The compiled builtin defaults, used if no CLI argument was given.
    ///
    // NOLINTNEXTLINE(cppcoreguidelines-special-member-functions) -- due to abstract class!
    struct compile_builtin {
        compile_builtin() = default;
        virtual ~compile_builtin();

        compile_builtin(compile_builtin&) = delete;
        compile_builtin(compile_builtin&&) = delete;

        virtual std::string_view input_extension() const = 0;
        virtual std::string_view expected_extension() const = 0;

        virtual std::string_view destination_dir() const = 0;
        virtual std::string_view output_extension() const = 0;
    };

    ///
    /// Set the builtin object
    ///
    /// @param other The bultin object intended to replace the current one.
    ///
    void set_builtin(std::unique_ptr<compile_builtin> other);

    ///
    /// Set the name of the fixture
    ///
    /// @param name of the fixture
    ///
    void set_name(std::string_view name) { fixture_name = name; }

private:
    /// Parse CLI arguments and if not given replace them with compile builtin values.
    void check_args();

    /// The name of the fixture for logging.
    std::string_view name() const;

    /// furnish a nice line with title in the middle
    static void head_line(std::ostream& os, std::string_view title, std::size_t col_width,
                          char fill);

private:
    ///
    /// @brief Member function to write the contents of result
    /// into filesystem.
    ///
    /// @param full_pathname holds the path/filename to write to
    /// @param result holds the data to be written.
    ///
    void write(fs::path const& full_pathname, std::string_view result);

    ///
    /// @brief Create a directory object
    ///
    /// @param write_path for the file to write. If the path doesn't exist
    /// it is created.
    /// @return true on success, directory does exist or is created successfull.
    /// @return false on failure on creating the directory.
    ///
    bool create_directories(fs::path const& write_path);

    ///
    /// @brief Write the contents into file.
    ///
    /// If a file with the same name exist it will be removed from
    /// filesstem and new created.
    ///
    /// @param filename is the name of the file to be written.
    /// @param contents to be written.
    /// @return true if successfully written.
    /// @return false on failure.
    ///
    bool write_file(fs::path const& filename, std::string_view contents);

private:
    std::unique_ptr<compile_builtin> builtin;

    std::string input_extension;
    std::string expected_extension;

    fs::path destination_dir;
    std::string output_extension;

    std::string fixture_name;
};

}  // namespace testsuite::util
