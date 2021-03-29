#pragma once

#include <string>
#include <filesystem>

#include <testsuite/common/namespace_alias.hpp>  // IWYU pragma: keep

namespace testsuite {

///
/// @brief Custom command line arguments fixture
///
/// Boost.UTF allows to apply custom command line arguments to
/// the test, e.g. for configuration purpose etc. The concept
/// used is described at Boost.UTF page
/// [Custom command line arguments](
/// https://www.boost.org/doc/libs/1_75_0/libs/test/doc/html/boost_test/runtime_config/custom_command_line_arguments.html).
///
/// This auxiliary class serves as a catch-all for all CLI options that arise with the test suites
/// and their fixtures etc. Each component that uses this class selects the one it needs.
///
/// The usage on implementation side is quite simple:
///
/// @code{.cpp}
/// using testsuite::cli_args;
///
/// BOOST_TEST_GLOBAL_FIXTURE(cli_args);
///
/// BOOST_AUTO_TEST_CASE(check_device_has_meaningful_name) {
///   BOOST_TEST(true);
///   if (!cli_args::source_dir().empty())
///     std::cout << "cli args: " << cli_args::source_dir() << '\n';
/// }
/// @endcode
///
/// also on user side:
///
/// @code{.unparsed}
/// $ ./cli_args_test -- --help
/// Running 1 test case...
/// Boost.UTF cli arg fixture
/// Usage: ./cli_args_test [OPTIONS]
///
/// Options:
///   -h,--help                   Print this help message and exit
///   -I,--source-dir TEXT        the source directory of test files to be read
///   -O,--destination-dir TEXT   the destination directory of test files to be written
///   -i,--input-extension TEXT   file extension to be read from source-dir
///   -o,--output-extension TEXT  file extension to be written to destination-dir
///
/// $ ./cli_args_test -- --source-dir=/tmp
/// Running 1 test case...
/// cli args: "/tmp"
/// ...
/// @endcode
///
class cli_args {
public:
    static void setup();
    static void teardown();

public:
    ///
    /// @brief The given "source_dir" option from cli
    ///
    /// @return fs::path to the source_dir in canonical form if the given
    /// path does exist and is a valid directory. Otherwise the path is
    /// empty. If no cli option was given the return fs::path is also empty.
    ///
    static fs::path source_dir() { return data.source_dir; }

    ///
    /// @brief The given "destination_dir" option from cli
    ///
    /// @return fs::path to the destination_dir in canonical form if the given
    /// path does exist and is a valid directory. If the destination_dir doesn't
    /// exist it will be created. If creation was failed or no cli option was
    /// given the return fs::path is empty.
    ///
    static fs::path destination_dir() { return data.destination_dir; }

    ///
    /// @brief The given "input_extension" option from cli
    ///
    /// @return std::string of "input_extension" option if given from cli,
    /// otherwise an empty string. No checks are performed.
    ///
    static std::string input_extension() { return data.input_extension; }

    ///
    /// @brief The given "expected_extension" option from cli
    ///
    /// @return std::string of "expected_extension" option if given from cli,
    /// otherwise an empty string. No checks are performed.
    ///
    static std::string expected_extension() { return data.expected_extension; }

    ///
    /// @brief The given "output_extension" option from cli
    ///
    /// @return std::string of "output_extension" option if given from cli,
    /// otherwise an empty string. No checks are performed.
    ///
    static std::string output_extension() { return data.output_extension; }

private:
    ///
    /// @brief parse the cli arguments and perform convenience checks on it.
    ///
    /// @return true on success
    /// @return false on failure of parsing the command line.
    ///
    static bool parse_cli();

    ///
    /// @brief Print the arguments given from command line if any
    ///
    static void print_settings();

private:
    struct cli_data {
        bool initialized{ false };
        fs::path source_dir;
        fs::path destination_dir;
        std::string input_extension;
        std::string expected_extension;
        std::string output_extension;
    };

    // NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
    static cli_data data;
};

}  // namespace testsuite
