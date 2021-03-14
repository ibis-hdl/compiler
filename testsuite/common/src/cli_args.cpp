#include <testsuite/common/cli_args.hpp>

#include <iostream>

#include <boost/test/unit_test.hpp>

#include <CLI/CLI.hpp>

namespace testsuite {

// NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
cli_args::cli_data cli_args::data;

void cli_args::setup()
{
  BOOST_TEST_MESSAGE("INFO: cli_args::setup()");
  if (data.initialized) {
    return;
  }

  BOOST_REQUIRE(parse_cli());

  print_settings();

  data.initialized = true;
}

void cli_args::teardown() { BOOST_TEST_MESSAGE("INFO: cli_args::teardown()"); }

bool cli_args::parse_cli()
{
  int const argc = boost::unit_test::framework::master_test_suite().argc;
  char** const argv = boost::unit_test::framework::master_test_suite().argv;

  CLI::App app("Boost.UTF cli arg fixture");

  // Note: CLI11 validators aren't used here, since the message isn't intuitive:
  // e.g.: Error occurred during parsing CLI: ValidationError
  app.add_option("-I,--source-dir", data.source_dir)
      ->description("the source directory of test files to be read");
  app.add_option("-O,--destination-dir", data.destination_dir)
      ->description("the destination directory of test files to be written");
  app.add_option("-i,--input-extension", data.input_extension)
      ->description("file extension to be read from source-dir");
  app.add_option("-o,--output-extension", data.output_extension)
      ->description("file extension to be written to destination-dir");

  try {
    app.parse(argc, argv);
  }
  catch (const CLI::CallForHelp& e) {
    // strange call with the intend of help ...
    std::exit(app.exit(e));
    return true;
  }
  catch (const CLI::ParseError& e) {
    BOOST_TEST_ERROR("Error occurred during parsing CLI: " << e.get_name());
    return false;
  }

  if (app.count("--source-dir") != 0) {
    if (fs::exists(data.source_dir) && fs::is_directory(data.source_dir)) {
      data.source_dir = fs::canonical(data.source_dir);
    }
    else {
      BOOST_TEST_ERROR("source-dir " << data.source_dir << " doesn't exist!");
      data.source_dir = fs::path{};  // clear wrong path if failed
    }
  }
  if (app.count("--destination-dir") != 0) {
    if (fs::exists(data.destination_dir)) {
      data.destination_dir = fs::canonical(data.destination_dir);
    }
    else {
      // create if not exist
      if (fs::create_directory(data.destination_dir)) {
        BOOST_TEST_MESSAGE("destination directory " << data.destination_dir << " created!");
        data.destination_dir = fs::canonical(data.destination_dir);
      }
      else {
        BOOST_TEST_ERROR("unable to create destination directory " << data.destination_dir);
        data.destination_dir = fs::path{};  // clear wrong path if failed
      }
    }
  }

  return true;
}

void cli_args::print_settings()
{
  if (!data.source_dir.empty()) {
    BOOST_TEST_MESSAGE("source directory " << data.source_dir);
  }
  if (!data.destination_dir.empty()) {
    BOOST_TEST_MESSAGE("destination directory " << data.destination_dir);
  }
  if (!data.input_extension.empty()) {
    BOOST_TEST_MESSAGE("input file extension '" << data.input_extension << "'");
  }
  if (!data.output_extension.empty()) {
    BOOST_TEST_MESSAGE("output file extension '" << data.output_extension << "'");
  }
}

}  // namespace testsuite
