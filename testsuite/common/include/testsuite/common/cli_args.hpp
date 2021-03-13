#pragma once

#include <string>

#include <boost/filesystem.hpp>

#include <testsuite/common/namespace_alias.hpp>

namespace testsuite {

///
/// @brief Custom command line arguments fixture
///
/// Boost.UTF allows to apply custom command line arguments to 
/// the test, e.g. for configuration purpose etc. The concept
/// used is described at [Custom command line arguments](
/// https://www.boost.org/doc/libs/1_75_0/libs/test/doc/html/boost_test/runtime_config/custom_command_line_arguments.html)
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
///   if (!cli_args::data.source_dir.empty())
///     std::cout << cli_args::data.source_dir << '\n';
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
/// "/tmp"
/// ...
/// @endcode
///
class cli_args 
{
public:
  static void setup();
  static void teardown();

public:
  static fs::path source_dir() { return data.source_dir; }
  static fs::path destination_dir() { return data.destination_dir; }
  static fs::path input_extension() { return data.input_extension; }
  static fs::path output_extension() { return data.output_extension; }

private:
  static bool parse_cli();
  static void print_settings();

private:
  struct cli_data {
    bool initialized{false};
    fs::path source_dir;
    fs::path destination_dir;
    std::string input_extension;
    std::string output_extension;
  };
  static cli_data data; // NOLINT(cppcoreguidelines-avoid-non-const-global-variables)
};

} // namespace testsuite
