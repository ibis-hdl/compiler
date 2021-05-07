#pragma once

#include <string>

namespace testsuite::util {

///
/// @brief Custom command line arguments
///
/// Boost.Test allows to apply custom command line arguments to
/// the test, e.g. for configuration purpose etc. The concept
/// used is described at Boost.Test page
/// [Custom command line arguments](
/// https://www.boost.org/doc/libs/1_75_0/libs/test/doc/html/boost_test/runtime_config/custom_command_line_arguments.html).
///
/// This auxiliary class serves as a catch-all for all CLI options that arise with the test suites
/// and their fixtures etc. Each component that uses this class selects the one it needs.
///
/// The usage on implementation side is quite simple:
///
/// FixMe: API is obsolete
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
    ///
    /// The given "source_dir" option from cli for dataset loader.
    ///
    /// @return fs::path to the source_dir in canonical form if the given
    /// path does exist and is a valid directory. Otherwise the path is
    /// empty. If no cli option was given the return fs::path is also empty.
    ///
    static std::string source_dir();

    ///
    /// The given "input_extension" option from cli for dataset loader.
    ///
    /// @return std::string of "input_extension" option if given from cli,
    /// otherwise an empty string. No checks are performed.
    ///
    static std::string input_extension();

    ///
    /// The given "expected_extension" option from cli for dataset loader.
    ///
    /// @return std::string of "expected_extension" option if given from cli,
    /// otherwise an empty string. No checks are performed.
    ///
    static std::string expected_extension();

    ///
    /// The given "destination_dir" option from cli for failure diagnostic fixture.
    ///
    /// @return fs::path to the destination_dir in canonical form if the given
    /// path does exist and is a valid directory. If the destination_dir doesn't
    /// exist it will be created. If creation was failed or no cli option was
    /// given the return fs::path is empty.
    ///
    static std::string destination_dir();

    ///
    /// The given "output_extension" option from cli for failure diagnostic fixture.
    ///
    /// @return std::string of "output_extension" option if given from cli,
    /// otherwise an empty string. No checks are performed.
    ///
    static std::string output_extension();

    ///
    /// The given "verbose_diagnostic" option from cli for failure diagnostic fixture.
    ///
    /// @return bool of "verbose_diagnostic" option if given from cli. No checks are performed.
    ///
    static bool verbose_diagnostic();

    ///
    /// Print the arguments given from command line if any.
    ///
    static void print_settings();

    ///
    /// parse the cli arguments and perform convenience checks on it.
    ///
    static void parse_cli(int const argc, char** const argv);

private:
    ///
    /// The data parsed from CLI and flag internally used for caching.
    ///
    struct cli_data {
        bool initialized = false;
        // Dataset loader
        std::string source_dir;
        std::string input_extension;
        std::string expected_extension;
        // Failure Diagnostic Fixture
        std::string destination_dir;
        std::string output_extension;
        bool verbose_diagnostic = false;
    };

    // NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
    static cli_data data;
};

}  // namespace testsuite::util
