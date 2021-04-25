#include <testsuite/util/cli_args.hpp>
#include <testsuite/namespace_alias.hpp>  /// IWYU pragma: keep

#include <CLI/App.hpp>
#include <CLI/Error.hpp>
#include <CLI/Option.hpp>
#include <CLI/Formatter.hpp>  // IWYU pragma: keep
#include <CLI/Config.hpp>     // IWYU pragma: keep

#include <cstdlib>
#include <sstream>
#include <filesystem>
#include <iostream>

namespace testsuite::util {

// _NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
cli_args::cli_data cli_args::data;

std::string cli_args::source_dir()
{
    // BOOST_TEST_REQUIRE(data.initialized);
    return data.source_dir;
}

std::string cli_args::destination_dir()
{
    // BOOST_TEST_REQUIRE(data.initialized);
    return data.destination_dir;
}

std::string cli_args::input_extension()
{
    // BOOST_TEST_REQUIRE(data.initialized);
    return data.input_extension;
}

std::string cli_args::expected_extension()
{
    // BOOST_TEST_REQUIRE(data.initialized);
    return data.expected_extension;
}

std::string cli_args::output_extension()
{
    // BOOST_TEST_REQUIRE(data.initialized);
    return data.output_extension;
}

void cli_args::parse_cli(int const argc, char** const argv)
{
    if (data.initialized) {
        return;
    }

    CLI::App app("Boost.UTF cli args");

    //
    // Dataset loader
    //
    auto* dataset_group =
        app.add_option_group("Dataset", "Test Data input sources with their reference files.");

    dataset_group->add_option("-I,--source-dir", data.source_dir)
        ->description("the source directory of test files to be read.");
    dataset_group->add_option("-i,--input-extension", data.input_extension)
        ->description("file extension to be read from source-dir as input.");
    dataset_group->add_option("-e,--expected-extension", data.expected_extension)
        ->description("file extension to be read from source-dir as expected output.");

    //
    // Failure Diagnostic Fixture
    //
    auto* diag_group =
        app.add_option_group("Failure Diagnostic", "On Failure, write output to destination.");

    diag_group->add_option("-O,--destination-dir", data.destination_dir)
        ->description("the destination directory of test files to be written.");
    diag_group->add_option("-o,--output-extension", data.output_extension)
        ->description(
            "file extension to be written to destination-dir for what was ultimately the result.");

    try {
        app.parse(argc, argv);
    }
    catch (CLI::CallForHelp const& e) {
        // strange call with the intend of help ...
        std::exit(app.exit(e));
    }
    catch (CLI::ParseError const& e) {
        std::string const bin_name = fs::path(e.get_name()).stem().generic_string();
        std::cerr << bin_name << ": Error occurred during parsing CLI:\n";
        // strange call to get a nice error message
        std::exit(app.exit(e));
    }

    data.initialized = true;
}

void cli_args::print_settings()
{
    //
    // Dataset loader
    //
    std::cout << "command line source directory:         "
              << (!data.source_dir.empty() ? data.source_dir : "N/A") << '\n';

    std::cout << "command line input file extension:     '"
              << (!data.input_extension.empty() ? data.input_extension : "N/A") << "'\n";

    std::cout << "command line expected file extension:  '"
              << (!data.expected_extension.empty() ? data.expected_extension : "N/A") << "'\n";

    //
    // Failure Diagnostic Fixture
    //
    std::cout << "command line destination directory:    "
              << (!data.destination_dir.empty() ? data.destination_dir : "N/A") << '\n';

    std::cout << "command line output file extension:    '"
              << (!data.output_extension.empty() ? data.output_extension : "N/A") << "'\n";
}

}  // namespace testsuite::util
